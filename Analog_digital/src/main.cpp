#include <Arduino.h>
#define red 9
#define blue 10
#define green 11

int gRGB = 125;
int r, g, b;

void setup() {
  pinMode(red,OUTPUT);
  pinMode(blue,OUTPUT);
  pinMode(green,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()>0){
    if(Serial.read()=='#'){
      r = Serial.parseInt();
      g = Serial.parseInt();
      b = Serial.parseInt();
    }
    Serial.print(r);
    Serial.print(" ");
    Serial.print(g);
    Serial.print(" ");
    Serial.println(b);
    analogWrite(red,r);
    analogWrite(green,g);
    analogWrite(blue, b);
  }
}

