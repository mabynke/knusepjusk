#include <NewPing.h>
#include <NewServo.h>
#include <Pushbutton.h>
//#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
//#include <SoftwareSerial.h>
#include <PLabBTSerial.h>

#include "Pins.h"
#include "KnuseZumo.h"
#include "States.h"
#include "Attack.h"
#include "SearchOnSpot.h"
#include "SearchMoving.h"
#include "AwayFromBorder.h"
#include "StartState.h"

Pushbutton button(ZUMO_BUTTON);
 
ZumoReflectanceSensorArray sensors;
NewPing leftSonar(leftTriggerPin, leftEchoPin, maxDistance);
NewPing rightSonar(rightTriggerPin, rightEchoPin, maxDistance);

KnuseZumo zumo(leftSonar, rightSonar);

void setup() {
  sensors.init(QTR_NO_EMITTER_PIN);  // 
  Serial.begin(9600);
  initBTSerial();
  pinMode(ledPin,OUTPUT);
  Serial.println("Før knapp");
  button.waitForButton(); // start when button pressed
  Serial.println("Etter knapp");
  
}

State state = StartState;

void loop() {
  updateBTSerial();
  switch(state) {
    case Attack:
      state = attack(zumo, sensors);
      break;
    case SearchOnSpot:
      state = searchOnSpot(zumo, sensors);
      break;
    case SearchMoving:
      state = searchMoving(zumo, sensors);
      break;
    case AwayFromBorder:
      state = awayFromBorder(zumo, sensors);
      break;
    case StartState:
      state = startState(zumo, sensors);
      break;
  }
}

