#ifndef KNUSE_ZUMO_H
#define KNUSE_ZUMO_H

#include <PLab_ZumoMotors.h>
#include <ZumoReflectanceSensorArray.h>
#include <NewPing.h>
#include <NewServo.h>
#include "Arduino.h"
#include "ArrayRing.h"

/*
 * Arver følgende funksjoner fra PLab_ZumoMotors
 * 
    void forward(int _speed, int length);
    void backward(int _speed, int _length);
    void turnRight(int _speed, int degrees);
    void turnLeft(int _speed, int degrees);   

    // enable/disable flipping of motors
    void flipLeftMotor(boolean flip);
    void flipRightMotor(boolean flip);

    // set speed for left, right, or both motors
    void setLeftSpeed(int speed);
    void setRightSpeed(int speed);
    void setSpeeds(int leftSpeed, int rightSpeed);

 */

class KnuseZumo : public PLab_ZumoMotors {
    public:
        KnuseZumo(NewPing &, NewPing &, NewServo &);
        void turnOnSpot(int _speed);
        void driveAndTurn(int _speed, int angle);
        void sendSonarPingLeft();
        void sendSonarPingRight();
        float leftSonarDistance();
        float rightSonarDistance();
        boolean newEnemyDetected();
        boolean stillSeesEnemy();
    private:
        static const int NUM_SENSORS = 6;
        static const int QTR_THRESHOLD = 1800;
        static const int SERVO_OFFSET = 47;
        ArrayRing leftSonarDistances;
        ArrayRing rightSonarDistances;
        NewPing leftSonar;
        NewPing rightSonar;
        int degreesServo = 0;
        int degreesStep = 10;

        void sendSonarPing();
};

#endif
