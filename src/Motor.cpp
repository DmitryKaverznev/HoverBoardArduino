#include "Motors.h"

#include "HoverboardController.h"

#include <Arduino.h>
#include <DueTimer.h>

HoverboardController motors::hoverUp(Serial1);
HoverboardController motors::hoverDown(Serial2);


void static hoverTimerInterrupt() {
    motors::hoverUp.timerInterrupt();
    motors::hoverDown.timerInterrupt();
}



void motors::set(int16_t steer, int16_t speed) {
    motors::hoverUp.set(steer, speed);
    motors::hoverDown.set(steer, speed);
}

void motors::setSoft(int16_t steer, int16_t time, int16_t speedEnd) {
    motors::hoverUp.setSoft(steer, time, speedEnd);
    motors::hoverDown.setSoft(steer, time, speedEnd);
}

void motors::init() {
    hoverUp.begin();
    hoverDown.begin();

    Timer0.attachInterrupt(hoverTimerInterrupt);
    Timer0.start(TIME_SEND);
}