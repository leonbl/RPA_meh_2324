#include <Arduino.h>
#define SDI 8
#define CLK 7
#define LATCH 4
#define CLK_DELAY (1)

void toggleCLK(void);
void writeToDisp(uint8_t dispNum, uint8_t dispVal);
void toggleLatchCLK(void);
void display(void);

uint8_t number[10] = {0x03,0x9f,0x25,0x0d,0x99,0x49,0x41,0x1f,0x01,0x19};
uint8_t disp_num[4] = {1,3,5,7};

void setup() {
  pinMode(SDI, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(LATCH, OUTPUT);
}

void loop() {
  uint32_t cas = millis();
  while((millis()-cas)<100){
    display();
  }
  disp_num[0]++;
  if(disp_num[0]>=9) disp_num[0]=0;
}

void toggleCLK(void){
  digitalWrite(CLK, LOW);
  digitalWrite(CLK, HIGH);
}

void toggleLatchCLK(void){
  digitalWrite(LATCH, LOW);
  digitalWrite(LATCH, HIGH);
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

void display(void){
  writeToDisp(0x80,number[disp_num[0]]);
  writeToDisp(0x40,number[disp_num[1]]);
  writeToDisp(0x20,number[disp_num[2]]);
  writeToDisp(0x10,number[disp_num[3]]);
}