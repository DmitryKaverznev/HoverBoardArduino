#ifndef DEVISE_H
#define DEVISE_H

#include <Servo.h>

#include "Config.h"

#include "HoverboardController.h"
#include "Camera.h"
#include "Sonar.h"
#include "Motor.h"

#define PIN_BTN_START 2

namespace dev {
    extern HoverboardController hoverUp;
    extern HoverboardController hoverDown;

    extern Camera camera;

    extern Sonar sonar1;
    extern Sonar sonar2;

    extern Servo servoCap;
    extern Motor motor;

    void hoverBoardSet(int16_t steer, int16_t speed);
    void hoverBoardSetSoft(int16_t steer, int16_t time, int16_t speedEnd);
    void hoverBoardRotate180();

    void buttonInit();
    void hoverBoardInit();
    void cameraInit();
    void servoInit();
    void motorInit();
    void sonarInit();
    void timersInit();


    bool getButton();
    void waitButton();

    uint getSonar();
    void waitSonar();

    void openCap();
    void closeCap();

    void upMotor();

    void waitMotorMaxCurr(uint max);
    void motorRun(int16_t speed, int16_t time);\
    void motorCalibration();


    bool goToHouse();   
    void goMeters(uint8_t meters);
}

#endif // DEVISE_H