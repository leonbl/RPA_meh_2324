import processing.serial.*;

Serial vmesnik;
short index=1;
String napetost;

void setup(){
  size(80,60);
  String vrata = Serial.list()[index];
  println((Object[])Serial.list());
  println(vrata);
  vmesnik = new Serial(this,vrata,9600);
}

void draw(){
}

void serialEvent(Serial vmesnik){
  if(vmesnik.read() == '#'){ //<>//
    napetost = vmesnik.readStringUntil('\n');
    println(float(napetost));
  }
}
