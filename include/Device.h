// motor.h
#ifndef DEVISE_H
#define DEVISE_H

#include "HoverboardController.h"
#include "Camera.h"

namespace device {
    extern HoverboardController hoverUp;
    extern HoverboardController hoverDown;

    extern Camera camera;


    void motorSet(int16_t steer, int16_t speed);
    void motorSetSoft(int16_t steer, int16_t time, int16_t speedEnd);

    void motorsInit();
    void cameraInit();
    void timersInit();
}

#endif // DEVISE_H