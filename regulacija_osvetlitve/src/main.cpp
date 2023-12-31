#include <Arduino.h>
#define led1 9
#define led2 10
#define led3 11

double pwm = 0.0;
double Kp = 1.0;
double Kd = 0.0;
double Ki = 1.0;
double e_prejsnji = 0.0, e = 0.0;
double e_sum = 0.0;
const uint32_t interval = 1;
uint32_t frameCount = 0;

void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  Serial.begin(115200);
}

void loop()
{
  uint32_t time = millis();
  if ((millis() - time) > interval)
  {
    int setpoint = analogRead(A0);
    long setpoint_m = map(setpoint, 0, 1023, 0, 255);
    int osvetlitev = analogRead(A1);
    long osvetlitev_m = map(osvetlitev, 0, 1023, 0, 255);
    e = setpoint_m - osvetlitev_m;
    e_sum += (e * interval);
    if (e_sum > 100) e_sum = 100;
    if (e_sum < -100) e_sum = -100;

    pwm = Kp * e + Kd * (e - e_prejsnji)/(double)interval + Ki * e_sum;
    if (pwm > 255.0)
      pwm = 255.0;

    Serial.print(frameCount++);
    Serial.print("\t");
    Serial.print(pwm);
    Serial.print("\t");
    Serial.print(setpoint_m);
    Serial.print("\t");
    Serial.println(osvetlitev_m);

    if (pwm < 0)
      pwm = 0;

    analogWrite(led1, pwm);
    analogWrite(led2, pwm);
    analogWrite(led3, pwm);
    delay(100);
    e_prejsnji = e;
  }
}
