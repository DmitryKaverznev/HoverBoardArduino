#include "Motors.h"

#include "HoverboardController.h"

#include <Arduino.h>
#include <DueTimer.h>

HoverboardController motors::hoverUp(Serial1);
HoverboardController motors::hoverDown(Serial2);


void static hoverUpTimerInterrupt() {
    motors::hoverUp.timerInterrupt();
}

void static hoverDownTimerInterrupt() {
    motors::hoverDown.timerInterrupt();
}

void motors::set(int16_t steer, int16_t speed) {
    motors::hoverUp.set(steer, speed);
    motors::hoverDown.set(steer, speed);
}

void motors::init() {
    hoverUp.begin();
    hoverDown.begin();

    Timer0.attachInterrupt(hoverUpTimerInterrupt);
    Timer0.start(TIME_SEND);

    Timer1.attachInterrupt(hoverDownTimerInterrupt);
    Timer1.start(TIME_SEND);
}