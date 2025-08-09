#include <Arduino.h>
#include "Motor_control.h"
#include "Get_readings.h"
#include "encoder.h"
#include "turning.h"
#include "task3.h"

void start_front_collector(){ // Start the front collector motor
    analogWrite(CM_EN, 150);
    digitalWrite(CM_FW, HIGH);
    digitalWrite(CM_BW, LOW);
}

void task3(int leftSpeed, int rightSpeed, int error, int limit[6]) {
    start_front_collector();
    forward(leftSpeed, rightSpeed, error);
    if(limit[0] == 1 || limit[1] == 1 || limit[2] == 1 || limit[3] == 1 || limit[4] == 1 || limit[5] == 1) {
        if(limit[2] == 1 || limit[3] == 1){
            turn180(true);
        }
    }
}