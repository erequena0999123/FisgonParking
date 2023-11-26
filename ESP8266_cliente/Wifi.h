#if defined(ESP32)

//Librerias para ESP32
#include <WiFi.h>
#include <WiFiMulti.h>
WiFiMulti WifiMulti;

#elif defined(ESP8266)

//Librerias para ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti WifiMulti;

#endif


//Código aplicado para generar sobrecarga de operadores
template<class T> inline Print &operator <<(Print &obj, T arg) { 
  obj.print(arg); 
  return obj; 
}

void ArranqueWifi(){

//==================================================================================
//                                  Código para estación
//==================================================================================

  Serial.begin(115200);
  delay(2000);

  // Obtenemos la macID de nuestro ESP8266
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) + String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  Serial.print(macID);
  
  WiFi.mode(WIFI_STA);
  Serial.println("\nIniciando multi Wifi");

  //Redes wifi configuradas
  WifiMulti.addAP(ESPSSID, PasswordSSID);
  WifiMulti.addAP("", "");

  //Ejecucion del multi Wifi para conectarse a una red de las configuradas
  Serial.print("Conectando a Wifi...");
  if (WifiMulti.run() == WL_CONNECTED) {
    
    Serial << "\n" << "Conectado" << "\n";
    Serial << "SSID: " << WiFi.SSID() << "\n" << "IP: " << WiFi.localIP() << "\n";
  }
}


//Función para refrescar el Wifi en caso de desconexión
void ActualizarWifi(){

  while(WifiMulti.run()!= WL_CONNECTED){
    Serial.print(".");
    delay(5000);
  }
  
   Serial << "\n" << "Conectado" << "\n";
   Serial << "SSID: " << WiFi.SSID() << "\n" << "IP: " << WiFi.localIP() << "\n";
}
