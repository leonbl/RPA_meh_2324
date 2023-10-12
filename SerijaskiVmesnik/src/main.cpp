#include <Arduino.h>

int n = 0;
void setup()
{
  pinMode(10,OUTPUT);
pinMode(11,OUTPUT);
pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
digitalWrite(10,HIGH);
digitalWrite(11,HIGH);
digitalWrite(12,HIGH);
  digitalWrite(13,HIGH);
  Serial.begin(9600);
  Serial.println("V setup() funkciji...");
}

void loop()
{
  int znak = 0;
  if (Serial.available() > 0)
  {
    znak = Serial.parseInt();
    Serial.print(">: ");
    Serial.println(znak);
  }
  if(znak != 0){
    Serial.print("Fuck off... ");
    Serial.println(znak);
    switch(znak){
      case 1: Serial.println("Case 1!!!!!!!!!!");
      digitalWrite(10,LOW); break;
      case 2: digitalWrite(11,LOW); break;
      case 3: digitalWrite(12,LOW); break;
      case 4: digitalWrite(13,LOW); break;
      case 5: digitalWrite(10,HIGH); break;
      case 6: digitalWrite(11,HIGH); break;
      case 7: digitalWrite(12,HIGH); break;
      case 8: digitalWrite(13,HIGH); break;
      default: break;
    }
  }
  delay(10);
}
