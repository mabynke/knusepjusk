#ifndef AWAY_FORM_BORDER_H
#define AWAY_FROM_BORDER_H

#include <ZumoReflectanceSensorArray.h>

#include "KnuseZumo.h"
#include "Utils.h"
#include "States.h"

State awayFromBorder(KnuseZumo &zumo, ZumoReflectanceSensorArray &sensors) {
  Serial.println("AwayFromBorder");
  
  int randAngle = random(100, 150); // Bør settes av borderStatus
  int borderStatus = findBorder(sensors);
  int REVERSE_SPEED = 400;
  int TURN_SPEED = 400;
  
  if (borderStatus == 1 || borderStatus == 2) {
    zumo.backward(REVERSE_SPEED, 10);
    zumo.turnRight(TURN_SPEED,randAngle);
  } else if (borderStatus == 3 || borderStatus == 4) {
    zumo.backward(REVERSE_SPEED, 10);
    zumo.turnLeft(TURN_SPEED,randAngle);
  }

  return SearchMoving;
}

#endif
