#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <Arduino.h>

#define KP  1.0 // Proportional gain
#define KD  0.5 // Derivative gain
#define kI  0.0 // Integral gain (not used in this example)


int calculate_error(const int digital[9]);
int compute_pid(int error, int pre_error, float Kp, float Kd);

#endif // PID_CONTROLLER_H
