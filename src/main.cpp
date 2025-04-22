#include <Arduino.h>
#include "Motors.h"


void setup() {
    while (millis() <= 2000);
    

    motors::init();
    Serial.begin(115200);

    motors::setSoft(0, 5000, 250);
    delay(2000);
    motors::setSoft(0, 5000, 0);
}

void loop() {
}