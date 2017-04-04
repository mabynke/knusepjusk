#ifndef AWAY_FORM_BORDER_H
#define AWAY_FROM_BORDER_H

#include <ZumoReflectanceSensorArray.h>

#include "KnuseZumo.h"
#include "Utils.h"
#include "States.h"

State awayFromBorder(KnuseZumo &zumo, ZumoReflectanceSensorArray &sensors) {
  Serial.println("AwayFromBorder");
  
  
  int borderStatus = findBorder(sensors);
  int REVERSE_SPEED = 400;
  int TURN_SPEED = 400;

  BTSerialSendMessage("AwayFromBorder | borderStatus: ", borderStatus);
  
  if (borderStatus == 1 || borderStatus == 2) {
    zumo.backward(REVERSE_SPEED, 10);
    zumo.turnRight(TURN_SPEED,random(100, 150));
  }
  else if (borderStatus == 3) {
    zumo.backward(REVERSE_SPEED, 10);
    zumo.turnRight(TURN_SPEED,random(150, 210));
  }
  else if (borderStatus == 4 || borderStatus == 5) {
    zumo.backward(REVERSE_SPEED, 10);
    zumo.turnLeft(TURN_SPEED,random(100, 150));
  }

  return SearchMoving;
}

#endif
