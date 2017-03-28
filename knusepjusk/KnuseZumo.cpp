#include "KnuseZumo.h"
//#include <NewPing.h>

// Noen viktige konstanter
const int sonarNumber = 50;         // Antall tall i arrayRing
const int newEnemyDetectedZeros = 4;
const int stillSeesEnemyZeros = 20;
const int forwardServoMargin = 5; // grader

KnuseZumo::KnuseZumo(NewPing &leftSonar, NewPing &rightSonar) :
  leftSonar(leftSonar),
  rightSonar(rightSonar),
  leftSonarDistances(sonarNumber),
  rightSonarDistances(sonarNumber)
  {};

boolean KnuseZumo::newEnemyDetected() {
  /*
   * Denne metoden burde kalles fra alle tilstandene utenom angrepstilstand(ene)
   * Metoden sender ping fra begge sonarene og 
   * returnerer 'true' hvis det har vært 'newEnemyDetectedZeros' ikke-null 
   * verdier fra minst en av sonarene
   */
  sendSonarPingLeft();
  sendSonarPingRight();
  return !(leftSonarDistances.isLastNDigit(newEnemyDetectedZeros, 0, 0) && rightSonarDistances.isLastNDigit(newEnemyDetectedZeros, 0, 0));
}

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

boolean KnuseZumo::stillSeesEnemy() {
  sendSonarPingLeft();
  sendSonarPingRight();
  return !(leftSonarDistances.isLastNDigit(stillSeesEnemyZeros, 0, 0) && rightSonarDistances.isLastNDigit(stillSeesEnemyZeros, 0, 0));
}

int KnuseZumo::sonarStatus() {
  // Left: -1, Both: 0, Right: 1, No: -2
  
  bool seesLeft = !leftSonarDistances.isLastNDigit(1, 0, 0);
  bool seesRight = !rightSonarDistances.isLastNDigit(1, 0, 0);
  if (seesLeft && seesRight) {
    return 0;
  } else if (seesLeft) {
    return -1;
  } else if (seesRight) {
    return 1;
  } else {
    return -2;
  }                            
}

float KnuseZumo::leftSonarDistance() {
  /*
   * Må kalles etter 'stillSeesEnemy()'
   */
  return leftSonarDistances.getAverage();
}

float KnuseZumo::rightSonarDistance() {
   /*
   * Må kalles etter 'stillSeesEnemy()'
   */
  return rightSonarDistances.getAverage();
}
