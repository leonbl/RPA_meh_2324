#include <Arduino.h>
#include "IFX007T-Motor-Control.h"
#include <QuickPID.h>

#define encA 2
#define encB 4

// Define Variables we'll be connecting to
float Setpoint, Input, Output;
float Kp = 1.3, Ki = 15.0, Kd = 0.1;
// Specify PID links
QuickPID myPID(&Input, &Output, &Setpoint);

char str[50];
char cmd = ' ';
uint8_t speed = 0;
bool direction = 1;

// Sample time
uint32_t loopTime = 50;
uint32_t time = 0;

volatile int32_t cnt = 0, oldCnt = 0;

IFX007TMotorControl MyMotor = IFX007TMotorControl();

void encoder();

void setup()
{
  Setpoint = 10000;
  myPID.SetOutputLimits(-255, 255);
  myPID.SetSampleTimeUs(loopTime * 1000);
  // apply PID gains
  myPID.SetTunings(Kp, Ki, Kd);
  // turn the PID on
  myPID.SetMode(myPID.Control::automatic);

  pinMode(encB, INPUT);
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(encA), encoder, RISING);
  MyMotor.begin();
}

void loop()
{
  uint32_t cnt = 0;
  while (millis() - time < loopTime)
  {
    if(cnt == 0){
      Serial.println(millis() - time);
      cnt = 1;
    }
  }
  time = millis();
  Input = cnt; // pozicija
  // Input = cnt - oldCnt;  // hitrost
  oldCnt = cnt;
  myPID.Compute();
  // Serial.print(Input);
  // Serial.print(" ");
  // Serial.println(Output);
  if (Output < 0)
  {
    direction = false;
    speed = abs(Output);
  }
  else
  {
    direction = true;
    speed = Output;
  }
  MyMotor.setBiDirMotorSpeed(direction, speed);

  if (Serial.available() > 0 && Serial.read() == '!')
  {
    uint32_t index = 0;
    while (index < 50)
    {
      str[index] = Serial.read();
      if (str[index] == 'P')
      {
        cmd = 'P';
      }
      else if (str[index] == 'D')
      {
        cmd = 'D';
      }
      else if (str[index] == 'I')
      {
        cmd = 'I';
      }
      else if (str[index] == 'X')
      {
      }
      else if (str[index] == '#')
      {
        str[index] = 0;
        break;
      }
      else if (isDigit(str[index]) || str[index] == '.')
      {
        index++;
      }
    }
    if (cmd == 'P')
    {
      Kp = atof(str);
      Serial.print("Kp: ");
      Serial.println(Kp);
    }
    else if (cmd == 'D')
    {
      Kd = atof(str);
      Serial.print("Kd: ");
      Serial.println(Kd);
    }
    else if (cmd == 'I')
    {
      Ki = atof(str);
      Serial.print("Ki: ");
      Serial.println(Ki);
    }
    cmd = ' ';
    memset(str, 0, 50);
  }
  Serial.print(Kp);
  Serial.print(",");
  Serial.print(Ki);
  Serial.print(",");
  Serial.print(Kd);
  Serial.print(",");
  Serial.print(Setpoint);
  Serial.print(",");
  Serial.print(Input);
  Serial.print(",");
  Serial.print(Output);
  Serial.println("#");
}

void encoder()
{
  if (digitalRead(encB) == HIGH)
    cnt += 1;
  else
    cnt -= 1;
}