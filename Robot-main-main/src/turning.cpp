// Functions to turn the robot using encoder readings
#include <Arduino.h>
#include "Motor_control.h"
#include "Get_readings.h"
#include "encoder.h"

// Define motor speed
#define SPEED 100

// Turn left: left motor 100, right motor 150 encoder counts
void turnLeft() {
    encoderCount_Left = 0;
    encoderCount_Right = 0;
    backward(100, 0, 0); // left backward
    forward(0, 100, 0);  // right forward
    while (encoderCount_Left > -150 || encoderCount_Right < 150) {
        if (encoderCount_Left <= -150) backward(0, 0, 0);
        if (encoderCount_Right >= 150) forward(0, 0, 0);
    }
    stopMotors();
}

// Turn right: right motor 100, left motor 150 encoder counts
void turnRight() {
    encoderCount_Left = 0;
    encoderCount_Right = 0;
    forward(100, 0, 0); // left forward
    backward(0, 100, 0); // right backward
    while (encoderCount_Right > -150 || encoderCount_Left < 150) {
        if (encoderCount_Right <= -150) backward(0, 0, 0);
        if (encoderCount_Left >= 150) forward(0, 0, 0);
    }
    stopMotors();
}

// Turn 180 degrees: both motors 300 encoder counts
void turn180(bool left) {
    encoderCount_Left = 0;
    encoderCount_Right = 0;
    if (left) {
        backward(100, 0, 0); // left backward
        forward(0, 100, 0);  // right forward
        while (encoderCount_Left > -300 || encoderCount_Right < 300) {
            if (encoderCount_Left <= -300) backward(0, 0, 0);
            if (encoderCount_Right >= 300) forward(0, 0, 0);
        }
    } else {
        forward(100, 0, 0); // left forward
        backward(0, 100, 0); // right backward
        while (encoderCount_Right > -300 || encoderCount_Left < 300) {
            if (encoderCount_Right <= -300) backward(0, 0, 0);
            if (encoderCount_Left >= 300) forward(0, 0, 0);
        }
    }
    stopMotors();
}