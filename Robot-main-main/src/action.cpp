#include "Motor_control.h"
#include "encoder.h"
#include "action.h"
#include "Get_readings.h"
#include <Arduino.h>
#include <stdlib.h>
#include <string.h>

// Array to store detected cross types
char crossArray[100];
int crossIndex = 0;
bool pathFinished = false; // Set true when path finding is done
int crossCount = 0; // Count of updated elements in crossArray

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
        if (encoderCount_Left >= 100) forward(100, 0, 0);
    }
    stopMotors();
}

// Update crossArray and count, set pathFinished if allOne
void updateCrossArray(char letter, bool finish = false) {
    crossArray[crossIndex++] = letter;
    crossCount++;
    if (finish) pathFinished = true;
}

// Rearrange crossArray based on specific patterns
void rearrangeCrossArray() {
    int  sortedIndex = 0;
    char* arraysorted = NULL;
    for (int i = 0; i < crossCount;) {
        // Stop and append D if found
        if (crossArray[i] == 'D') {
            arraysorted = (char*)realloc(arraysorted, (sortedIndex + 1) * sizeof(char));
            arraysorted[sortedIndex++] = 'D';
            break;
        }
        // Check for patterns RUR, RUS, SUR
        if (i + 2 < crossCount) {
            if (crossArray[i] == 'R' && crossArray[i+1] == 'U' && crossArray[i+2] == 'R') {
                arraysorted = (char*)realloc(arraysorted, (sortedIndex + 1) * sizeof(char));
                arraysorted[sortedIndex++] = 'S';
                i += 3;
                continue;
            }
            if (crossArray[i] == 'R' && crossArray[i+1] == 'U' && crossArray[i+2] == 'S') {
                arraysorted = (char*)realloc(arraysorted, (sortedIndex + 1) * sizeof(char));
                arraysorted[sortedIndex++] = 'L';
                i += 3;
                continue;
            }
            if (crossArray[i] == 'S' && crossArray[i+1] == 'U' && crossArray[i+2] == 'R') {
                arraysorted = (char*)realloc(arraysorted, (sortedIndex + 1) * sizeof(char));
                arraysorted[sortedIndex++] = 'L';
                i += 3;
                continue;
            }
        }
        // Otherwise, copy as is
        arraysorted = (char*)realloc(arraysorted, (sortedIndex + 1) * sizeof(char));
        arraysorted[sortedIndex++] = crossArray[i];
        i++;
    }
    // Optionally print or use arraysorted
    Serial.print("Rearranged Array: ");
    for (int i = 0; i < sortedIndex; i++) {
        Serial.print(arraysorted[i]);
        Serial.print(" ");
    }
    //free(arraysorted);
    reverseAndSwapSortedArray(arraysorted, sortedIndex);
    free(arraysorted);
}

void reverseAndSwapSortedArray(const char* arraysorted, int length) {
    char* reversed = (char*)malloc(length * sizeof(char));
    if (!reversed) {
        Serial.println("Memory allocation failed!");
        return;
    }
    for (int i = 0; i < length; i++) {
        char c = arraysorted[length - 1 - i];
        if (c == 'L') reversed[i] = 'R';
        else if (c == 'R') reversed[i] = 'L';
        else reversed[i] = c;
    }
    // Optionally print or use reversed array
    Serial.print("Reversed & Swapped Array: ");
    for (int i = 0; i < length; i++) {
        Serial.print(reversed[i]);
        Serial.print(" ");
    }
    Serial.println();
    free(reversed);
}

// Main cross detection handler
void handleSpecialCross(const char* crossType, const int analog_readings[9], const int thresholds[9]) {
    int irArray[9];
    // Move a bit forward before checking
    forward(100, 100, 0);
    delay(200);
    stopMotors();
    digitalize_with_calibrated_threshold(analog_readings, thresholds, irArray);

    if (strcmp(crossType, "t_left") == 0) {
        bool tCross = (irArray[3] == 1 || irArray[4] == 1 || irArray[5] == 1);
        bool allZero = (irArray[0] == 0 && irArray[1] == 0 && irArray[2] == 0 && irArray[3] == 0 && irArray[4] == 0 && irArray[5] == 0 && irArray[6] == 0 && irArray[7] == 0 && irArray[8] == 0);
        if (tCross) {
            updateCrossArray('S');
        } else if (allZero) {
            updateCrossArray('L');
            // Turn left
            
        }
    } 
    else if (strcmp(crossType, "t_right") == 0) {
        // Move forward and turn right
        //Turn right
    } 
    else if (strcmp(crossType, "cross") == 0) {
        bool allOne = (irArray[0] == 1 && irArray[1] == 1 && irArray[2] == 1 && irArray[3] == 1 && irArray[4] == 1 && irArray[5] == 1 && irArray[6] == 1 && irArray[7] == 1 && irArray[8] == 1);
        bool allZero = (irArray[0] == 0 && irArray[1] == 0 && irArray[2] == 0 && irArray[3] == 0 && irArray[4] == 0 && irArray[5] == 0 && irArray[6] == 0 && irArray[7] == 0 && irArray[8] == 0);
        bool plusCross = (irArray[3] == 1 || irArray[4] == 1 || irArray[5] == 1);
        if (allOne) {
            updateCrossArray('D', true);
        } 
        
        else if (allZero) {
            updateCrossArray('R');
            //Turn right
        } 
        
        else if (plusCross && !allOne) {
            //Turn right
            updateCrossArray('R');
        }
    }
}

