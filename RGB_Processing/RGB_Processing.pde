import processing.serial.*;  //<>//

Serial vmesnik;
short index=1;
float napetost, yVal, oldyVal=0;
char [] data = new char[6];
int xPos = 0;
String message = new String();
int cnt = 0;
String[] list = {" ", " "," ", " ", " "," "};

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
    text(list[0], 40, 120); 
}

void serialEvent(Serial vmesnik) {
  if (vmesnik.available() > 0)
  {
    char ch = vmesnik.readChar();
    
    if (ch == '#')
    {  
      list = split(message, ',');
      println(message);
      message="";
    }
    else {
      message += ch;
    }
  }
}
