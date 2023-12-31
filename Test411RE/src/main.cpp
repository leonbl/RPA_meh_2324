#include <Arduino.h>
#include <QuickPID.h>

#define PIN_INPUT A1
#define PIN_OUTPUT 3

HardwareTimer *Tim1;
TIM_TypeDef *I1;
uint32_t c1, pwm = 0;

//Define Variables we'll be connecting to
double Setpoint, Input, Output;
double Kp = 2, Ki = 5, Kd = 1;
//Specify PID links
QuickPID myPID(&Input, &Output, &Setpoint);

void setup()
{
  Input = analogRead(PIN_INPUT);
  Setpoint = 100;
    //apply PID gains
  myPID.SetTunings(Kp, Ki, Kd);

  I1 = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(PIN_OUTPUT), PinMap_PWM);
  c1 = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(PIN_OUTPUT), PinMap_PWM));
  Tim1 = new HardwareTimer(I1);
  Tim1->setMode(c1, TIMER_OUTPUT_COMPARE_PWM1, PIN_OUTPUT);
  Tim1->resume();

    //turn the PID on
  myPID.SetMode(myPID.Control::automatic);
}


void loop()
{
  Input = analogRead(PIN_INPUT);
  myPID.Compute();
  Tim1->setCaptureCompare(c1, Output, PERCENT_COMPARE_FORMAT);
}