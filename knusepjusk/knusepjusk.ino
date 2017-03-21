/*
 */
#include <NewPing.h>
#include <NewServo.h>
#include <Pushbutton.h>
#include <PLab_ZumoMotors.h>
#include <ZumoMotors.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <SoftwareSerial.h>
#include <PLabBTSerial.h>
  
// these might need to be tuned for different motor types
int REVERSE_SPEED  = 400; // 0 is stopped, 400 is full speed
int TURN_SPEED     = 300;
int FORWARD_SPEED  = 250;

#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];

#define SERVO_OFFSET 20  // DS: Degrees offset of servo... error in hardware...
 
ZumoReflectanceSensorArray sensors;


ZumoMotors motors;

const int ledPin=A4;

const int echoPin = 2;
const int triggerPin = 3;
const int maxDistance = 50;

const int servoPin = 6;

const int txPin = 0; // Connected to tx on bt unit
const int rxPin = 1; // Connected to rx on bt unit

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

//...........................................................................
// Always include these two methods .
// They send a message to the BT port, without or with an int value
// 
void BTSerialSendMessage(String msgString) {
  btSerial.println(msgString); 
}

void BTSerialSendMessage(String msgString,int msgValue) {
  btSerial.print(msgString); 
  btSerial.print(",");
  btSerial.println(msgValue);
}
//...........................................................................


void setup() {
  sensors.init(QTR_NO_EMITTER_PIN);  // 
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  myServo.attach(servoPin); 
  myServo.write(90);
  button.waitForButton(); // start when button pressed
//  btSerial.begin(9600); // Open serial communication to Bluetooth unit
}

void stepServo() {
   degreesServo = degreesServo + degreesStep;
   if (degreesServo > 180) {
       degreesStep = -degreesStep;
       degreesServo = 180;
   } else if (degreesServo < 0) {
       degreesStep = -degreesStep;
       degreesServo = 0;
   } 
   myServo.write(degreesServo);
}

float sonarDistance() {
  // Gjør ett ping, og beregn avstanden
  unsigned int time = sonar.ping();
  float distance = sonar.convert_cm(time);
  if (distance == 0.0) { // sonar gives zero when outside range
    // Turn off LED and just go forward
    digitalWrite(ledPin,LOW); 
   } else {
    digitalWrite(ledPin,HIGH);
   }
   return distance;
}

//void BTSerialMessageReceived(String msgString,int msgValue) {
//  Serial.print("Message:"); Serial.print(msgString); // Debug print
//  Serial.print(", Value:"); Serial.println(msgValue);  // Debug print
//  if (msgString == "#speed") {
//    REVERSE_SPEED  = msgValue; // 0 is stopped, 400 is full speed
//    TURN_SPEED     = msgValue;
//    FORWARD_SPEED  = msgValue; return;
//  } 
//}

//bool shouldTurnLeft(int degree, int distance) {
//  
//}

void turn(int spd, int degree) {
  int leftSpeed;
  int rightSpeed;
  if (degree < 0) {
    int leftSpeed = spd*cos(degree);
    int rightSpeed = spd;
  } else {
    int leftSpeed = spd;
    int rightSpeed = spd*cos(degree);
  }
  motors.setSpeeds(leftSpeed, rightSpeed);
}

int reachedBorder(int sensors[]) {
  // Sjekker om man står inntil kanten. 
  for (int i = 0; i < 6; ++i) {
    if (sensors[i] < QTR_THRESHOLD) {
      return 1;
    }
  }
  return 0;
}

void loop() {
//   updateBTSerial();  // Check if we have input on the BT serial port.
   stepServo();
   sensors.read(sensor_values);

  int borderStatus = reachedBorder(sensor_values);
  Serial.print(borderStatus);

   if (borderStatus == 1) {
    // Sørger for at den ikke kjører utenfor
    int randAngle = random(100, 150);
    if (sensor_values[0] < QTR_THRESHOLD) {
       plab_Motors.backward(REVERSE_SPEED, 10);
       plab_Motors.turnRight(TURN_SPEED,randAngle);
     } else if (sensor_values[5] < QTR_THRESHOLD) {
       plab_Motors.backward(REVERSE_SPEED, 10);
       plab_Motors.turnLeft(TURN_SPEED,randAngle);
     }
   } else if (borderStatus == 0) {
   
   int distance = sonarDistance();
//   Serial.prin(distance);
   if (distance > 0) {
      int actual_degrees_servo = degreesServo + SERVO_OFFSET;
      if (actual_degrees_servo > 100) {
        turn(TURN_SPEED,actual_degrees_servo-90);
         BTSerialSendMessage("#angle",actual_degrees_servo);
      } else if (actual_degrees_servo < 80) {
         turn(TURN_SPEED,90-actual_degrees_servo);
      } else {
      myServo.write(degreesServo);
      }
    } else {
      motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
    }
  } 
}


