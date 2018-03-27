#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Ultrasonic.h>

#define ECHOPIN 10
#define TRIGPIN 9
Ultrasonic ultrasonic(11);
Ultrasonic ultrasonic2(12);

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);


    long RangeInInches;
    long RangeInInches2;
    float distance;

    int realigning = 0;

    bool moving = true;
    int direct = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    pinMode(ECHOPIN, INPUT);
    pinMode(TRIGPIN, OUTPUT);

    AFMS.begin(); 
    
    myMotor->setSpeed(80); //right
    myMotor2->setSpeed(80);
    myMotor->run(FORWARD);
    myMotor2->run(FORWARD);
    myMotor->run(RELEASE);
    myMotor->run(RELEASE);

}
void loop()
{    
    detection();

    if(moving == true){
      if(direct < 0){
        direct++;
        myMotor->setSpeed(80); //right
        myMotor2->setSpeed(150);
      }
      if(direct > 0){
        direct--;
        myMotor->setSpeed(150);//right
        myMotor2->setSpeed(80);
      }
      if(direct == 0){
        myMotor->setSpeed(80); //right
        myMotor2->setSpeed(80);
      }
      if((RangeInInches <= 3 || RangeInInches2 <=3 || distance <= 3)){
        digitalWrite(LED_BUILTIN, HIGH);
        myMotor->run(RELEASE);
        myMotor2->run(RELEASE);
        moving = false;
      }
      else{
        digitalWrite(LED_BUILTIN, LOW);
        myMotor->run(BACKWARD);
        myMotor2->run(BACKWARD);
        moving = true;
      }
    }
    if(RangeInInches > 3 && RangeInInches2 > 3 && distance > 3){
          moving = true;
    }
    if(moving == false){
        if(RangeInInches2 >= RangeInInches){
          myMotor->run(FORWARD);
          myMotor2->run(BACKWARD);
          direct ++;
        }
        else{
          myMotor2->run(FORWARD);
          myMotor->run(BACKWARD);
          direct --;
        }
        
    }
}

void detection(){
    ultrasonic.DistanceMeasure();
    ultrasonic2.DistanceMeasure();
    RangeInInches = ultrasonic.microsecondsToInches();
    RangeInInches2 = ultrasonic2.microsecondsToInches();
    digitalWrite(TRIGPIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGPIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGPIN, LOW);
    distance = pulseIn(ECHOPIN, HIGH);
    distance= distance/58;
    distance= distance/2.54;
}




