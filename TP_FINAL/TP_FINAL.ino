#include <LiquidCrystal.h>
//Defino constantes para identificar las salidas
#define p1 13
#define p2 12
#define d3 11
#define p4 10
#define d5 A3
#define d6 A4
#define d7 A5

//Defino constantes para identificar las teclas
#define NADA 0
#define SELECT 1
#define UP 2
#define DOWN 3 
#define LEFT 4
#define RIGHT 5 

//Objeto LCD
LiquidCrystal lcd(8,9,4,5,6,7); 

//Variables y firma de funciones
int valorTecla;
int i = 0;
char binario[4] = {'*','*','*','*'};
int inicio = NADA;
int botonPresionado = NADA;
int flag = 0;

void setup()
{
  //Defino pines como entradas o salidas
  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(p4, OUTPUT);
  pinMode(d5, OUTPUT);
  pinMode(d6, OUTPUT);
  pinMode(d7, OUTPUT);
  
  digitalWrite(p1, HIGH);
  digitalWrite(p2, HIGH);
  digitalWrite(d3, HIGH);
  digitalWrite(p4, HIGH);
  digitalWrite(d5, HIGH);
  digitalWrite(d6, HIGH);
  digitalWrite(d7, HIGH);
  
  lcd.begin(16,2);
  lcd.clear();           //Borrar la pantalla
  lcd.setCursor(5, 0);   
  lcd.print("TP SPD");
  lcd.setCursor(4, 1);
  lcd.print("Carranza");
  delay(1500);
  lcd.clear(); 
  lcd.setCursor(0, 0);   //Llevar el cursor al inicio
  lcd.print("Presiona SELECT");
  lcd.setCursor(0,1);
  lcd.print("para continuar.");
  lcd.setCursor(0, 0);   //Llevar el cursor al inicio
}

void loop()
{
    inicio = LeerBotones();
    while(inicio == SELECT && flag == 0)
    {
      lcd.clear();           //Borrar la pantalla
      lcd.setCursor(0, 0);   //Llevar el cursor al inicio
      lcd.print("Binario 4 bits:");
      for(int j = 0; j<4; j++)
      {
        lcd.setCursor(j,1);
        lcd.print(binario[j]);
      }
      
      SelectBit();
      delay(150); //reaccion en el movimiento
      if(LeerBotones() == SELECT && binario[0] != '*' && binario[1] != '*' && binario[2] != '*' && binario[3] != '*')
      {
        flag = 1;
        for(int k = 0 ; k <4; k++)
        {
          lcd.setCursor(k,1);
          lcd.noBlink();
        }
      }
    }
    
    digitalWrite(d3, !String(binario[0]).toInt());
    digitalWrite(d5, !String(binario[1]).toInt());
    digitalWrite(d6, !String(binario[2]).toInt());
    digitalWrite(d7, !String(binario[3]).toInt());
  
    delay(500);
    
    if(digitalRead(d3)==LOW && digitalRead(d5)==HIGH && digitalRead(d7)==HIGH || digitalRead(d3)==HIGH && digitalRead(d5)==HIGH && digitalRead(d7)==LOW || digitalRead(d3)==LOW && digitalRead(d5)==LOW && digitalRead(d7)==LOW || digitalRead(d3)==HIGH && digitalRead(d5)==LOW && digitalRead(d7)==HIGH)
    {
      digitalWrite(p1, LOW);
    }
  
    if(digitalRead(d3)==LOW && digitalRead(d6)==HIGH && digitalRead(d7)==HIGH || digitalRead(d3)==HIGH && digitalRead(d6)==HIGH && digitalRead(d7)==LOW || digitalRead(d3)==LOW && digitalRead(d6)==LOW && digitalRead(d7)==LOW || digitalRead(d3)==HIGH && digitalRead(d6)==LOW && digitalRead(d7)==HIGH)
    {
      digitalWrite(p2, LOW);
    }
  
    if(digitalRead(d5)==LOW && digitalRead(d6)==HIGH && digitalRead(d7)==HIGH || digitalRead(d5)==HIGH && digitalRead(d6)==HIGH && digitalRead(d7)==LOW || digitalRead(d5)==LOW && digitalRead(d6)==LOW && digitalRead(d7)==LOW || digitalRead(d5)==HIGH && digitalRead(d6)==LOW && digitalRead(d7)==HIGH)
    {
      digitalWrite(p4, LOW);
    }
}

//----Funciones----

// Lee la entrada analógica y devuelve la tecla presionada
int LeerBotones()  
{
  valorTecla = analogRead(A0);
 
 if (valorTecla > 1000 )   
 {
  return NADA;  
 }
  
 if (valorTecla < 50 )   
 {
  return RIGHT;  
 }
 if (valorTecla < 195 ) 
 {
   return UP; 
 }
 if (valorTecla < 380 ) 
 {
   return DOWN; 
 }
 if (valorTecla < 555 )
 {
   return LEFT;
 }
 if (valorTecla < 790 )  
 {
   return SELECT;  
 }
  
  return NADA;
}

void SelectBit()
{
  lcd.setCursor(i,1);
  lcd.blink();
  
  botonPresionado = LeerBotones();  // Lee las teclas
 
 switch (botonPresionado)               
 {
   case RIGHT:
     {
     if( i < 3)
     {
      //lcd.setCursor(i,1);
      lcd.blink();
      i++;
     }
     break;
     }
   case LEFT:
     {
      //lcd.setCursor(i,1);
      lcd.blink();
      i--;
     break;
     }
   case UP:
     {
     lcd.setCursor(i,1);
     lcd.print(binario[i] = '1');
     break;
     }
   case DOWN:
     {
     lcd.setCursor(i,1);
     lcd.print(binario[i] = '0');
     break;
     }
   case SELECT:
   case NADA:
     break;
    
 }
}
