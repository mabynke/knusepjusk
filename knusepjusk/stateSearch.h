#include <NewServo.h>
#include <NewPing.h>
#include <PLab_ZumoMotors.h>
#include <ZumoReflectanceSensorArray.h>
#include <PLab_ZumoMotors.h>

#include "borderdetect.h"
#include "Arduino.h"

#define NUM_SENSORS 6
#define SERVO_OFFSET 20  // DS: Degrees offset of servo... error in hardware...

int REVERSE_SPEED  = 400; // 0 is stopped, 400 is full speed
int TURN_SPEED     = 300;
int FORWARD_SPEED  = 250;


void stepServo(NewServo &myServo,int& degreesServo, int& degreesStep);
int search(NewServo &myServo, ZumoReflectanceSensorArray &sensors, PLab_ZumoMotors &plab_Motors,NewPing& sonar, int& degreesServo, int& degreesStep);
float sonarDistance();
void turn(PLab_ZumoMotors &plab_Motors, int spd, int degree);

int search(NewServo &myServo, ZumoReflectanceSensorArray &sensors, PLab_ZumoMotors &plab_Motors, NewPing& sonar, int& degreesServo, int& degreesStep) {
  unsigned int sensor_values[NUM_SENSORS];
  
  while (true) {
    stepServo(myServo, degreesServo, degreesStep );
    sensors.read(sensor_values);

    int borderStatus = findBorder(sensor_values, NUM_SENSORS);
    Serial.print(borderStatus);

    if (borderStatus != 0) {
      // Sørger for at den ikke kjører utenfor
      int randAngle = random(100, 150);
      if (borderStatus == 1 || borderStatus == 2) {
        plab_Motors.backward(REVERSE_SPEED, 10);
        plab_Motors.turnRight(TURN_SPEED,randAngle);
      } else if (sensor_values[5] < QTR_THRESHOLD) {
        plab_Motors.backward(REVERSE_SPEED, 10);
        plab_Motors.turnLeft(TURN_SPEED,randAngle);
      }
    } else if (borderStatus == 0) {

      int distance = sonarDistance();
      if (distance > 0) {
        int actual_degrees_servo = degreesServo + SERVO_OFFSET;
        if (actual_degrees_servo > 100) {
        turn(plab_Motors, TURN_SPEED,actual_degrees_servo-90);
        //BTSerialSendMessage(btSerial, "#angle",actual_degrees_servo);
        } else if (actual_degrees_servo < 80) {
         turn(plab_Motors, TURN_SPEED,90-actual_degrees_servo);
        } else {
        myServo.write(degreesServo);
        }
      } else {
        plab_Motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
      }
    }
  } 
}


void stepServo(NewServo &myServo, int& degreesServo, int& degreesStep) {
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

float sonarDistance(NewPing& sonar) {
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

void turn(PLab_ZumoMotors &plab_Motors, int spd, int degree) {
  int leftSpeed;
  int rightSpeed;
  if (degree < 0) {
    int leftSpeed = spd*cos(degree);
    int rightSpeed = spd;
  } else {
    int leftSpeed = spd;
    int rightSpeed = spd*cos(degree);
  }
  plab_Motors.setSpeeds(leftSpeed, rightSpeed);
}
