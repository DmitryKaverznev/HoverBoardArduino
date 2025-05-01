#include "Device.h"

#include "Camera.h"
#include "HoverboardController.h"

#include <Arduino.h>
#include <DueTimer.h>

HoverboardController device::hoverUp(Serial1);
HoverboardController device::hoverDown(Serial2);

Camera device::camera(Serial3);

void static timerInterrupt() {
    device::hoverUp.timerInterrupt();
    device::hoverDown.timerInterrupt();

    device::camera.timerInterrupt();
}


void device::motorSet(int16_t steer, int16_t speed) {
    device::hoverUp.set(steer, speed);
    device::hoverDown.set(steer, speed);
}

void device::motorSetSoft(int16_t steer, int16_t time, int16_t speedEnd) {
    device::hoverUp.setSoft(steer, time, speedEnd);
    device::hoverDown.setSoft(steer, time, speedEnd);
}

void device::motorsInit() {
    hoverUp.begin();
    hoverDown.begin();
}

void device::cameraInit() {
    camera.begin();
}

void device::timersInit() {
    Timer0.attachInterrupt(timerInterrupt);
    Timer0.start(TIME_SEND);
}