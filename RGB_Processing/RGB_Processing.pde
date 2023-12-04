import processing.serial.*;  //<>//

Serial vmesnik;
short index=1;
float napetost, yVal, oldyVal=0;
char [] data = new char[6];
int xPos = 0;
String message = new String();
int cnt = 0;
float Kp, Ki, Kd, Setpoint, Input, Output;

void setup() {
  size(500, 200);
  String vrata = Serial.list()[index];
  println((Object[])Serial.list());
  println(vrata);
  vmesnik = new Serial(this, vrata, 115200);
  background(200);
  
}

void draw() {
    background(200);

}

void serialEvent(Serial vmesnik) {
  if (vmesnik.available() > 0)
  {
    char ch = vmesnik.readChar();
    
    if (ch == '#')
    {  
      float[] list = float(split(message, ','));
      Kp = list[0];
      Ki = list[1];
      Kd = list[2];
      Setpoint = list[3];
      Input = list[4];
      Output = list[5];
      println(message);
      message="";
    }
    else {
      message += ch;
    }
  }
}
