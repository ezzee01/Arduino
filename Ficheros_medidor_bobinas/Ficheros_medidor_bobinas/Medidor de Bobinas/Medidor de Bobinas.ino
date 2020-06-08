#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);                                   // cambiar el LCD address a 0x3f si no funciona
double pulso, frecuencia, capacidad, valor, inductancia;              // Variables globales usadas.
int numeroLecturas = 500;
const int pulsoOut = 20;
const int pulsoIn = 21;
int buzzer = 8;
int flag = 0;

void setup()
{
  pinMode(pulsoIn, INPUT);                                           // Pin lectura pulso.
  pinMode(pulsoOut, OUTPUT);                                         // Pin carga osciladr
  lcd.init();                                                       // Inicializamos el lcd.
  lcd.backlight();                                                  // Encendemos el backlight, para apagarlo lcd.noBacklight
  lcd.setCursor(0, 0);                                              // Cursor en posicion 0,0.
  lcd.print("Inductance-meter.");
  lcd.setCursor(0, 1);
  lcd.print("Rev.1");
  delay(1500);
}

void loop()
{
  valor = medir();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print ("Valor:");

  if (valor > 1000)
  {
    if (flag == 0)
    {
      tone(buzzer, 1000 , 250);
      flag = 1;
    }
    valor = valor / 1000;
    lcd.setCursor(7, 0);
    lcd.print (valor);
    lcd.setCursor(13, 0);
    lcd.print ("mH.");
  }
  else
  {
    lcd.setCursor(7, 0);
    lcd.print (valor);
    lcd.setCursor(13, 0);
    lcd.print ("uH.");
    flag = 0;
  }
  delay(1);
}

//Funcion

double medir()
{

  double auxInductancia = 0;

  for (int conta = 0; conta < numeroLecturas ; conta++)
  {
    digitalWrite(pulsoOut, HIGH);
    delay(5);                                                                  // Dar algun timepo para cargar la bobina.
    digitalWrite(pulsoOut, LOW);
    delayMicroseconds(100);                                                    // verificar que mide la resonancia.
    pulso = pulseIn(pulsoIn, HIGH, 5000);                                           // retorna 0 si esta fuera de tiempo.
    if (pulso > 0.1) 
    {                                                         // Si no se activo el fuera de tiempo ... tomo una lectura:
      capacidad = 2.E-6;                                                       // Insertar la capacidad de los condensadores aqui. Por defecto se usa 2 uF pero se debe medir el valor real del componente para mayor exactitud.
      frecuencia = 1.E6 / (2 * pulso);
      inductancia = 1. / (capacidad * frecuencia * frecuencia * 4.*3.14159 * 3.14159);
      inductancia *= 1E6;                                                        // Tenga en cuenta que esto es lo mismo que decir  inductance = inductance*1E6
      auxInductancia += inductancia;
    }
  }
  return (auxInductancia / numeroLecturas);
}
