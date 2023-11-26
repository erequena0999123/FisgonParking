#include <Ticker.h>
Ticker lectorUltraS;

//Librerias internas del proyecto
#include "Datos.h"
#include "Wifi.h"
#include "Cliente_Servidor.h"



void setup() {

  ArranqueWifi();

  SetPins();

}

void loop() {

  //timer = millis();
  
  //Condición que llama a la función de reconectar al wifi
  if (WifiMulti.run() != WL_CONNECTED){
    ActualizarWifi();
  }

  if (ECO == NULL){
    Serial.println("Fallo del sensor!!");
    return;
  }


  LecturaUltrasonica();
  
  
  valor_dist = (int)DISTANCIA;
  Serial << valor_dist << " cm" << "\n";


  ConexionServidor();

}
