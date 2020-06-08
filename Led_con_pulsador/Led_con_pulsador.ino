#define LED 13
#define PULSADOR 12

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(PULSADOR, INPUT);
}

int pulsador = HIGH; //guardo el valor del pulsador
int estadoLED = 0; //estado del led apagado
int estadoANT = HIGH; //estado anterior del pulsador

void loop()
{  
  pulsador = digitalRead(PULSADOR); //leo pin del pulsador
  delay(50);
  
  if(pulsador == LOW && estadoANT == HIGH) 
  {
    estadoLED = 1 - estadoLED; //cambia el estado del led cuando se pulsa
  }
  
   estadoANT = pulsador;  //guardo el estado que tenia el pulsador
  
  if(estadoLED == 1)
  {
    digitalWrite(LED, HIGH); //pendo el led cuando el estado lo indique
  }
  else digitalWrite(LED, LOW);
}
