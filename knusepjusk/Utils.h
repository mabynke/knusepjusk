#ifndef UTILS_H
#define UTILS_H

#define QTR_THRESHOLD 1800;

boolean fittingTime(int currentTime, int startTime, int duration) {
  return (currentTime - startTime < duration);
}

int findBorder(ZumoReflectanceSensorArray &sensors) {
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
//
//   for (int i = 0; i < NUM_SENSORS; i++) {
//    sensor_values[i]++;
//  }

  int NUM_SENSORS = 6;
  int sensor_values[NUM_SENSORS];

  sensors.read(sensor_values);
//  for (int i = 0; i < NUM_SENSORS; i++) {
//    Serial.print(sensor_values[i]);
//    Serial.print(" ");
//  }

//  Serial.print(analogRead(4));
  

  bool left = sensor_values[0] < QTR_THRESHOLD;
  bool secondLeft = sensor_values[1] < QTR_THRESHOLD;
  bool secondRight = sensor_values[NUM_SENSORS - 2] < QTR_THRESHOLD;
  bool right = sensor_values[NUM_SENSORS-1] < QTR_THRESHOLD;

  //debugging
//  Serial.print("LEFT: "); Serial.print(left); Serial.println();
//  Serial.print("SECOND_LEFT: "); Serial.print(secondLeft); Serial.println();
//  Serial.print("RIGHT: "); Serial.print(right); Serial.println();
//  Serial.print("SECOND_RIGHT: "); Serial.print(secondRight); Serial.println();
//  delay(500);
  
  if (left && right) return 3;
  if (left && secondLeft) return 2;
  if (left) return 1;
  if (right && secondRight) return 4;
  if (right) return 3;
  return 0;
}

#endif
