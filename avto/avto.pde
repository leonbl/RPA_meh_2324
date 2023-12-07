PImage myImage; //<>//
boolean obrni = true;
int cnt = 0;
float heading;
float posX, posY;
float h;
Vehicle v = new Vehicle(60, 60);

// PID1
float R1 = 16; // Referenca - željena oddaljenost od desne stene
float e1, et1, es1;
float Kp1 = -0.05;
float Ki1 = -0.01;
float Kd1 = -0.00;

// PID2
float R2 = 70; // Referenca - željena oddaljenost spredaj
float e2, et2, es2;
float Kp2 = -0.1;
float Ki2 = -0.2;
float Kd2 = -0.00;

float umax = 2.0;
float umin = -2.0;
float uimax = 60.0;
float uimin = -60.0;
float T = 0.02;
float kot = 0;

void setup() {
  size(600, 600);
  myImage = loadImage("labirint2.jpg");

  heading = v.getHeading();
  //v.setHeading(90);
  v.printHeading();
}

void draw() {
  background(255);
  image(myImage, 0, 0);

  PVector p = new PVector();
  PVector s = v.distanceV(); // enotin vektor v smeri vožnje
  PVector d = v.distanceV();
  d.rotate(PI/2);            // enotin vektor pravokoten na smer vožnje

  // merjenje razdalje spredaj
  p = v.position.copy();
  p.add(s);
  int dFront=0;
  while (get((int)p.x, (int)p.y)!=0xff000000) {
    point(p.x, p.y);
    p.add(s);
    //println(d.x+" "+d.y);
    dFront++;
    if (dFront >= R2) break;
  }

  // merjenje razdalje desno
  p = v.position.copy();
  p.add(d);
  int dRight=0;
  while (get((int)p.x, (int)p.y)!=0xff000000) {
    point(p.x, p.y);
    p.add(d);
    dRight++;
    if (dRight > 70) break;
  }

  // izračun PID za desni senzor
  e1 = R1 - dRight;
  float u1 = calcPID(e1, Kp1, Ki1, Kd1, es1, et1);
  v.setHeading(u1);
  et1 = e1;
  
  // izračun PID za prednji senzor
  e2 = R2 - dFront ;
  float u2 = calcPID(e2, Kp2, Ki2, Kd2, es2, et2);
  v.setHeading(u2);
  et2 = e2;

  v.update();
  v.display();

  text("dRight: ", 350, 120);
  text(dRight, 400, 120);
  text("u1: ", 450, 120);
  text(u1, 470, 120);
  text("dFront: ", 350, 130);
  text(dFront, 400, 130);
  text("u2: ", 450, 130);
  //text(u2, 470, 130);
}

float calcPID(float e, float Kp, float Ki, float Kd, float es, float et){
  float up = Kp*e; 
  es = es + e;
  float ui = Ki*T*es;
  
  // prispevek integralnega člena omejimo
  if(ui>uimax) ui = uimax;
  if(ui<uimin) ui = uimin;
  float ud = Kd*(e-et)/T;
  float u = up + ui + ud;
  
  // omejimo celoten izračun
  // pazi na to vrednost!!!
  if(u>umax) u = umax;
  if(u<umin) u = umin;
  return  u;
}
