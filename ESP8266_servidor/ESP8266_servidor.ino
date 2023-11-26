//Librerias internas del proyecto
#include "Datos.h"
#include "Wifi.h"
#include "Servidor_Cliente.h"


void setup() {
  
  ArranqueWifi();
  
  mDNS();

  
  server.on("/", paginaInicio);
  
  server.on("/sensor1", Sensor1);
  server.on("/nivel1", funcionNivel1);
  
  server.on("/sensor2", Sensor2);
  server.on("/nivel2", funcionNivel2);
  
  server.onNotFound(mensajeError);
  
  //Inicialización del servidor
  server.begin();
  Serial.println("Servidor HTTP iniciado");

  Pagina.replace("%ip", WiFi.localIP().toString());
}

void loop() {

  //Condición que llama a la función de reconectar al wifi
  if (WiFi.status() != WL_CONNECTED){
    ActualizarWifi();
  }

  server.handleClient();

  #if defined(ESP8266)
    MDNS.update();
  #endif
  
  //Variable para determinar la disponibilidad del cliente
  //WiFiClient cliente = server.available();
  
  


}
