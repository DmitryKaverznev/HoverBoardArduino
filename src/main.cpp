#include <Arduino.h>
#include "Motors.h"


void motorTest() {
    motors::hoverUp.set(200, 100);
    delay(2000);
    motors::hoverUp.set(-200, 100);
    delay(2000);
    
    motors::hoverUp.set(200, -100);
    delay(2000);
    motors::hoverUp.set(-200, -100);
    delay(2000);

    motors::hoverUp.set(0, 100);
    delay(2000);
    motors::hoverUp.set(0, 100);
    delay(2000);

    motors::hoverUp.set(0, -100);
    delay(2000);
    motors::hoverUp.set(0, -100);
    delay(2000);

    motors::hoverUp.set(0, 0);
}

void setup() {
    while (millis() <= 2000);
    

    motors::init();
    Serial.begin(115200);

    motorTest();
}



void loop() {
}