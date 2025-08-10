#include <Arduino.h>
#include "Get_readings.h"
#include "Motor_control.h"
#include "PID_controller.h"
#include "buzzer.h"
#include "encoder.h"
#include "turning.h"
#include "action.h"

#include <Wire.h>
#include <QMC5883LCompass.h>
#include "L3G.h"

// Removed display initialization, now handled in oled.h/cpp

int thresholds[9];
int readings[9];
int digital[9];
int integral_error = 0;
int encoder_integral_error = 0;
int cross_type = 0;

//======= IR PID =============
int error = 0;
int previous_error = 0;
int pid_output = 0;
int pid_sign = 0;

//========= Encorder =============
int encoder_error = 0;
int previous_encoder_error = 0;
int encoder_pid_output = 0;
int encoder_sign = 0;

//====== Gyro Initialization ======
float pid_output_gyro = 0;
float integral_error_gyro = 0;
float previous_error_gyro = 0;
float initial_heading = 0;

QMC5883LCompass compass;

void setup() {
  pinMode(buzzer, OUTPUT);
  for(int i = 43;i<52;i++){
    pinMode(i, INPUT);
  }

  Serial.begin(9600);
  Wire.begin();
  compass.init();

  buzzer_on(1, 100);
  IR_pin_configuration();
  motor_pin_configuration();
  buzzer_on(3, 100);
  Serial.println("IR sensors calibration started.");
  calibrate_IR_sensors(thresholds, 100); // Calibrate IR sensors with 200 samples, store thresholds
  Serial.println("IR sensors calibration completed.");
  buzzer_on(3, 100);
  delay(3000);

  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT_A), countEncLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT_A), countEncRight, RISING);
}

void loop() {

  //========= IR PID ==========
  read_IR_sensors(readings);
  digitalize_with_calibrated_threshold(readings, thresholds, digital);
  error = calculate_error(digital);
  pid_output = compute_pid(error, previous_error, KP, KD);
  //pid_output = map(pid_output, 0, 200, 0, 150);
  previous_error = error;

  //========== Encoder PID ==========
  encoder_error = calculate_error_encoder(encoderCount_Left, encoderCount_Right);
  encoder_pid_output = compute_pid_encoder(encoder_error, previous_encoder_error, KPe, KDe, KIe);
  previous_encoder_error = encoder_error;

  if(encoder_error<0){
    encoder_sign = -1;
  }else {
    encoder_sign = 1;
  }

  encoder_pid_output = map(abs(encoder_pid_output), 0, 1024, 0, 150)*encoder_sign;
  Serial.print("Encoder PID Output: "); Serial.println(encoder_pid_output);
/*
  compass.read();

    int x = compass.getX();
    int y = compass.getY();
    int z = compass.getZ();

    int heading = compass.getAzimuth(); // Heading in degrees
    char headingText[3];
    compass.getDirection(headingText, heading);

    Serial.print("X: "); Serial.print(x);
    Serial.print(" Y: "); Serial.print(y);
    Serial.print(" Z: "); Serial.print(z);
    Serial.print("  Heading: "); Serial.print(heading);

    delay(500);
  pid_output_gyro = (headingPID(initial_heading, heading))*1;
  */
  
  //Serial.print("Leftcounter: " + String(encoderCount_Left));
  //Serial.println(" Rightcounter: " + String(encoderCount_Right));
  //Serial.print(" Encoder Error: " + String(encorder_error));
  //Serial.println(" Encoder PID Output: " + String(encorder_pid_output));

  //Serial.println("Forward");
  //left_motor(100, 1, 0);
  //right_motor(100, 1, 0);
  int left_speed = 105 - 0;
  int right_speed = 90 + 10;
  forward(left_speed, right_speed, encoder_pid_output); // Use PID output for correction forward( leftSpeed,  rightSpeed,  error);
  /*
    if(digital[0] == 1 && digital[1] == 1 && digital[2] == 1 && digital[3] == 1 && digital[4] == 1 && digital[5] == 1 && digital[6] == 1 && digital[7] == 1 && digital[8] == 1 ) { //cross
        Serial.println("Cross detected: Cross" );    
        cross_type = 1;
        backward(100,100,0);
        buzzer_on(10, 100);
        stopMotors();
        delay(5000);
        //handleSpecialCross("cross", readings, thresholds);
    }else if ((digital[0] == 1 && digital[1] == 1 && digital[2] == 1 && digital[3] == 1) && digital[4]==1){
      Serial.println("Cross detected: T-Left" );
      cross_type = 2;
      backward(100,100,0);
      stopMotors();
      buzzer_on(5, 100);
      delay(5000);
      //handleSpecialCross("t_left", readings, thresholds);
    }else if ((digital[5] == 1 && digital[6] == 1 && digital[7] == 1 && digital[8] == 1) && digital[4]==1){
      Serial.println("Cross detected: T-Right" );
      cross_type = 3;
      backward(100,100,0);
      stopMotors();
      buzzer_on(2, 100);
      delay(5000);
      //handleSpecialCross("t_right", readings, thresholds);
    }else if(digital[0] == 0 && digital[1] == 0 && digital[2] == 0 && digital[3] == 0 && digital[4] == 0 && digital[5] == 0 && digital[6] == 0 && digital[7] == 0 && digital[8] == 0){
      backward(100,100,0);
      stopMotors();
    }  

    */
    
/*
  delay(1000);
  Serial.println("Turning left");
  turnLeft();  
  delay(1000);
  forward(100, 100, 0);
  delay(1000);
  Serial.println("Turning right");
  turnRight();
  delay(1000);*/
  /*
delay(1000);
turn180(1);
delay(1000);
forward(105, 90, 0);
delay(1000);
turn180(0);
delay(1000);
*/

}
