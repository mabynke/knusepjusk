#ifndef PID_H
#define PID_H

#include "Arduino.h"

double PID(double Value, double R, double P, double I, double D, double MIN, double MAX) {
  double e = Value - R;
  double output = P*e + I*e + D*e;
  output = max(output, MIN);
  output = min(output, MAX);
  return output;
}

#endif
