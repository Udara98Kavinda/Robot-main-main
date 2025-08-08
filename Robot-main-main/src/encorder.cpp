#include <Arduino.h>
#include "encorder.h" 

volatile long encoderCount_Left = 0;
volatile long encoderCount_Right = 0;



 void countEncLeft() {
    if(digitalRead(ENCODER_LEFT_B) == LOW) {
        encoderCount_Left++;
    } else {
        encoderCount_Left--;
    }
}

void countEncRight() {
    if(digitalRead(ENCODER_RIGHT_B) == LOW) {
        encoderCount_Right++;
    } else {
        encoderCount_Right--;
    }
}