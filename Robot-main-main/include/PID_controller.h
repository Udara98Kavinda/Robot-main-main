#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <Arduino.h>

#define KP  8.0 // Proportional gain 8
#define KD  4.0 // Derivative gain 0.5
#define kI  0.0 // Integral gain (not used in this example)

#define KPe  1.0 // Proportional gain for encoder
#define KDe  0.5 // Derivative gain for encoder

int calculate_error(const int digital[9]);
int compute_pid(int error, int pre_error, float Kp, float Kd);
int calculate_error_encorder(long encoderCount_Left, long encoderCount_Right);
//int compute_pid_encoder(long encoderCount_Left, long encoderCount_Right);

#endif // PID_CONTROLLER_H
