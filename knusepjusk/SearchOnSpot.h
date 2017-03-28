#ifndef SEARCH_ON_SPOT_H
#define SEARCH_ON_SPOT_H

#include "KnuseZumo.h"
#include "States.h"
#include "Utils.h"

boolean fittingTime(int currentTime, int startTime, int duration);  // funksjoner må deklareres før de brukes

State searchOnSpot(KnuseZumo &zumo, ZumoReflectanceSensorArray &sonar) {
  Serial.println("searchOnSpot");
  BTSerialSendMessage("serchOnSpot");
  int randInt = rand()%2;
  int lowSpeed = 20;
  int highSpeed = 300;
  if (randInt == 1) {
    zumo.setSpeeds(lowSpeed, highSpeed);
  } else {
    zumo.setSpeeds(highSpeed, lowSpeed);
  }
  
  int startTime = millis();
  //int currentTime = startTime;
  int duration = 2000;
  
  while (fittingTime(millis(), startTime, duration)) {
    if (zumo.newEnemyDetected()) {
      return Attack;
    }
    if (findBorder(sonar) != 0) {
      return AwayFromBorder;
    }
    //currentTime = millis();
  }
  return SearchMoving;
}

#endif


