#define LED_ROJO 12  //defino pin
#define LED_AMARILLO 11
#define LED_VERDE 10
#define PULSADOR 9

void setup()
{
  pinMode(LED_ROJO, OUTPUT); //Pin 12 como salida
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(PULSADOR, INPUT);
  Serial.begin(9600); //inicia comunicacion serie
}

int pulsador = HIGH; //guardo el pulso, inicia apagado
int estadoLEDS = 0; //estado de los leds apagados
int estadoANT = HIGH; //estado anterior del pulsador

void loop()
{
  pulsador = digitalRead(PULSADOR);
  delay(50);
  
  if(pulsador == LOW && estadoANT == HIGH)
  {
    estadoLEDS = 1 - estadoLEDS;
    delay(50);
  }
  
  estadoANT = pulsador;
  
  if(estadoLEDS == 1)
  {
  Serial.println("Secuencia encendida");

  digitalWrite(LED_VERDE, LOW); 
  digitalWrite(LED_ROJO, HIGH); //pin 12 en alto
  delay(2000);  //retardo 1 seg  
  
  digitalWrite(LED_AMARILLO, HIGH); 
  delay(1500);  
  digitalWrite(LED_AMARILLO, LOW);
  digitalWrite(LED_ROJO, LOW);
  
  digitalWrite(LED_VERDE, HIGH); 
  delay(3000);  
  digitalWrite(LED_AMARILLO, HIGH); 
  delay(1500); 
  digitalWrite(LED_AMARILLO, LOW);
  digitalWrite(LED_VERDE, LOW);
  
  digitalWrite(LED_ROJO, HIGH);
  estadoLEDS = 0;
  Serial.println("Fin de secuencia");
  }
  else 
  {
    Serial.println("Apagados");
    //digitalWrite(LED_VERDE, LOW);
    //digitalWrite(LED_AMARILLO, LOW);
    //digitalWrite(LED_ROJO, LOW);
  }  
}
