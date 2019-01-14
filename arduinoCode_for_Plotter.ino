
#include <Wire.h>
#include <AccelStepper.h>
#include <Adafruit_MotorShield.h>
#include <Servo.h>

const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output

//keep track of where the virtual mouse is
int xLoc = 0;
int yLoc = 0;

//Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_MotorShield AFMS;

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #1 & #2
Adafruit_StepperMotor *stepperLeft = AFMS.getStepper(200, 1);
Adafruit_StepperMotor *stepperRight = AFMS.getStepper(200, 2);

Servo myServo;

void forwardLeft(){
  //stepperLeft->step(50, BACKWARD, SINGLE);
  stepperLeft->onestep(BACKWARD, SINGLE);
}

void forwardRight(){
  //stepperRight->step(50, BACKWARD, SINGLE);
  stepperRight->onestep(BACKWARD, SINGLE);
}

void backwardLeft(){
  //stepperLeft->step(50, FORWARD, SINGLE);
  stepperLeft->onestep(FORWARD, SINGLE);
}

void backwardRight(){
  //stepperRight->step(50, FORWARD, SINGLE);
  stepperRight->onestep(FORWARD, SINGLE);
}

AccelStepper leftStep(forwardLeft, backwardLeft);
AccelStepper rightStep(forwardRight, backwardRight);

int xRead;
int yRead;
int servoisUp = 1;
int moveServ;

void setup(){
  AFMS.begin();  // create with the default frequency 1.6KHz
  Serial.begin(9600);

  pinMode(SW_pin, INPUT);
  pinMode(2, INPUT);
  digitalWrite(SW_pin, HIGH);

  myServo.attach(9);

  stepperLeft->setSpeed(200);  // 10 rpm
  stepperRight->setSpeed(200);

  myServo.write(90);
  

}


                    //================ MOTOR COMBINATIONS ================\\

void loop(){
  if (digitalRead(2) != 1)

  Serial.print("Button: ");
  Serial.println(moveServ);

  if (moveServ == 0){
    if (servoisUp == 1){
      myServo.write(5);
      servoisUp = 0;
    }
    else if (servoisUp == 0){
      myServo.write(90);
      servoisUp = 1;
    }
  }
//  else if (moveServ == 0 && servoisUp == 0){
//    myServo.write(90);
//    servoisUp = 1;
//  }




//  if (analogRead(4) < 950){
//    myServo.write(90);
//  }
//  if (analogRead(4) > 950){
//    myServo.write(20);
//  }
  
//  Serial.print("Switch:  ");
//  Serial.println(digitalRead(SW_pin));
//  Serial.print("\n");
//  Serial.print("X-axis: ");
//  Serial.print(analogRead(X_pin));
//  Serial.print("\n");
//  Serial.print("Y-axis: ");
//  Serial.println(analogRead(Y_pin));
//  Serial.print("\n\n");
  //delay(200);

//read direction and magnitude
  xRead = analogRead(X_pin);
  yRead = analogRead(Y_pin);

  //NORTHWEST
 if (xRead<150 && yRead<150){
  stepperLeft->step(1, FORWARD, SINGLE);
 }

 //NORTH
 if (xRead <= 600 && xRead >= 400){
  if (yRead<= 50){
    stepperLeft->step(1, FORWARD, SINGLE);
    stepperRight->step(1, FORWARD, SINGLE);
  }
 }

 //NORTHEAST
 if (xRead >= 850 && yRead <= 150){
//  leftStep.moveTo(1);
//    rightStep.moveTo(1);
//    leftStep.run();
//    rightStep.run();
//    
//  rightStep.moveTo(-100);
//  rightStep.run();
  stepperRight->step(1, FORWARD, SINGLE);
 }

 //EAST
 if (xRead >= 950){
  if (yRead >= 400 && yRead <= 600){
//    leftStep.moveTo(1);
//    rightStep.moveTo(1);
//    leftStep.run();
//    rightStep.run();
//    
//    leftStep.moveTo(100);
//    rightStep.moveTo(-100);
//    leftStep.run();
//    rightStep.run();
    stepperLeft->step(1, BACKWARD, SINGLE);
    stepperRight->step(1, FORWARD, SINGLE);
  }
 }

 //SOUTHEAST
 if (xRead >= 850 && yRead >= 850){
//  leftStep.moveTo(1);
//    rightStep.moveTo(1);
//    leftStep.run();
//    rightStep.run();
//    
//  leftStep.moveTo(100);
//  leftStep.run();
    stepperLeft->step(1, BACKWARD, SINGLE);
 }

 //SOUTH
 if (xRead <= 600 && xRead >= 400){
  if (yRead >= 850){
//    leftStep.moveTo(1);
//    rightStep.moveTo(1);
//    leftStep.run();
//    rightStep.run();
//    
//    leftStep.moveTo(100);
//    rightStep.moveTo(100);
//    leftStep.run();
//    rightStep.run();
    stepperLeft->step(1, BACKWARD, SINGLE);
    stepperRight->step(1, BACKWARD, SINGLE);
  }
 }

 //SOUTHWEST
 if (xRead <= 150 && yRead >= 850){
//  leftStep.moveTo(1);
//    rightStep.moveTo(1);
//    leftStep.run();
//    rightStep.run();
//    
//  rightStep.moveTo(100);
//  rightStep.run();
    stepperRight->step(1, BACKWARD, SINGLE);
 }

 //WEST
 if (xRead <= 150){
  if (yRead <= 600 && yRead >= 400){
//    leftStep.moveTo(1);
//    rightStep.moveTo(1);
//    leftStep.run();
//    rightStep.run();
//    
//    leftStep.moveTo(-100);
//    rightStep.moveTo(100);
//    leftStep.run();
//    rightStep.run();
    stepperLeft->step(1, FORWARD, SINGLE);
    stepperRight->step(1, BACKWARD, SINGLE);
  }
 }

  //now adjust the virtual mouse to it's new location
//  xLoc += (xRead-500)/500;
//  if(xLoc < -400){
//    xLoc = -400;
//  } else if (xLoc > 400) {
//    xLoc = 400; 
//  }
//
//  yLoc += (yRead-500)/500;
//  if(yLoc < -400){
//    yLoc = -400;
//  } else if (yLoc > 400) {
//    yLoc = 400; 
//  }

//  Serial.println(yLoc);
//  Serial.println(xLoc);
//
//  Serial.println(" ");

//pythagoras!

//left motor = sqrt( xLoc^2 + ( YTotal - yLoc)^2)
//right motor = sqrt( (XTotal - xLoc)^2 + (YTotal - yLoc) ^2)
//  int lMpos = sqrt((sq(xLoc)) + (sq(800-yLoc)));
//  int rMpos = sqrt((sq(800-xLoc)) + (sq(800-yLoc)));

//  xLoc = 0;
//  yLoc = 0;
//  
//  int YTotal = 0;
//  int XTotal = 0;
//
//  int x2 = (xRead-500)/500;
//  int y2 = (yRead-500)/500;

//  float a1 = sqrt(sq(xLoc) + sq(YTotal-yLoc));
//  float a2 = sqrt(sq(x2) + sq(YTotal-y2));
//  float b1 = sqrt(sq(XTotal-xLoc) + sq(YTotal-yLoc));
//  float b2 = sqrt(sq(XTotal-x2) + sq(YTotal-y2));

  

//  Serial.println(a1);
//  Serial.println(a2);
//  Serial.println(b1);
//  Serial.println(b2);
//  Serial.println(" ");
//  Serial.println(x2);
//  Serial.println(y2);
//  Serial.println(" ");
//  Serial.println(xLoc);
//  Serial.println(yLoc);
  //delay(500);
  
  

  //move to places
//  leftStep.moveTo(-1000);
//  rightStep.moveTo(1000);


  //adjust x and y Reads so that motors arent constantly running
//  if (xRead >= 498 && xRead <= 505){
//    xRead = 500;
//  }
//  if (yRead >= 498 && yRead <= 505){
//    yRead = 500;
//  }
//
//  Serial.println(lMpos);
//  Serial.println(rMpos);
//  //======================only move if not in resting=============
//  if(xRead != 500 && yRead != 500){
//      leftStep.run();
//      rightStep.run();
//  }

}


