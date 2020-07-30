#include "MotorController.h"

Servo xServo, yServo;

void startMotors(){
  xServo.attach(9);
  yServo.attach(10);
}

void setMotors(float x, float y){
  if(x>180) x-=360;
  else if(x<-180) x+=360;
  xServo.writeMicroseconds(500+(90-x*1.3)*11.11);
  yServo.writeMicroseconds(500+(90-y*1.1)*11.11);
}
