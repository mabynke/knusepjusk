#ifndef ROTATE_H
#define ROTATE_H

#include "Arduino.h"
#include <PLab_ZumoMotors.h>


int rotate(PLab_ZumoMotors &plab_Motors) {
  int startTime = millis();
  while (millis() < startTime + 5000) {
    plab_Motors(100, -100);
  }
  return 0;
}

#endif
