
#include <Arduino.h>

int cas=100;

void setup()
{
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop()
{
  for (int n = 10; n <= 13; n++)
  {
    digitalWrite(n, LOW);
    delay(cas);
    digitalWrite(n, HIGH);
  }
  for (int n = 13; n >= 10; n--)
  {
    digitalWrite(n, LOW);
    delay(cas);
    digitalWrite(n, HIGH);
  }
  cas-=5;
  if(cas<=0) cas =100;
  
}
