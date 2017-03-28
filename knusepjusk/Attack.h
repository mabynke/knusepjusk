#ifndef ATTACK_H
#define ATTACK_H

#include <ZumoReflectanceSensorArray.h>

#include "KnuseZumo.h"
#include "Utils.h"
#include "States.h"

State attack(KnuseZumo &zumo, ZumoReflectanceSensorArray &sensors) {
  Serial.println("Attack");
  
  zumo.driveAndTurn(400, 0);  // trengs bare å settes én gang
  
  while (zumo.stillSeesEnemy()) {
    if (findBorder(sensors) != 0) {
      return AwayFromBorder;
    }
  }
  return SearchOnSpot;
}

#endif

