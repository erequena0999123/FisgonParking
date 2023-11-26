//==================================================================================
//Definición de Librerias para el proyecto
//==================================================================================

#if defined(ESP32)

//Librerias para ESP32
#include <WiFi.h>
#include <WiFiMulti.h>
#include <ESPmDNS.h>
#include <DNSServer.h>
#include <WebServer.h>
WiFiMulti WifiMulti;

WebServer server(80);

#elif defined(ESP8266)

//Librerias para ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
//#include <ESPAsyncWebServer.h>

//Establecer el módulo ESP8266 como servidor
//AsyncWebServer server(80); //Puerto 80 (http)
ESP8266WebServer server(80);

#endif

#include <WiFiManager.h>

//WiFiManager, creación de un objeto
WiFiManager wm;

#include <Ticker.h>
Ticker tick;
#define Led_interno LED_BUILTIN
byte cont = 0;

//Código aplicado para generar sobrecarga de operadores
template<class T> inline Print &operator <<(Print &obj, T arg) { 
  obj.print(arg); 
  return obj; 
}

//==================================================================================
//Definición de funciones para el proyecto
//==================================================================================


void AccessPoint(){
  
//==================================================================================
//                                 Código para Access Point
//==================================================================================
    
  // Se obtiene la macID para nombrar nuestro dispositivo
  // Nuestra SSID sera ESP8266 Server + macID
  String mac = WiFi.macAddress();

  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) + String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  String AP_NombreString = "ESP8266 Server " + macID;
  

  char AP_NombreChar[AP_NombreString.length() + 1];
  memset(AP_NombreChar, AP_NombreString.length() + 1, 0);
  

  for (int i = 0; i < AP_NombreString.length(); i++)
    AP_NombreChar[i] = AP_NombreString.charAt(i);


  // Se crea el punto de acceso con el nombre ESP8266 Thing + macID 
  // con la contraseña maestra
  Serial.println(WiFi.softAP(AP_NombreChar, Password_AP) ? "Listo" : "Fallo");
}

void ParpadeoLedWifi(){
  //Cambia el estado del LED
  byte estado = digitalRead(Led_interno);
  digitalWrite(Led_interno, !estado);
}

void WifiManager(){

  pinMode(Led_interno, OUTPUT);
  //WiFiManager wm;

  //Uso de la libreria ticker para hacer un temporizador 
  tick.attach_ms(500, ParpadeoLedWifi);

  //Función para borrar la información almacenada en la EEPROM de redes WiFi
  //Función propia de la libreria del ESP8266
  //wm.resetSettings();

  //Creamos el AP y comprobamos si se establece la conexión
  if (!wm.autoConnect("WManager_ESP8266SERVER", "password")){
    Serial.println("Fallo en la conexión, tiempo de espera agotado");
    ESP.restart();
    delay(1000);
  }

  Serial.println("Conexión exitosa!!");

  AccessPoint();

  //Eliminamos el temporizador
  tick.detach();
  //Apagar el LED
  digitalWrite(Led_interno, HIGH); 
}


void ArranqueWifi(){

//==================================================================================
//                                  Código para estación
//==================================================================================
  Serial.begin(115200);
  delay(2000);
  WiFi.mode(WIFI_AP_STA);
  
  Serial.print("Conectando a Wifi...");
  if (WiFi.status() == WL_CONNECTED) {
    
    Serial << "\n" << "Conectado" << "\n";
    Serial << "SSID: " << WiFi.SSID() << "\n" << "IP: " << WiFi.localIP() << "\n";

    AccessPoint();

  }
  else{
    Serial.println("Iniciando WiFi manager..");
    WifiManager();
  }
}


//Función para refrescar el Wifi en caso de desconexión
void ActualizarWifi(){

  while(WiFi.status()!= WL_CONNECTED){
    if(WiFi.status()!= WL_CONNECTED && cont == 5){
      cont = 0;
      break;
    }
    else{
      cont++;
      Serial.print(".");
      Serial.print(cont);
      delay(2000);
    }
  }

  WifiManager();
  
  Serial << "\n" << "Conectado" << "\n";
  Serial << "SSID: " << WiFi.SSID() << "\n" << "IP: " << WiFi.localIP() << "\n";
}


void mDNS(){

  //Configuración y uso de la libreria mDNS para asignar nombre 
  //para evitar usar la IP en el navegador
  if (!MDNS.begin("EspServer")) {
    Serial.println("Error configurando mDNS!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS configurado");

  //Servicios asignados al mDNS
  MDNS.addService("http", "tcp", 80);
}
