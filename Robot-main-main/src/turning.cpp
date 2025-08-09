// Functions to turn the robot using encoder readings
#include <Arduino.h>
#include "Motor_control.h"
#include "Get_readings.h"
#include "encoder.h"

// Define motor speed
#define SPEED 150
#define turncount1 150



// Turn left: left motor 100, right motor 150 encoder counts
void turnLeft() {
    stopMotors();
    delay(500);
    encoderCount_Left = 0;
    encoderCount_Right = 0;
    right_motor(SPEED, 1, 0); // right forward
    left_motor(SPEED, 0, 0); // left backward

    while (encoderCount_Left > -turncount1 || encoderCount_Right < turncount1) {
        Serial.print("encoderCount_Left: ");
        Serial.print(encoderCount_Left);
        Serial.print(" ");
        Serial.print("encoderCount_Right: ");
        Serial.print(encoderCount_Right);
        Serial.println();
        if (encoderCount_Left <= -150) backward(0, 0, 0);
        if (encoderCount_Right >= 150) forward(0, 0, 0);
    }
    stopMotors();
}

// Turn right: right motor 100, left motor 150 encoder counts
void turnRight() {
    stopMotors();
    delay(500);
    encoderCount_Left = 0;
    encoderCount_Right = 0;

    right_motor(SPEED, 0, 0); // Right motor backward
    left_motor(SPEED, 1, 0); // Left motor forward

    while (encoderCount_Right > -150 || encoderCount_Left < 150) {
        Serial.print("encoderCount_Right: ");
        Serial.print(encoderCount_Right);
        Serial.print(" ");
        Serial.print("encoderCount_Left: ");
        Serial.print(encoderCount_Left);
        Serial.println();
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
