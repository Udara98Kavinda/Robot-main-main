#include <Arduino.h>
#include "Get_readings.h"
#include "PID_controller.h"
#include <QMC5883LCompass.h>

static float lastError = 0;
static float integral = 0;

//=========== IR PID ==========

int calculate_error(const int digital[9]) {
    // Weights: L3,R3=30, L2,R2=20, L1,R1=10, L0,R0=0; negative for left
    const int weights[9] = {-8, -6, -4, -2, 0, 2, 4, 6, 8};
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


//================ Encoder PID ==========

int calculate_error_encoder(long encoderCount_Left, long encoderCount_Right) {
    // Calculate the error based on encoder counts
    // This is a placeholder implementation; adjust as needed
    int error = encoderCount_Right - encoderCount_Left;
    return error;
}

int compute_pid_encoder(int error, int previous_error, float Kp, float Kd, float Ki) {
    // Compute the PID output based on encoder counts
    int derivative = error - previous_error;
    int pid_output = Kp * error + Kd * derivative;
    return pid_output;
}

//=============== Gyro ================================


float headingPID(float targetHeading, float currentHeading) {
    float heading = currentHeading;

    // Calculate shortest direction error
    float error = targetHeading - heading;
    if (error > 180) error -= 360;
    if (error < -180) error += 360;

    // PID calculations
    integral += error;
    float derivative = error - lastError;
    lastError = error;

    float output = Kpc * error + Kic * integral + Kdc * derivative;
    return output; // This should be mapped to motor speeds
}