#include <Arduino.h>
#include "IFX007T-Motor-Control.h"
#include <QuickPID.h>

#define encA 2
#define encB 4

//Define Variables we'll be connecting to
float Setpoint, Input, Output;
float Kp = 1.3, Ki = 15.0, Kd = 0.1;
//Specify PID links
QuickPID myPID(&Input, &Output, &Setpoint);

uint8_t speed = 0;
bool direction = 1;

// Sample time
uint32_t loopTime = 10;
uint32_t time = 0;

volatile int32_t cnt = 0, oldCnt=0;

IFX007TMotorControl MyMotor = IFX007TMotorControl();

void encoder();

void setup() {
  Setpoint = 10000;
  myPID.SetOutputLimits(-255, 255);
  myPID.SetSampleTimeUs(loopTime * 1000);
  //apply PID gains
  myPID.SetTunings(Kp, Ki, Kd);
  //turn the PID on
  myPID.SetMode(myPID.Control::automatic);

  pinMode(encB, INPUT);
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(encA), encoder, RISING );
  MyMotor.begin();
}

void loop() {
  while(millis()-time < loopTime){}
  time = millis();
  Input = cnt;  // pozicija
  //Input = cnt - oldCnt;  // hitrost
  oldCnt = cnt;
  myPID.Compute();
  Serial.print(Input);
  Serial.print(" ");
  Serial.println(Output);
  if(Output < 0){
    direction = false;
    speed = abs(Output);
  }
  else {
    direction = true;
    speed = Output;
  }
  MyMotor.setBiDirMotorSpeed(direction, speed);

}

void encoder(){
  if(digitalRead(encB) == HIGH)
    cnt+=1;
  else 
    cnt-=1;
}