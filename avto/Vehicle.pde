class Vehicle {
  
  PVector position;
  PVector velocity;
  PVector acceleration;
  float rx, ry;
  float maxforce;    // Maximum steering force
  float maxspeed;    // Maximum speed

  Vehicle(float x, float y) {
    acceleration = new PVector(0,0);
    velocity = new PVector(1,0);
    position = new PVector(x,y);
    rx = 8;
    ry = 12;
    maxspeed = 1;
    maxforce = 0.1;
  }

  // Method to update position
  void update() {
    // Update velocity
    velocity.add(acceleration);
    // Limit speed
    velocity.limit(maxspeed);
    position.add(velocity);
    // Reset accelerationelertion to 0 each cycle
    acceleration.mult(0);
  }

  PVector distanceV(){
    PVector d = new PVector();
    d = velocity.copy();
    d.normalize();
    return d;
  }
  
  float getHeading(){
     return velocity.heading()*180/PI;
  }
  
  void setHeading(float angle){
    velocity.rotate(angle*PI/180);
  }
  
  void printHeading(){
    println(velocity.heading()*180/PI); 
  }

  void steer(float theta) {
    acceleration.add(velocity);
  }
  
  void display() {
    // Draw a triangle rotated in the direction of velocity
    float theta = velocity.heading() + PI/2;
    fill(127);
    stroke(0);
    strokeWeight(1);
    pushMatrix();
    translate(position.x,position.y);
    rotate(theta);
    beginShape();
    vertex(rx, ry);
    vertex(rx, -ry);
    vertex(0, -ry-5);
    vertex(-rx, -ry);
    vertex(-rx, ry);
    endShape(CLOSE);
    popMatrix();
  }
}
