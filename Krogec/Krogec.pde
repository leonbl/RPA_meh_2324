float x=0,y=0, ySpeed=10,xSpeed=10;
void setup(){
  size(500,300);
}

void draw(){
  background(#0B8352);
  x += xSpeed;
  y += ySpeed;
  if(y>height || y<0) ySpeed *= -1;
  if(x>width || x<0) xSpeed *= -1;
  ellipse(x,y,100,100);
}
