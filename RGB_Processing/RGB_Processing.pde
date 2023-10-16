import processing.serial.*;

Serial vmesnik;
short index=1;
int r=100,b=50,g=30;

void setup(){
  size(800,600);
  String vrata = Serial.list()[index];
  println((Object[])Serial.list());
  println(vrata);
  vmesnik = new Serial(this,vrata,9600);
}

void draw(){
  background(r,g,b);
}

void mousePressed(){
  posljiSporocilo();
}

void posljiSporocilo(){
  r = (int)random(255);
  g = (int)random(255);
  b = (int)random(255);
  println(r+" "+g+" "+b);
  vmesnik.write('#');
  vmesnik.write(str(r));
  vmesnik.write(',');
  vmesnik.write(str(g));  
  vmesnik.write(',');
  vmesnik.write(str(b));
}
