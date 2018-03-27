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
#include <NewPing.h>



#define ECHO_PIN 12
#define TRIGGER_PIN 13                      
#define MAX_DISTANCE 20
unsigned int distance;
unsigned int microseconds;
unsigned int readcount;
unsigned int pingSpeed = 50; // How frequently are we going to send out a ping (in milliseconds). 50ms would be 20 times a second.
unsigned long pingTimer;     // Holds the next ping time.


// two stepper motors one on each port
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_StepperMotor *motor1 = AFMS.getStepper(1000, 1);
Adafruit_StepperMotor *motor2 = AFMS.getStepper(1000, 2);
// you can change these to DOUBLE or INTERLEAVE or MICROSTEP!
// wrappers for the first motor!
void forwardstep1() {  
  motor1->onestep(BACKWARD, SINGLE);
}
void backwardstep1() {  
  motor1->onestep(FORWARD, SINGLE);
}
// wrappers for the second motor!
void forwardstep2() {  
  motor2->onestep(BACKWARD, SINGLE);
}
void backwardstep2() {  
  motor2->onestep(FORWARD, SINGLE);
}
// Motor shield has two motor ports, now we'll wrap them in an AccelStepper object
AccelStepper stepper1(forwardstep1, backwardstep1);
AccelStepper stepper2(forwardstep2, backwardstep2);
void setup()
{  
    Serial.begin(115200);
   // pingTimer = millis(); // Start now.
    AFMS.begin();
    stepper1.setMaxSpeed(200.0);
    stepper1.setAcceleration(300.0);
    stepper1.moveTo(1000000);
    stepper2.setMaxSpeed(300.0);
    stepper2.setAcceleration(300.0);
    stepper2.moveTo(1000000);


   
    
}
void loop()
{
  if (millis() >= pingTimer) {   // pingSpeed milliseconds since last ping, do another ping.
    pingTimer += pingSpeed;      // Set the next ping time.
    sonar.ping_timer(echoCheck); // Send out the ping, calls "echoCheck" function every 24uS where you can check the ping status.
  }


  if(distance < 10){
     stepper1.stop();
      stepper2.stop();
  }
  else{
    stepper2.moveTo(1000000);
    stepper1.moveTo(1000000);
    stepper1.run();
    stepper2.run();
  }

}
void echoCheck() { // Timer2 interrupt calls this function every 24uS where you can check the ping status.
  // Don't do anything here!
  if (sonar.check_timer()){ // This is how you check to see if the ping was received.
    // Here's where you can add code.
    microseconds = sonar.ping_result;
    distance = microseconds/US_ROUNDTRIP_CM;
    Serial.print("Ping: ");
    Serial.print(distance);
    Serial.println(" cm");

  }
  // Don't do anything here!
}



