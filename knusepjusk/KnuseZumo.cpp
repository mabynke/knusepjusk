#include "KnuseZumo.h"
//#include <NewPing.h>

// Noen viktige konstanter
const int sonarNumber = 50;         // Antall tall i arrayRing
const int newEnemyDetectedZeros = 4;
const int stillSeesEnemyZeros = 20;
const int forwardServoMargin = 5; // grader

KnuseZumo::KnuseZumo(NewPing &sonar, NewServo &servo) :
  sonar(sonar),
  myServo(servo), 
  sonarDistances(sonarNumber)
  {};


void KnuseZumo::sendSonarPing() {
  unsigned int time = sonar.ping();
  sonarDistances.add(sonar.convert_cm(time));
}

void KnuseZumo::turnOnSpot(int _speed) {
  /*
   * Fart større enn 0: Svinger mot klokken
   * Fart mindre enn 0: Svinger med klokken
   */
   setLeftSpeed(-_speed);
   setRightSpeed(_speed);
}

void KnuseZumo::stepServo() {
  /*
   * Servoen roterer gitt ved 'degreesStep' og degreesServo
   */
   degreesServo = degreesServo + degreesStep;
   if (degreesServo > 180) {
       degreesStep = -degreesStep;
       degreesServo = 180;
   } else if (degreesServo < 0) {
       degreesStep = -degreesStep;
       degreesServo = 0;
   } 
   myServo.write(degreesServo - SERVO_OFFSET);
}

void KnuseZumo::setForwardServo() {
  /*
   * Gjør at servoen peker fremover
   */
  if (degreesServo < 90 - forwardServoMargin || degreesServo > 90 + forwardServoMargin) {
    degreesServo = 90;
    myServo.write(degreesServo - SERVO_OFFSET);
  }
}

void KnuseZumo::driveAndTurn(int _speed, int angle) {
  /*
   * Kjører og svinger samtidig. 
   * NB! Angle angir nødvendigvis ikke hvilken zumoen svinger. (Se implementering for detaljer)
   */
  int leftSpeed;
  int rightSpeed;
  if (angle < 0) {
    leftSpeed = _speed*cos(angle);
    rightSpeed = _speed;
  } else {
    leftSpeed = _speed;
    rightSpeed = _speed*cos(angle);
  }
  setSpeeds(leftSpeed, rightSpeed);
}

float KnuseZumo::sonarDistance() {
  sendSonarPing();
  return sonarDistances.getAverage();
}

boolean KnuseZumo::newEnemyDetected() {
  sendSonarPing();
  return !sonarDistances.isLastNDigit(newEnemyDetectedZeros, 0, 0);
}

boolean KnuseZumo::stillSeesEnemy() {
  sendSonarPing();
  return !sonarDistances.isLastNDigit(stillSeesEnemyZeros, 0, 0);
}

