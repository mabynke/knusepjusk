#ifndef ATTACK_H
#define ATTACK_H

#include <ZumoReflectanceSensorArray.h>

#include "KnuseZumo.h"
#include "Utils.h"
#include "States.h"

State attack(KnuseZumo &zumo, ZumoReflectanceSensorArray &sensors) {
  const int lowSpeed = 180;
  const int highSpeed = 400;

  Serial.println("Attack");
  int currentStatus;
  float leftDistance;
  float rightDistance;

  BTSerialSendMessage("Attack");
  
  while (zumo.stillSeesEnemy()) {
    if (findBorder(sensors) != 0) {
      return AwayFromBorder;
    }
    
    currentStatus = zumo.sonarStatus();
    BTSerialSendMessage("Attack currentStatus: ", currentStatus);
    
    if (currentStatus == 0) { // Ser noe rett foran
      zumo.setSpeeds(400, 400);
      continue;
    }
    
    leftDistance = zumo.leftSonarDistance();
    rightDistance = zumo.rightSonarDistance();
    if (currentStatus == -1) { // Ser noe til venstre
      zumo.setSpeeds(lowSpeed, highSpeed);
    }
    else if (currentStatus == 1) { // Ser noe til høyre
      zumo.setSpeeds(highSpeed, lowSpeed);
    }
    else { // Ser ingenting
      zumo.setSpeeds(200, 200);
    }
  }
  return SearchOnSpot;
}

#endif

