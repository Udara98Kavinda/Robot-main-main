#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <Arduino.h>

#define KP  8.0 // Proportional gain 8
#define KD  4.0 // Derivative gain 0.5
#define kI  0.0 // Integral gain (not used in this example)

//=============== Encoder ================================
#define KPe  15//20 // Proportional gain for encoder
#define KDe 10 //6.8// 10 // Derivative gain for encoder
#define KIe 5 //2.8// 5

//=============== Gyro ================================
#define Kpc  10.0
#define Kic  0.0
#define Kdc  10.0

int calculate_error(const int digital[9]);
int compute_pid(int error, int pre_error, float Kp, float Kd);

int calculate_error_encoder(long encoderCount_Left, long encoderCount_Right);
int compute_pid_encoder(int error, int previous_error, float Kp, float Kd, float Ki);


// PID to move towards target heading
float headingPID(float targetHeading, float currentHeading);

#endif // PID_CONTROLLER_H
