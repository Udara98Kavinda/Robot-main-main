#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

#define buzzer 12


void buzzer_on(int count, int t){
    for(int i=0; i<count; i++){
        digitalWrite(buzzer,HIGH);
        delay(t);
        digitalWrite(buzzer,LOW);
        delay(t);
    }
}

#endif