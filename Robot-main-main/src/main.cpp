#include <Arduino.h>
#include "Get_readings.h"
#include "Motor_control.h"
#include "PID_controller.h"
#include "buzzer.h"
#include "encorder.h"

int thresholds[9];
int readings[9];
int digital[9];
int error = 0;
int previous_error = 0;
int pid_output = 0;
int integral_error = 0;


void setup() {
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
  buzzer_on(1, 100);
  IR_pin_configuration();
  motor_pin_configuration();
  buzzer_on(3, 100);
  Serial.println("IR sensors calibration started.");
  calibrate_IR_sensors(thresholds, 100); // Calibrate IR sensors with 500 samples, store thresholds
  Serial.println("IR sensors calibration completed.");
  buzzer_on(3, 100);

  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT_A), countEncLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT_A), countEncRight, RISING);
  
}

void loop() {
  read_IR_sensors(readings);
  digitalize_with_calibrated_threshold(readings, thresholds, digital);
  error = calculate_error(digital);
  pid_output = compute_pid(error, previous_error, KP, KD);
  previous_error = error;
  
  Serial.print("Leftcounter: " + String(encoderCount_Left));
  Serial.println(" Rightcounter: " + String(encoderCount_Right));
  forward(102, 100, 0); // Use PID output for correction forward( leftSpeed,  rightSpeed,  error);
  delay(100);
}
