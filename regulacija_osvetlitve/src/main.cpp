#include <Arduino.h>
#define led1 9
#define led2 10
#define led3 11

double pwm = 0.0;
double Kp = 1.2;
double Kd = 0.8;
double e_prejsnji = 0.0, e = 0.0;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  int setpoint = analogRead(A0);
  long setpoint_m = map(setpoint, 0, 1023, 0, 255);
  int osvetlitev = analogRead(A1);
  long osvetlitev_m = map(osvetlitev, 0, 1023, 0, 255);
  e = setpoint_m - osvetlitev_m;
  pwm = Kp*e + Kd * (e-e_prejsnji);
  if(pwm>255.0) pwm=255.0;

  Serial.print(pwm);
  Serial.print(" i:");
  Serial.print(setpoint_m);
  Serial.print(" o:");
  Serial.println(osvetlitev_m);

  if(pwm < 0) pwm = 0;

  analogWrite(led1,pwm);
  analogWrite(led2,pwm);
  analogWrite(led3,pwm);
  delay(100);
  e_prejsnji = e;
}
