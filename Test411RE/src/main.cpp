#include <Arduino.h>

#define pin1 9
#define pin2 10
#define pin3 11
HardwareTimer *Tim1, *Tim2, *Tim3;
TIM_TypeDef *I1, *I2, *I3;
uint32_t c1, c2, c3, procent = 0;

void setup()
{

  I1 = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(pin1), PinMap_PWM);
  c1 = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(pin1), PinMap_PWM));
  Tim1 = new HardwareTimer(I1);
  Tim1->setMode(c1, TIMER_OUTPUT_COMPARE_PWM1, pin1);
  Tim1->resume();

  I2 = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(pin2), PinMap_PWM);
  c2 = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(pin2), PinMap_PWM));
  Tim2 = new HardwareTimer(I2);
  Tim2->setMode(c2, TIMER_OUTPUT_COMPARE_PWM1, pin2);
  Tim2->resume();

  I3 = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(pin3), PinMap_PWM);
  c3 = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(pin3), PinMap_PWM));
  Tim3 = new HardwareTimer(I3);
  Tim3->setMode(c3, TIMER_OUTPUT_COMPARE_PWM1, pin3);
  Tim3->resume();

}


void loop()
{
  procent++;
  Tim1->setCaptureCompare(c1, procent, PERCENT_COMPARE_FORMAT);
  Tim2->setCaptureCompare(c2, procent, PERCENT_COMPARE_FORMAT);
  Tim3->setCaptureCompare(c3, procent, PERCENT_COMPARE_FORMAT);
  delay(10);
  if(procent==100) procent = 0;
}