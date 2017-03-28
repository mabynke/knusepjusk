#include <NewPing.h>
#include <NewServo.h>
#include <Pushbutton.h>
//#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
//#include <SoftwareSerial.h>
//#include <PLabBTSerial.h>

#include "Pins.h"
#include "KnuseZumo.h"
#include "States.h"
#include "Attack.h"
#include "SearchOnSpot.h"
#include "SearchMoving.h"
#include "AwayFromBorder.h"

// NB! 47 I VÅRT TILFELLE
#define SERVO_OFFSET 47  // DS: Degrees offset of servo... error in hardware...


Pushbutton button(ZUMO_BUTTON);
 
ZumoReflectanceSensorArray sensors;
//PLabBTSerial btSerial(txPin, rxPin);
NewPing sonar(triggerPin, echoPin, maxDistance);
NewServo myServo; 

KnuseZumo zumo(sonar, myServo);

void setup() {
  sensors.init(QTR_NO_EMITTER_PIN);  // 
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  myServo.attach(servoPin); 
  myServo.write(90 - SERVO_OFFSET);
  Serial.println("Før knapp");
  button.waitForButton(); // start when button pressed
  Serial.println("Etter knapp");
  
}

State state = SearchMoving;

void loop() {
//  Serial.print(zumo.sonarDistance());
//  Serial.print(" ");
//  Serial.print(zumo.newEnemyDetected());
//  Serial.print(" ");
//  Serial.println(zumo.stillSeesEnemy());
//  zumo.driveAndTurn(100, 0);
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
  }
}

