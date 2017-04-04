
#ifndef START_STATE_H
#define SSTART_STATE_H

#include <ZumoReflectanceSensorArray.h>

#include "KnuseZumo.h"
#include "States.h"
#include "Utils.h"

State startState(KnuseZumo &zumo, ZumoReflectanceSensorArray &sensors) {
  const int minForward = 15;
  const int maxForward = 25;
  Serial.println("startState");
  BTSerialSendMessage("startState");
  
  // Kjører rett fram så fort den kan
  int randDistance = random(minForward, maxForward);
//  zumo.forward(400, randDistance);

  // Farten setter bare en gang
  int randInt = rand()%2;
  int lowSpeed = -250;
  int highSpeed = 250;
  if (randInt == 1) {
    zumo.setSpeeds(lowSpeed, highSpeed);
  } else {
    zumo.setSpeeds(highSpeed, lowSpeed);
  }
  
  int startTime = millis();
  //int currentTime = startTime;
  int duration = 1000;
  
  while (fittingTime(millis(), startTime, duration)) {
    if (zumo.newEnemyDetected()) {
      return Attack;
    }
    if (findBorder(sensors) != 0) {
      return AwayFromBorder;
    }
    //currentTime = millis();
  }
  return SearchOnSpot;
}

#endif
