#ifndef SERACH_MOVING_H
#define SERACH_MOVING_H

#include <ZumoReflectanceSensorArray.h>

#include "KnuseZumo.h"
#include "States.h"
#include "Utils.h"

State searchMoving(KnuseZumo &zumo, ZumoReflectanceSensorArray &sensors) {
  Serial.println("searchMoving");
  
  int angle = random(-60, 60);
  angle = 3.1415/180*angle;
  int startTime = millis();
  int currentTime = startTime;
  int duration = random(300,500);

  zumo.driveAndTurn(300, angle);
  while (fittingTime(currentTime, startTime, duration)) {
    if (findBorder(sensors) != 0) {
      return AwayFromBorder;
    }
    if (zumo.newEnemyDetected()) {
      return Attack;
    }
    currentTime = millis();
  }
  return SearchOnSpot;
}

#endif
