#ifndef UTILS_H
#define UTILS_H

#include <NewServo.h>
#include <NewPing.h>
#include <PLab_ZumoMotors.h>
#include <ZumoReflectanceSensorArray.h>
#include <PLab_ZumoMotors.h>

#include "Arduino.h"
#include "Pins.h"


// Tilstander
#define ATTACK 0
#define SEARCH 1
#define BORDER_FLEE 2

int REVERSE_SPEED  = 400; // 0 is stopped, 400 is full speed
int TURN_SPEED     = 300;
int FORWARD_SPEED  = 250;

void turn(PLab_ZumoMotors &plab_Motors, int spd, int degree) {
  int leftSpeed;
  int rightSpeed;
  if (degree < 0) {
    int leftSpeed = spd*cos(degree);
    int rightSpeed = spd;
  } else {
    int leftSpeed = spd;
    int rightSpeed = spd*cos(degree);
  }
  plab_Motors.setSpeeds(leftSpeed, rightSpeed);
}

void stepServo(NewServo &myServo, int& degreesServo, int& degreesStep) {
   degreesServo = degreesServo + degreesStep;
   if (degreesServo > 180) {
       degreesStep = -degreesStep;
       degreesServo = 180;
   } else if (degreesServo < 0) {
       degreesStep = -degreesStep;
       degreesServo = 0;
   } 
   myServo.write(degreesServo);
}

float sonarDistance(NewPing& sonar) {
  // Gjør ett ping, og beregn avstanden
  unsigned int time = sonar.ping();
  float distance = sonar.convert_cm(time);
  if (distance == 0.0) { // sonar gives zero when outside range
    // Turn off LED and just go forward
    digitalWrite(ledPin,LOW); 
   } else {
    digitalWrite(ledPin,HIGH);
   }
   return distance;
}


void borderFlee(PLab_ZumoMotors &plab_Motors, int borderStatus) {
  int randAngle = random(100, 150); // Bør settes av borderStatus
  if (borderStatus == 1 || borderStatus == 2) {
    plab_Motors.backward(REVERSE_SPEED, 10);
    plab_Motors.turnRight(TURN_SPEED,randAngle);
  } else if (borderStatus == 3 || borderStatus == 4) {
    plab_Motors.backward(REVERSE_SPEED, 10);
    plab_Motors.turnLeft(TURN_SPEED,randAngle);
  }
}

#endif
