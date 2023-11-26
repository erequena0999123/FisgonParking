//Declaración e inicialización de las variables utilizadas
//para la conexión WIFI local
const char* ESPSSID         = "ESP8266 Server 423A?";
const char* PasswordSSID    = "M_2R9'5#V+w8";


//Información del servidor
const char* host            = "192.168.4.1"; //Dirección IP del servidor
const uint8_t httpPort      = 80; //Puerto de conexión

String macID; //Variable para almacenar la macID
String url;

//Variable donde se almacenará la medición del sensor ultrasónico
int valor_dist;


//Variables para medir el tiempo con millis
unsigned int timer, t1=0,t2=0,t3=0;


//==================================================================================
//Definición de pines para el nodeMCU V3 1.0 ESP8266 Módulo ESP - 12E
//==================================================================================

#define D0    16   //GPIO16  - WAKE UP
#define D1    5    //GPIO5
#define D2    4    //GPIO4
#define D3    0    //GPIO0
#define D4    2    //GPIO2   - TXD1

#define D5    14   //GPIO14  - HSCLK
#define D6    12   //GPIO12  - HMISO
#define D7    13   //GPIO13  - HMOSI  - RXD2
#define D8    15   //GPIO15  - HCS    - TXD2
#define RX    3    //GPIO3   - RXD0
#define TX    1    //GPIO1   - TXD0

#define S2 9       //GPIO9
#define S3 10      //GPIO10


//==================================================================================
//Inicialización de pines para el funcionamiento del sensor
//==================================================================================
 
const uint8_t TRIG = D7;      // Señal de transmisión
const uint8_t ECO = D5;       // Señal de recepción
const uint8_t LED_ROJO = D0;  // Led rojo
const uint8_t LED_VERDE = D2; // Led verde
int           DURACION;       // Variable para almacenar la información recibida del sensor
int           DISTANCIA;      // Variable utilizada para transformar a distancia según la información
                              // dada por el fabricante del sensor ultrasónico
const uint8_t Dist_max = 30;
const uint8_t Dist_min = 2;

//==================================================================================
//Setting y funcionamiento del sensor
//==================================================================================

void SetPins(){
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECO, INPUT);
}

void LecturaUltrasonica(){
  digitalWrite(TRIG, HIGH);      // Estas tres líneas sirven para medir el tiempo que toma
  delayMicroseconds(10);          // el sensor para enviar y recibir una respuesta  
  digitalWrite(TRIG, LOW);
  
  DURACION = pulseIn(ECO, HIGH); // Devuelve un valor de tiempo equivalente en microsegundos
  DISTANCIA = DURACION / 58.3;   // 58.3 es un valor especificado por el fabricante
                                 // y el resultado es dado en centímentros

// El if evaluará la distancia captada por el sensor y apagará y encenderá los leds
  if (DISTANCIA >= Dist_min && DISTANCIA <= Dist_max){
    digitalWrite(LED_ROJO, HIGH);
    digitalWrite(LED_VERDE, LOW);
  }
  else if (DISTANCIA >= Dist_max){
    digitalWrite(LED_ROJO, LOW);
    digitalWrite(LED_VERDE, HIGH);
  }
  else{
    digitalWrite(LED_ROJO, LOW);
    digitalWrite(LED_VERDE, LOW);
  }
}
