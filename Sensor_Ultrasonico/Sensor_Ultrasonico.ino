#define D0    16   //GPIO16  - WAKE UP
#define D1    5    //GPIO5
#define D2    4    //GPIO4
#define D3    0    //GPIO0
#define D4    2    //GPIO2   - TXD1

#define D5    14   //GPIO14  - HSCLK
#define D6    12   //GPIO12  - HMISO
#define D7    13   //GPIO13  - HMOSI  - RXD2
#define D8    15   //GPIO15  - HCS    - TXD2
#define RX    3    //GPIO3    - RXD0
#define TX    1    //GPIO1    - TXD0

#define S2 9       //GPIO9
#define S3 10      //GPIO10


int  TRIG = D7; // Señal de transmisión
int ECO = D5; // Señal de recepción
int LED_ROJO = D0; // Led rojo
int LED_VERDE = D2; // Led verde
int DURACION; // Variable para almacenar la información recibida del sensor
int DISTANCIA; // Variable utilizada para transformar a distancia según la información
               // dada por el fabricante del sensor ultrasónico

void setup() {
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECO, INPUT);
  Serial.begin(115200);

}

void loop() {

  digitalWrite(TRIG, HIGH); // Estas tres líneas sirven para medir el tiempo que toma
  delay(1);                 // el sensor para enviar y recibir una respuesta  
  digitalWrite(TRIG, LOW);
  
  DURACION = pulseIn(ECO, HIGH); // Devuelve un valor de tiempo equivalente en microsegundos
  DISTANCIA = DURACION / 58.2;   // 58.2 es un valor especificado por el fabricante
                                 // y el resultado es dado en centímentros

  Serial.println(DISTANCIA);  // Usaremos el monitor serial para visualizar los valores
  delay(200);                  // dados por el sensor



// El if evaluará la distancia captada por el sensor y apagará y encenderá los leds
  if (DISTANCIA <= 30){
    digitalWrite(LED_ROJO, HIGH);
    digitalWrite(LED_VERDE, LOW);
  }
  else{
    digitalWrite(LED_ROJO, LOW);
    digitalWrite(LED_VERDE, HIGH);
  }
  delay(100);
}
