#include <Arduino.h>
#include <QuickPID.h>

#define PIN_INPUT A1
#define PIN_OUTPUT 5

HardwareTimer *Tim1;
TIM_TypeDef *I1;
uint32_t c1, pwm = 0;
volatile bool computeNow = false;

// Define Variables we'll be connecting to
float Setpoint, Input, Output;
float Kp = 2, Ki = 5, Kd = 1;
// Specify PID links
QuickPID myPID(&Input, &Output, &Setpoint);

void prekinitev_PID();

void setup()
{
  Serial.begin(115200);
  Input = analogRead(PIN_INPUT);
  Setpoint = 900;
  // apply PID gains
  myPID.SetTunings(Kp, Ki, Kd);

  I1 = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(PIN_OUTPUT), PinMap_PWM);
  c1 = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(PIN_OUTPUT), PinMap_PWM));
  Tim1 = new HardwareTimer(I1);
  Tim1->setMode(c1, TIMER_OUTPUT_COMPARE_PWM1, PIN_OUTPUT);
  Tim1->resume();

  uint32_t perioda = 100000;
  TIM_TypeDef *PeriodTimer = TIM3;
  HardwareTimer *casovnik = new HardwareTimer(PeriodTimer);
  casovnik->setOverflow(perioda, MICROSEC_FORMAT);
  casovnik->attachInterrupt(prekinitev_PID);
  casovnik->resume();

  // turn the PID on
  myPID.SetMode(myPID.Control::automatic);
}

void prekinitev_PID()
{
  computeNow = true;
}

void loop()
{
  if (computeNow)
  {
    Input = analogRead(PIN_INPUT);
    myPID.Compute();
    long pwm = map(Output, 0, 255, 0, 100);
    Tim1->setCaptureCompare(c1, pwm, PERCENT_COMPARE_FORMAT);
    Serial.print(Input);
    Serial.print(" ");
    Serial.println(pwm);
    computeNow = false;
  }
}