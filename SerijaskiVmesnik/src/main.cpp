#include <Arduino.h>

int cas =100;

void setup()
{
  pinMode(10,OUTPUT);
  pinMode(A2, INPUT);
}

void loop()
{
  digitalWrite(10,digitalRead(A2));  
}
