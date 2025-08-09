#include "Motor_control.h"
#include "encoder.h"
#include "action.h"
#include "Get_readings.h"
#include "turning.h"

#include <Arduino.h>

// Array to store detected cross types
char crossArray[50];
int crossIndex = 0;

// Helper: Stop, reverse slowly, then go forward
void handleCrossApproach() {
    stopMotors();
    backward(10, 10, 0); // slow backward
    delay(200);
    stopMotors();
    encoderCount_Left = 0;
    encoderCount_Right = 0;
    forward(100, 100, 0);
    while (encoderCount_Left < 100 && encoderCount_Right < 100) {
        if (encoderCount_Right >= 100) forward(100, 0, 0);
        if (encoderCount_Left >= 100) forward(0, 100, 0);
    }
    stopMotors();
}

// Main cross detection handler
void handleSpecialCross(int crossType, const int analog_readings[9], const int thresholds[9]) {
    int irArray[9];
    // Move a bit forward before checking
    forward(100, 100, 0);
    delay(200);
    stopMotors();
    digitalize_with_calibrated_threshold(analog_readings, thresholds, irArray);

    if (crossType == 2) { // T-Left
        bool tCross = (irArray[3] == 1 || irArray[4] == 1 || irArray[5] == 1);
        bool allZero = (irArray[0] == 0 && irArray[1] == 0 && irArray[2] == 0 && irArray[3] == 0 && irArray[4] == 0 && irArray[5] == 0 && irArray[6] == 0 && irArray[7] == 0 && irArray[8] == 0);
        if (tCross) {
            crossArray[crossIndex++] = 'S';
        } else if (allZero) {
            crossArray[crossIndex++] = 'L';
            // Turn left
            turnLeft();
        }  
    } 
    else if (crossType == 3) { // T-Right
        turnRight();
        // Move forward and turn right
        //Turn right
        crossType = 0;  
    } 
    else if (crossType == 1) { // Cross
        bool allOne = (irArray[0] == 1 && irArray[1] == 1 && irArray[2] == 1 && irArray[3] == 1 && irArray[4] == 1 && irArray[5] == 1 && irArray[6] == 1 && irArray[7] == 1 && irArray[8] == 1);
        bool allZero = (irArray[0] == 0 && irArray[1] == 0 && irArray[2] == 0 && irArray[3] == 0 && irArray[4] == 0 && irArray[5] == 0 && irArray[6] == 0 && irArray[7] == 0 && irArray[8] == 0);
        bool plusCross = (irArray[3] == 1 || irArray[4] == 1 || irArray[5] == 1);
        if (allOne) {
            crossArray[crossIndex++] = 'D';
        } 
        
        else if (allZero) {
            crossArray[crossIndex++] = 'R';
            //Turn right
        } 
        
        else if (plusCross && !allOne) {
            //Turn right
            crossArray[crossIndex++] = 'R';
        }
    }
    crossType = 0;  
}