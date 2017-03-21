#include <NewPing.h>
#include <NewServo.h>
#include <Pushbutton.h>
#include <PLab_ZumoMotors.h>
#include <ZumoMotors.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <SoftwareSerial.h>
#include <PLabBTSerial.h>

#include "Utils.h"
#include "borderdetect.h"
#include "Pins.h"
#include "Bluetooth.h"
#include "stateSearch.h"
/*
// these might need to be tuned for different motor types
int REVERSE_SPEED  = 400; // 0 is stopped, 400 is full speed
int TURN_SPEED     = 300;
int FORWARD_SPEED  = 250;
*/
#define NUM_SENSORS 6
//unsigned int sensor_values[NUM_SENSORS]; // Denne bør defineres hvert sted den evt. trengs, ikke i denne filen.

#define SERVO_OFFSET 20  // DS: Degrees offset of servo... error in hardware...

// Tilstander
#define ATTACK 0
#define SEARCH 1
 
ZumoReflectanceSensorArray sensors;


ZumoMotors motors;

PLabBTSerial btSerial(txPin, rxPin);

NewPing sonar(triggerPin, echoPin, maxDistance);
NewServo myServo; 

Pushbutton button(ZUMO_BUTTON); 

int degreesServo = 0;
int degreesStep = 10;

PLab_ZumoMotors plab_Motors;

//...........................................................................
// Always include this method.
// It reads from the BT port and calls BTSerialMessageReceived.
// 
//char msg[100];
//void updateBTSerial() {
//  int availableCount = btSerial.available();
//  if (availableCount > 0) {
//    btSerial.read(msg, availableCount);
//    char *divided = strchr(msg,',');
//    int msgValue = 0;
//    if (divided != 0) {
//       divided[0] = 0; divided++;
//       String str(divided);
//       msgValue = str.toInt();
//    };
//    String msgString(msg);
//    BTSerialMessageReceived(msgString,msgValue);   
//  }
//}
//...........................................................................


//void BTSerialMessageReceived(String msgString,int msgValue) {
//  Serial.print("Message:"); Serial.print(msgString); // Debug print
//  Serial.print(", Value:"); Serial.println(msgValue);  // Debug print
//  if (msgString == "#speed") {
//    REVERSE_SPEED  = msgValue; // 0 is stopped, 400 is full speed
//    TURN_SPEED     = msgValue;
//    FORWARD_SPEED  = msgValue; return;
//  } 
//}

void setup() {
  sensors.init(QTR_NO_EMITTER_PIN);  // 
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  myServo.attach(servoPin); 
  myServo.write(90);
  button.waitForButton(); // start when button pressed
//  btSerial.begin(9600); // Open serial communication to Bluetooth unit
}

int state = SEARCH;

void loop() {
  switch(state) {
    case SEARCH:
      state = search(myServo, sensors, plab_Motors,sonar, degreesServo, degreesStep);
      break;
    case ATTACK:
      //TODO: attack()
      break;
  }
}
