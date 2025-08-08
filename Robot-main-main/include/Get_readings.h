#ifndef IR_PANEL_H
#define IR_PANEL_H

#include <Arduino.h>

#define R4 A0
#define R3 A1
#define R2 A2
#define R1 A3
#define C0 A4
#define L1 A5
#define L2 A6
#define L3 A7
#define L4 A8

extern const int IR_PINS[9];

void IR_pin_configuration();
void read_IR_sensors(int readings[9]);
void print_IR_readings(const int readings[9]);
void calibrate_IR_sensors(int readings[9], int samples);
void digitalize_with_calibrated_threshold(const int analog_readings[9], const int thresholds[9], int digital[9]);


#endif // IR_PANEL_H
