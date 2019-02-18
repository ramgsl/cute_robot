#include <AFMotor.h> 
#include <Servo.h>    
#include <NewPing.h>

Servo servo;
NewPing sonar(A0, A1, 1000);
AF_DCMotor leftMotor(2, MOTOR12_8KHZ); 
AF_DCMotor rightMotor(1, MOTOR12_8KHZ); 

int pos = 0; 
int dist = 0;
int ldist = 0;
int rdist = 0;
int c = 0;

void setup() {
  Serial.begin(115200);
  servo.attach(10);  
  servo.write(70);
  moveFront();
}

void loop() {
  dist = readPing();
  if (dist<20) {
    moveBack();
    delay(500);
    rdist = lookRight();
    delay(1000);
    ldist = lookLeft();
    delay(1000);
    if (ldist >= rdist){
      moveLeft();
    }else{
      moveRight();
    }
  }
  moveFront();
}

int readPing() {
  delay(70);
  unsigned int uS = sonar.ping();
  int cm = uS/US_ROUNDTRIP_CM;
  return cm;
}

void moveFront() {
    leftMotor.run(FORWARD);
    rightMotor.run(FORWARD);
    for (c = 0; c < 150; c +=2) {
      leftMotor.setSpeed(c);
      rightMotor.setSpeed(c);
     }
    delay(300);
}

void moveBack() {
    leftMotor.run(BACKWARD);
    rightMotor.run(BACKWARD);
    delay(200);
}  

void moveRight() {
  leftMotor.run(FORWARD);
  rightMotor.run(BACKWARD);
  delay(300);
}

void moveLeft() {
  leftMotor.run(BACKWARD);
  rightMotor.run(FORWARD);
  delay(300);
}  

void moveStop() {
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
  delay(500);
}

int lookLeft() {
  int rdist = 0;
  moveStop();  
  for(pos = 70; pos >= 0; pos-=10){
    servo.write(pos);
    delay(50);
  }
  delay(1000);
  rdist = readPing();
  servo.write(70);
  return rdist;  
}

int lookRight() {
  int ldist = 0;
  moveStop();
  for(pos = 70; pos <= 140; pos+=10){
    servo.write(pos);
    delay(50);
  }
  delay(1000);
  ldist = readPing();
  servo.write(70);
  return ldist;  
}
