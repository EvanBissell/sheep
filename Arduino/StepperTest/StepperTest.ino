// AFMotor_MultiStepper.pde
// -*- mode: C++ -*-
//
// Control both Stepper motors at the same time with different speeds
// and accelerations. 
// Requires the AFMotor library (https://github.com/adafruit/Adafruit-Motor-Shield-library)
// Caution, does not work with Adafruit Motor Shield V2
// See https://github.com/adafruit/Adafruit_Motor_Shield_V2_Library 
// for examples that work with Adafruit Motor Shield V2.
#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"


#define ECHOPINFR 1
#define TRIGPINFR 0
#define ECHOPINFL 12
#define TRIGPINFL 11
#define ECHOPIN 10
#define TRIGPIN 9


// two stepper motors one on each port
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_StepperMotor *motorL = AFMS.getStepper(1000, 1);
Adafruit_StepperMotor *motorR = AFMS.getStepper(1000, 2);
long RangeInInchesL;
long RangeInInchesR;

int realigning = 0;
bool moving = true;
int direct = 0;
// you can change these to DOUBLE or INTERLEAVE or MICROSTEP!
// wrappers for the first motor!
void forwardstep1() {  
  motorL->onestep(BACKWARD, SINGLE);
}
void backwardstep1() {  
  motorL->onestep(FORWARD, SINGLE);
}
// wrappers for the second motor!
void forwardstep2() {  
  motorR->onestep(BACKWARD, SINGLE);
}
void backwardstep2() {  
  motorR->onestep(FORWARD, SINGLE);
}
// Motor shield has two motor ports, now we'll wrap them in an AccelStepper object
AccelStepper stepper1(forwardstep1, backwardstep1);
AccelStepper stepper2(forwardstep2, backwardstep2);
void setup()
{  
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    pinMode(ECHOPIN, INPUT);
    pinMode(TRIGPIN, OUTPUT);
    
    pinMode(ECHOPINFL, INPUT);
    pinMode(TRIGPINFL, OUTPUT);

    pinMode(ECHOPINFR, INPUT);
    pinMode(TRIGPINFR, OUTPUT);

    AFMS.begin();
    
    motorL->setSpeed(200);
    motorR->setSpeed(200);
    stepper1.setMaxSpeed(400.0);
    stepper1.setAcceleration(100.0);
    stepper1.moveTo(5000);
    
    stepper2.setMaxSpeed(400.0);
    stepper2.setAcceleration(100.0);
    stepper2.moveTo(5000);
    
}
void loop()
{
    /*digitalWrite(TRIGPIN, LOW); //for Front Center Sensor
    delayMicroseconds(2);
    digitalWrite(TRIGPIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGPIN, LOW);
    float distance = pulseIn(ECHOPIN, HIGH);
    distance= distance/58;
    distance= distance/2.54;
   */
/*    
    digitalWrite(TRIGPINFL, LOW); //for Front Left Sensor
    delayMicroseconds(2);
    digitalWrite(TRIGPINFL, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGPINFL, LOW);
    float RangeInInchesL = pulseIn(ECHOPINFL, HIGH);
    RangeInInchesL= RangeInInchesL/58;
    RangeInInchesL= RangeInInchesL/2.54;

    digitalWrite(TRIGPINFR, LOW); //for Front Right Sensor
    delayMicroseconds(2);
    digitalWrite(TRIGPINFR, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGPINFR, LOW);
    float RangeInInchesR = pulseIn(ECHOPINFR, HIGH);
    RangeInInchesR= RangeInInchesR/58;
    RangeInInchesR= RangeInInchesR/2.54;
*/
   /* if(moving == true){
      if((RangeInInchesR <= 3 || RangeInInchesL <=3 || distance <= 3)){
        digitalWrite(LED_BUILTIN, HIGH);
        stepper1.moveTo(0);
        stepper2.moveTo(0);

        
        moving = false;
      } 

      */
      /*
 if(moving == true){
    if( distance <= 3){
        digitalWrite(LED_BUILTIN, HIGH);
        stepper1.moveTo(-10000);
        stepper2.moveTo(-10000);

      }

    else{
        stepper1.moveTo(10000);
        stepper2.moveTo(10000);
    }
}
*/
/*
  
    if(moving == false){
        if(RangeInInchesL >= RangeInInchesR){
          
          backwardstep1();
          forwardstep2();
          direct ++;
        }
        else{
          forwardstep1();
          backwardstep2();
          direct --;
        }
        if(RangeInInchesR > 3 && RangeInInchesL > 3 && distance > 3){
          moving = true;
        }
    }
    if(direct < 0 && moving == true){
      direct++;
      motorR->setSpeed(80); //right
      motorL->setSpeed(150);
    }
    if(direct > 0 && moving == true){
      direct--;
      motorR->setSpeed(150); //right
      motorL->setSpeed(80);
    }
   
    if(direct == 0){
      motorR->setSpeed(250); 
      motorL->setSpeed(250);
    }
     */
    
    // Change direction at the limits
   /* if (stepper1.distanceToGo() == 0)
        stepper1.moveTo(-stepper1.currentPosition());
    if (stepper2.distanceToGo() == 0)
    stepper2.moveTo(-stepper1.currentPosition());
    stepper1.run();
    stepper2.run();
    */
   stepper1.runSpeed();
   stepper2.runSpeed();
}
