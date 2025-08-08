
#include <Arduino.h>
#include "Motor_control.h"

void motor_pin_configuration() {
  pinMode(LM_EN, OUTPUT);
  pinMode(LM_FW, OUTPUT);
  pinMode(LM_BW, OUTPUT);
  pinMode(RM_EN, OUTPUT);
  pinMode(RM_FW, OUTPUT);
  pinMode(RM_BW, OUTPUT);
}

void setMotorSpeed(int leftSpeed, int rightSpeed, int error) {
  analogWrite(LM_EN, leftSpeed + error);
  analogWrite(RM_EN, rightSpeed - error);
}

void forward(int leftSpeed, int rightSpeed, int error) {
  digitalWrite(LM_FW, HIGH);
  digitalWrite(LM_BW, LOW);
  digitalWrite(RM_FW, HIGH);
  digitalWrite(RM_BW, LOW);
  setMotorSpeed(leftSpeed, rightSpeed, error);
}

void backward(int leftSpeed, int rightSpeed, int error) {
  digitalWrite(LM_FW, LOW);
  digitalWrite(LM_BW, HIGH);
  digitalWrite(RM_FW, LOW);
  digitalWrite(RM_BW, HIGH);
  setMotorSpeed(leftSpeed, rightSpeed, error);
}

void stopMotors() {
  setMotorSpeed(0, 0, 0);
}