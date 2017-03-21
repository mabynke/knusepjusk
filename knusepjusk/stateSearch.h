#include <NewServo.h>
#include <PLab_ZumoMotors.h>
#include <ZumoReflectanceSensorArray.h>

#include "knusepjusk.ino"
#include "borderdetect.h"

int search(sensors) {
  unsigned int sensor_values[NUM_SENSORS];
  
  while (true) {
    stepServo();
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
        turn(TURN_SPEED,actual_degrees_servo-90);
        //BTSerialSendMessage(btSerial, "#angle",actual_degrees_servo);
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
}
