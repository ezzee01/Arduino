#include <Servo.h>
//Variables y objetos
int pos = 0;
int estadoANT = 0;
Servo miServo;

void setup()
{
  miServo.attach(9,500,1600);
}

void loop()
{
  pos = analogRead(A0);  //leo potenciometro  
  pos = map(pos,0,1023,0,180); //mapeo valor pote de 0-1023 a 0-180 
  //delay(100);
  
  if(estadoANT != pos)
  {
    estadoANT = pos;
    miServo.write(pos);  //indico la posicion al servo
    delay(15);
  }

//  miServo.write(0);
//  delay(20);  
//
//  miServo.write(90);
//  delay(1000); 
//
//  miServo.write(180);
//  delay(1000); 
}
