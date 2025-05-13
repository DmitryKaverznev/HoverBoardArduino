#include "Sonar.h"

Sonar::Sonar(uint8_t pinTrig, uint8_t pinEcho) {
    _pinTrig = pinTrig;
    _pinEcho = pinEcho;
}

uint Sonar::read() {
    while(millis() - _timer < DELAY_BETWEEN);
    
    digitalWrite(_pinTrig, HIGH);
    delayMicroseconds(DELAY_TRIG);
    digitalWrite(_pinTrig, LOW);

    uint16_t duration = pulseIn(_pinEcho, HIGH, MAX_DIST);
    _timer = millis();
    return duration / DIST_SOUND; 
}

void Sonar::begin() {
    pinMode(_pinTrig, OUTPUT);
    pinMode(_pinEcho, INPUT);

    _timer = millis();
}