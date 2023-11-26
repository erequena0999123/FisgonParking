void ConexionServidor(){
  // Inicia la conexión con el servidor
  Serial << "Conectando a...  " << "\n" << host;
  
  // Se intenta la conexión con el servidor
  WiFiClient client;
  if (!client.connect(host, httpPort)) {
    Serial.println("Conexión fallida!!!");
    return;
  }

  //Si la conexión es realizada, se realiza una URL concatenando la mac del ESP8266
  //con el valor de la distancia leída
  url   = macID;
  url  += "&valor_dist";
  url  += valor_dist;

  Serial << "Solicitando URL: " << url << "\n";
}
