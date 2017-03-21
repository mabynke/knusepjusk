#include <NewPing.h>
#include <NewServo.h>
#include <Pushbutton.h>
#include <PLab_ZumoMotors.h>
#include <ZumoMotors.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>

PLab_ZumoMotors plab_Motors;

int rotate() {
  int startTime = millis();
  while (millis() < startTime + 5000) {
    plab_Motors(100, -100);
  }
  return 0;
}
