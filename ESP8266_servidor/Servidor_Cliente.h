

String Pagina =  R"====(<!doctypehtml><html lang=en><meta charset=UTF-8><meta content="width=device-width,initial-scale=1"name=viewport><title>ESP8266 Server</title><style>html{font-family:'Segoe UI',tahoma,Geneva,Verdana,sans-serif;background:#000;background:linear-gradient(to right,#5b5757,#000);display:inline-block;text-align:center}body{margin:0 auto;max-width:600px;padding-bottom:25px;display:flex;align-items:center;justify-content:center;height:100vh}.contenedor{background-color:#fff;padding:20px;border-radius:8px;box-shadow:0 0 10px rgba(0,0,0,1.5)}h1{text-decoration:underline;font-size:2.7rem;color:#16d13c}h4{font-family:Arial,sans-serif;font-size:20px;margin:0;padding:0;display:flex;align-items:center;justify-content:center;height:15vh;color:#000}#espacio_contenedor{margin-top:20px}#valor_distancia{margin-left:10px;margin-right:10px;height:33px;font-weight:700;font-size:24px;color:#007bff}.rango{font-size:20px}</style><div class=contenedor><h1>Fisgon Parking Monitoring</h1><div id=espacio_contenedor><h4 class=display id=dist1>Parqueadero 1: <span class=display id=valor_distancia1>---</span> Cm</h4><output class=rango id=rango_valP1>40</output><br><input id=rangoP1 max=400 min=2 oninput="rango_valP1.value=value"type=range value=40><h4 class=display id=dist2>Parqueadero 2: <span class=display id=valor_distancia2>---</span> Cm</h4><output class=rango id=rango_valP2>40</output><br><input id=rangoP2 max=400 min=2 oninput="rango_valP2.value=value"type=range value=40></div></div><script>const tiempoAgotado = 4000;
        const dist1 = document.getElementById('valor_distancia1');
        const dist2 = document.getElementById('valor_distancia2');
        const elementoRango1 = document.getElementById('rangoP1');
        const elementoRango2 = document.getElementById('rangoP2');

        elementoRango1.addEventListener('click', cambiarDistancia1);
        elementoRango2.addEventListener('click', cambiarDistancia2);

        document.addEventListener('DOMContentLoaded', () => {
            console.log('Página cargada!');
            setTimeout(actualizarDistancia1, tiempoAgotado);
        });

        function actualizarDistancia1(processTemp){
            let xhr = new XMLHttpRequest();

            xhr.onreadystatechange = () => {
                //Hecho = 4
                if(xhr.readyState === 4 && xhr.status === 200) {
                    dist1.innerText = xhr.responseText;
                }
            }

            xhr.open('GET', "/")
            xhr.send();
            setTimeout(actualizarDistancia1, tiempoAgotado);
        }
        

        function cambiarDistancia1(){
            const elementoRango1 = document.getElementById('rangoP1');
            console.log("Cambiando distancia del sensor a " + elementoRango1.value + " para el parqueadero 1");
            consultaGET("http://%ip/puesto1?valor=" + elementoRango1.value);
        }

        function cambiarDistancia2(){
            const elementoRango2 = document.getElementById('rangoP2');
            console.log("Cambiando distancia del sensor a " + elementoRango2.value + " para el parqueadero 2");
            consultaGET("http://%ip/puesto2?valor=" + elementoRango2.value);
        }



        function consultaGET(consulta){
            const Http = new XMLHttpRequest();
            console.log(`Consultando  ${consulta}`)
            Http.open("GET", consulta);
            Http.send();

            Http.onreadystatechange = (e) =>{
                console.log(Http.status);
                //console.log(Http.responseText);
            };
        }</script>)====";


void paginaInicio(){
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/html", Pagina);
}

void mensajeError() {
  String mensaje = "<h1>404</h1>";
  mensaje += "Pagina No encontrada</br>";
  mensaje += "Intenta otra pagina</br>";
  server.send(404, "text/html", mensaje);
}


void Sensor1(){
  Serial.println();
  //server.sendHeader("Access-Control-Allow-Origin", "*");
  //server.send(200, "text/plain", "Endendiendo LED");
}

void funcionNivel1() {

  if (server.hasArg("valor1")) {
    Valor1 = server.arg("valor1");
    Nivel1 = atoi(Valor1.c_str());
    Serial << "Cambiando nivel " << Nivel1 << "\n";
  }
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "Nivel Cambiado");
}

void Sensor2(){
  Serial.println();
 // server.sendHeader("Access-Control-Allow-Origin", "*");
  //server.send(200, "text/plain", "Endendiendo LED");
}

void funcionNivel2() {

  if (server.hasArg("valor2")) {
    Valor2 = server.arg("valor2");
    Nivel2 = atoi(Valor2.c_str());
    Serial << "Cambiando nivel " << Nivel2 << "\n";
  }
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "Nivel Cambiado");
}
