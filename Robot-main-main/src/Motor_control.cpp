
#include <Arduino.h>
#include "Motor_control.h"
#include "encoder.h"
#include "PID_controller.h"

void motor_pin_configuration() {
  pinMode(LM_EN, OUTPUT);
  pinMode(LM_FW, OUTPUT);
  pinMode(LM_BW, OUTPUT);
  pinMode(RM_EN, OUTPUT);
  pinMode(RM_FW, OUTPUT);
  pinMode(RM_BW, OUTPUT);
}

void right_motor(int speed, bool direction, int error) {
    if(direction == 1){ // Forward
        digitalWrite(RM_FW, HIGH);
        digitalWrite(RM_BW, LOW);
    }else{ // Backward
        digitalWrite(RM_FW, LOW);
        digitalWrite(RM_BW, HIGH);
    }
    analogWrite(RM_EN, speed - error);
}

void left_motor(int speed, bool direction, int error){
    if(direction == 1){ // Forward
        digitalWrite(LM_FW, HIGH);
        digitalWrite(LM_BW, LOW);
    }else{ // Backward
        digitalWrite(LM_FW, LOW);
        digitalWrite(LM_BW, HIGH);
    }
    analogWrite(LM_EN, speed + error);
}

void forward(int leftSpeed, int rightSpeed, int error) {
  right_motor(rightSpeed, 1, error);
  left_motor(leftSpeed, 1, error);
  
}

// Move robot forward for 250 encoder counts with balanced speed
void move_forward_250_counts(int baseSpeed) {
  encoderCount_Left = 0;
  encoderCount_Right = 0;
  int previous_error = 0;
  while (encoderCount_Left < 250 || encoderCount_Right < 250) {
    int error = calculate_error_encoder(encoderCount_Left, encoderCount_Right);
    int pid_output = compute_pid_encoder(error, previous_error, KPe, KDe, KIe);
    previous_error = error;
    int leftSpeed = baseSpeed + pid_output;
    int rightSpeed = baseSpeed - pid_output;
    leftSpeed = constrain(leftSpeed, 0, 255);
    rightSpeed = constrain(rightSpeed, 0, 255);
    if (encoderCount_Right < 250) {
      right_motor(rightSpeed, 1, 0);
    } else {
      right_motor(0, 1, 0); // Stop right motor
    }
    if (encoderCount_Left < 250) {
      left_motor(leftSpeed, 1, 0);
    } else {
      left_motor(0, 1, 0); // Stop left motor
    }
    //delay(1);
  }
  stopMotors();
}

void backward(int leftSpeed, int rightSpeed, int error) {
  right_motor(rightSpeed, 0, error);
  left_motor(leftSpeed, 0, error);
}

void stopMotors() {
  digitalWrite(RM_FW, HIGH);
  digitalWrite(RM_BW, HIGH);
  digitalWrite(LM_FW, HIGH);
  digitalWrite(LM_BW, HIGH);
  analogWrite(RM_EN, 100);
  analogWrite(LM_EN, 100);
}

void stopMotors2(bool right_motor, bool left_motor) {
  if(right_motor) {
    digitalWrite(RM_FW, HIGH);
    digitalWrite(RM_BW, HIGH);
    analogWrite(RM_EN, 100);
  }
  if(left_motor) {
    digitalWrite(LM_FW, HIGH);
    digitalWrite(LM_BW, HIGH);
    analogWrite(LM_EN, 100);
  }
}

