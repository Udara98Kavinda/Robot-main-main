#ifndef ACTION_H
#define ACTION_H

#include <Arduino.h>

void handleSpecialCross(const char* crossType, const int analog_readings[9], const int thresholds[9]);

#endif // ACTION_H