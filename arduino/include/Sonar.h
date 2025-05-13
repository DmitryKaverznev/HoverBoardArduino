#ifndef SONAR_H
#define SONAR_H

#include <Arduino.h>


#define DIST_SOUND 58
#define DELAY_TRIG 10
#define MAX_DIST 10000
#define DELAY_BETWEEN 10

class Sonar {
public:
    Sonar(uint8_t pinTrig, uint8_t pinEcho);
    void begin();
    uint read();

    
private:
    uint8_t _pinTrig;
    uint8_t _pinEcho;

    uint8_t _timer;

};

#endif