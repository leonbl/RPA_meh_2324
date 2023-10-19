#include <Arduino.h>
void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print('#');
  Serial.println((float)analogRead(A0)*5.0/1023.0);
  delay(100);
}
