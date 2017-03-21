#include <NewServo.h>
#include <NewPing.h>
#include <PLab_ZumoMotors.h>
#include <ZumoReflectanceSensorArray.h>
#include <PLab_ZumoMotors.h>

#include "borderdetect.h"
#include "Arduino.h"
#include "Utils.h"

#define NUM_SENSORS 6
#define SERVO_OFFSET 20  // DS: Degrees offset of servo... error in hardware...


// int search(NewServo &myServo, ZumoReflectanceSensorArray &sensors, PLab_ZumoMotors &plab_Motors,NewPing& sonar, int& degreesServo, int& degreesStep);

int search(NewServo &myServo, ZumoReflectanceSensorArray &sensors, PLab_ZumoMotors &plab_Motors, NewPing& sonar, int& degreesServo, int& degreesStep) {
  unsigned int sensor_values[NUM_SENSORS];
  
  while (true) {
    stepServo(myServo, degreesServo, degreesStep );
    sensors.read(sensor_values);

    int borderStatus = findBorder(sensor_values, NUM_SENSORS);
    Serial.print(borderStatus);

    if (borderStatus != 0) {
      // Sørger for at den ikke kjører utenfor
      borderFlee(plab_Motors, borderStatus);
    } else {
      int distance = sonarDistance(sonar);
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



