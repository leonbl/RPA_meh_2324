#include <Arduino.h>
#define SDI 8
#define CLK 7
#define LATCH 4
#define CLK_DELAY (10)

void toggleCLK(void);
void writeToDisp(uint8_t dispNum, uint8_t dispVal);
void toggleLatchCLK(void);

void setup() {
  pinMode(SDI, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(LATCH, OUTPUT);
}

void loop() {
  writeToDisp(0xff,0x00);
  delay(1000);
}

void toggleCLK(void){
  digitalWrite(CLK, LOW);
  delay(CLK_DELAY);
  digitalWrite(CLK, HIGH);
  delay(CLK_DELAY);
}

void toggleLatchCLK(void){
  digitalWrite(LATCH, LOW);
  delay(CLK_DELAY);
  digitalWrite(LATCH, HIGH);
  delay(CLK_DELAY);
}

void writeToDisp(uint8_t dispNum, uint8_t dispVal){
  for(int n=0; n<8; n++){
    digitalWrite(SDI, (dispVal & 0x01));
    toggleCLK();
    dispVal = dispVal >> 1;
  }
  for(int n=0; n<8; n++){
    digitalWrite(SDI, (dispNum & 0x01));
    toggleCLK();
    dispNum = dispNum >> 1;
  }
  toggleLatchCLK();
}