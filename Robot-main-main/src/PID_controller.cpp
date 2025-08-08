#include <Arduino.h>
#include "Get_readings.h"
#include "PID_controller.h"


int calculate_error(const int digital[9]) {
    // Weights: L3,R3=30, L2,R2=20, L1,R1=10, L0,R0=0; negative for left
    const int weights[9] = {-35, -20, -10, -5, 0, 5, 10, 20, 35};
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
