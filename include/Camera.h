#ifndef CAMERA_H
#define CAMERA_H

#include <Arduino.h>

#define BITE_LEN 2
#define START_BITE 0xAB

class Camera {
public:
    Camera(USARTClass& cameraSerial);
    void timerInterrupt();
    void begin();
    uint16_t getCode();
private:
    USARTClass& _cameraSerial;
    
    uint16_t _code = 0;
    void _receive();
    
};

#endif