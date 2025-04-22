// motor.h
#ifndef MOTOR_H
#define MOTOR_H

#include "HoverboardController.h"

namespace motors {
    extern HoverboardController hoverUp;
    extern HoverboardController hoverDown;

    void set(int16_t steer, int16_t speed);
    void setSoft(int16_t steer, int16_t time, int16_t speedEnd);
    void init();
}

#endif