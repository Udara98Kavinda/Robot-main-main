#include <Arduino.h>
#include "Get_readings.h"
#include "PID_controller.h"


int calculate_error(const int digital[9]) {
    // Weights: L3,R3=30, L2,R2=20, L1,R1=10, L0,R0=0; negative for left
    const int weights[9] = {-20, -15, -10, -5, 0, 5, 10, 15, 20};
    int error = 0;
    for (int i = 0; i < 9; i++) {
        error += weights[i] * digital[i]; 
    }
    return error;
}

int compute_pid(int error, int previous_error, float Kp, float Kd) {
    int derivative = error - previous_error;
    int pid_output = Kp * error + Kd * derivative;
    return pid_output;
}


int calculate_error_encorder(long encoderCount_Left, long encoderCount_Right) {
    // Calculate the error based on encoder counts
    // This is a placeholder implementation; adjust as needed
    int error = encoderCount_Left - encoderCount_Right;
    return error;
}

//int compute_pid_encoder(int error, int previous_error, float Kp, float Kd) {
    // Compute the PID output based on encoder counts
  //  int derivative = error - previous_error;
  //  int pid_output = Kp * error + Kd * derivative;
  //  return pid_output;
//}