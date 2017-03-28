#include "KnuseZumo.h"
//#include <NewPing.h>

// Noen viktige konstanter
const int sonarNumber = 50;         // Antall tall i arrayRing
const int newEnemyDetectedZeros = 4;
const int stillSeesEnemyZeros = 20;
const int forwardServoMargin = 5; // grader

KnuseZumo::KnuseZumo(NewPing &leftSonar, NewPing &rightSonar, NewServo &servo) :
  leftSonar(leftSonar),
  rightSonar(rightSonar),
  leftSonarDistances(sonarNumber),
  rightSonarDistances(sonarNumber)
  {};

void KnuseZumo::turnOnSpot(int _speed) {
  /*
   * Fart større enn 0: Svinger mot klokken
   * Fart mindre enn 0: Svinger med klokken
   */
   setLeftSpeed(-_speed);
   setRightSpeed(_speed);
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

void KnuseZumo::sendSonarPingLeft() {
  unsigned int time = leftSonar.ping();
  leftSonarDistances.add(leftSonar.convert_cm(time));
}

void KnuseZumo::sendSonarPingRight() {
  unsigned int time = rightSonar.ping();
  rightSonarDistances.add(rightSonar.convert_cm(time));
}

float KnuseZumo::leftSonarDistance() {
  sendSonarPing();
  return leftSonarDistances.getAverage();
}

float KnuseZumo::rightSonarDistance() {
  sendSonarPing();
  return rightSonarDistances.getAverage();
}

boolean KnuseZumo::newEnemyDetected() {
  sendSonarPingLeft();
  sendSonarPingRight();
  return !(leftSonarDistances.isLastNDigit(newEnemyDetectedZeros, 0, 0) && rightSonarDistances.isLastNDigit(newEnemyDetectedZeros, 0, 0));
}

boolean KnuseZumo::stillSeesEnemy() {
  sendSonarPingLeft();
  sendSonarPingRight();
  return !(leftSonarDistances.isLastNDigit(stillSeesEnemyZeros, 0, 0) && rightSonarDistances.isLastNDigit(stillSeesEnemyZeros, 0, 0));
}

