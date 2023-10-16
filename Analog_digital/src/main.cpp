#include <Arduino.h>
#define red 9
#define blue 10
#define green 11

int gRGB = 125;

void setup() {
  pinMode(red,OUTPUT);
  pinMode(blue,OUTPUT);
  pinMode(green,OUTPUT);
}

void loop() {
  for(int n=0; n<256; n++){
    analogWrite(red, n);
    analogWrite(blue,abs(n-255));
    if(n<125)gRGB++;
    else gRGB--;
    analogWrite(green,gRGB);
    delay(10);
  }
  for(int n=255; n>=0; n--){
    analogWrite(red, n);
    analogWrite(blue,abs(n-255));
    if(n>125)gRGB--;
    else gRGB++;
    delay(10);
  }
}

