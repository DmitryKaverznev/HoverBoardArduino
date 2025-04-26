#include <Arduino.h>
#include "Device.h"

#define CORRECT_CAMERA_CODE 100

#define TIME_INCREASE 500
#define TIME_NORMAL 500
#define TIME_DECREASE 500

#define MILLIS_INCREASE  TIME_INCREASE
#define MILLIS_NORMAL    MILLIS_INCREASE + TIME_NORMAL
#define MILLIS_DECREASE  MILLIS_NORMAL   + TIME_DECREASE

#define MOTOR_SPEED_STOP 0
#define MOTOR_SPEED 100

#define MOTOR_STEER 0

void setup() {
    Serial.begin(115200);

    device::motorsInit();
    device::cameraInit();
    device::timersInit();
}

void loop() {
    static bool isFinish = false;
    static uint32_t startTime = 0;
    if (isFinish)
        return;

    if (device::camera.getCode() == CORRECT_CAMERA_CODE) {
        if (startTime == 0) {
            startTime = millis();
        }

        uint32_t currentTime = millis() - startTime;

        if (currentTime <= MILLIS_INCREASE) {
            device::motorSetSoft(MOTOR_STEER, TIME_INCREASE, MOTOR_SPEED);
        } else if (currentTime <= MILLIS_NORMAL) {
            device::motorSet(MOTOR_STEER, MOTOR_SPEED);
        } else if (currentTime <= MILLIS_DECREASE) {
            device::motorSetSoft(MOTOR_STEER, TIME_DECREASE, MOTOR_SPEED_STOP);
        } else {
            device::motorSet(MOTOR_STEER, MOTOR_SPEED_STOP);
            isFinish = true;
            startTime = 0;
        }
    } else {
        startTime = 0;
    }
}
