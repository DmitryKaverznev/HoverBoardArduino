#include <Arduino.h>
#include "Device.h"

#define CORRECT_CAMERA_CODE 2

#define TIME_INCREASE 500
#define TIME_NORMAL 500
#define TIME_DECREASE 500


#define MOTOR_SPEED_STOP 0
#define MOTOR_SPEED 100

#define MOTOR_STEER 0

void setup() {
    Serial.begin(115200);

    device::motorsInit();
    device::cameraInit();
    device::timersInit();

    device::hoverUp.setDebug(DebugMode::ENABLE);
}



void loop() {
    Serial.println(device::camera.getRecive().id);
    Serial.println(device::camera.getRecive().cx);
    Serial.println(device::camera.getRecive().cy);

}
