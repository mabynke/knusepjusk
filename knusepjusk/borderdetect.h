#ifndef BORDERDETECT_H
#define BORDERDETECT_H

#include "Arduino.h"
// this might need to be tuned for different lighting conditions, surfaces, etc.
#define QTR_THRESHOLD  1800 

int findBorder(int* sensors, int num_sensors) {
  /*
   * Tar inn verdiene fra de infrarøde sensorene i en array og antall sensorer (antall tall i arrayen).
   * 
   * Returnerer 0 dersom ingen kant blir funnet.
   * Returnerer 1 dersom en kant blir funnet helt til venstre.
   * Returnerer 2 dersom en kant blir funnet litt til venstre.
   * Returnerer 3 dersom en kant blir funnet rett foran.
   * Returnerer 4 dersom en kant blir funnet litt til høyre.
   * Returnerer 5 dersom en kant blir funnet helt til høyre.
   */

  bool left = sensors[0] < QTR_THRESHOLD;
  bool secondLeft = sensors[1] < QTR_THRESHOLD;
  bool secondRight = sensors[num_sensors - 2] < QTR_THRESHOLD;
  bool right = sensors[num_sensors-1] < QTR_THRESHOLD;

  //debugging
  Serial.print("LEFT: "); Serial.print(left); Serial.println();
  Serial.print("SECOND_LEFT: "); Serial.print(secondLeft); Serial.println();
  Serial.print("RIGHT: "); Serial.print(right); Serial.println();
  Serial.print("SECOND_RIGHT: "); Serial.print(secondRight); Serial.println();
  
  if (left && right) return 3;
  if (left && secondLeft) return 2;
  if (left) return 1;
  if (right && secondRight) return 4;
  if (right) return 3;
  return 0;
}
#endif
