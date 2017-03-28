#ifndef ATTACK_H
#define ATTACK_H

#include <ZumoReflectanceSensorArray.h>

#include "KnuseZumo.h"
#include "Utils.h"
#include "States.h"

State attack(KnuseZumo &zumo, ZumoReflectanceSensorArray &sensors) {
  Serial.println("Attack");
  
  //zumo.driveAndTurn(400, 0);  // trengs bare å settes én gang
  
  float leftDistance;
  float rightDistance;
  
  while (zumo.stillSeesEnemy()) {
    if (findBorder(sensors) != 0) {
      return AwayFromBorder;
    }
    
    int currentStatus = sonarStatus();
    
    if (currentStatus == 0) { // Ser noe rett foran
      setSpeeds(400, 400);
      continue;
    }
    
    leftDistance = leftSonarDistance();
    rightDistance = rightSonarDistance();
    if (currentStatus == -1) { // Ser noe til venstre
      setSpeeds(200, 400);
    }
    else if (currentStatus == 1) { // Ser noe til høyre
      setSpeeds(400, 200);
    }
    else if (currentStatus == -2) { // Ser ingenting
      setSpeeds(200, 200);
    }
  }
  return SearchOnSpot;
}

#endif

