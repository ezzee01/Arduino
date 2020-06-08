#define LEDUNO 12
#define LEDDOS 11
#define PULSADOR 9

void setup()
{
  pinMode(LEDUNO, OUTPUT);
  pinMode(LEDDOS, OUTPUT);
  pinMode(PULSADOR, INPUT);
}

int pulsador = HIGH;  //guarda el pulso
int estadoLEDS = 0;  //led apagado
int estadoANT = HIGH;  //estado anterior del pulsador
int contador = 0;  //cuenta cantidad de veces pulsado

void loop()
{
  pulsador = digitalRead(PULSADOR);
  delay(100);

  if(pulsador == LOW && estadoANT == HIGH)
  {
    estadoLEDS = 1 - estadoLEDS;
    contador++;
  }

  estadoANT = pulsador;

  if(estadoLEDS == 1 )
  {
    digitalWrite(LEDUNO, HIGH);
  }
  else
  {
    digitalWrite(LEDUNO, LOW);
    
    if(contador == 2)
    {
      digitalWrite(LEDDOS, HIGH);
    }
    else
    {
      digitalWrite(LEDDOS, LOW);
    
      if(contador == 3)
      {
        digitalWrite(LEDUNO, HIGH);
        digitalWrite(LEDDOS, HIGH);
      }
    }
  }

  if(contador == 3)
  {
    contador = -1;
  }
}
