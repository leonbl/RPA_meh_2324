#include <Arduino.h>
#define tipka 2
#define led 13
int staroStanje = 0;

void setup()
{
  pinMode(tipka, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int stanje = digitalRead(tipka);
  int dCnt = 0, longCnt=0;
  if (staroStanje == 1 && stanje == 0)
  {
    for (int n = 0; n < 5; n++)
    {
      delay(5);
      if (stanje == 0)
        dCnt++;
    }
    while(digitalRead(tipka) == 0){
      delay(1);
      if(longCnt++ > 3000) break;
    }

    if(longCnt>3000)
      Serial.println("long press");
  }
  staroStanje = stanje;
}
