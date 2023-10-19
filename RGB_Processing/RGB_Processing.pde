import processing.serial.*;  //<>//

Serial vmesnik;
short index=1;
float napetost, yVal, oldyVal=0;
char [] data = new char[6];
int xPos = 0;

void setup() {
  size(500, 200);
  String vrata = Serial.list()[index];
  println((Object[])Serial.list());
  println(vrata);
  vmesnik = new Serial(this, vrata, 9600);
  background(200);
}

void draw() {
  yVal = map(napetost, 5.0, 0.0, 20, 180);
  //point(xPos, yVal);
  line(xPos,oldyVal,xPos+1,yVal);
  xPos++;
  oldyVal = yVal;
  if (xPos > width)
  {
    xPos = 0;
    background(200);
    color(#FF7017);
  }
}

void serialEvent(Serial vmesnik) {
  if (vmesnik.available() > 5)
  {
    if (vmesnik.read() == '#')
    {
      for (int n = 0; n<4; n++)
      {
        data[n] = char(vmesnik.read());
      }
      String nap = new String(data);
      napetost = float(nap);
      println(napetost);
    }
  }
}
