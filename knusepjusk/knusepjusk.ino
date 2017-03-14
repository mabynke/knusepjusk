#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>

ZumoReflectanceSensorArray irSensors(QTR_NO_EMITTER_PIN);
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

unsigned int sensorData[6];

void setup() {
  Serial.begin(9600);
  button.waitForButton();
}

void loop() {
  irSensors.read(sensorData);
  for (auto it : sensorData) {
    Serial.print(it);
    Serial.print(' ');
  }
  Serial.println();
  delay(200);
}
