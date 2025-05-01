#include "Camera.h"


Camera::Camera(USARTClass& cameraSerial) : _cameraSerial(cameraSerial) {}

void Camera::begin() {
  _cameraSerial.begin(115200);
}

void Camera::timerInterrupt() {
    _receive();
}

void Camera::_receive() {
    uint8_t biteLen = sizeof(ReciveData);

    if (_cameraSerial.available() > biteLen)
    {
        uint8_t bites[biteLen];
        _cameraSerial.readBytes(bites, biteLen);
        
        if (START_BITE != bites[0]) return;
        

        uint8_t checksum = bites[0];
        for (uint8_t i = 0; i < biteLen - 1; i++) {
            checksum ^= bites[i];
        }
        
        if (checksum != bites[biteLen - 1]) return;

        _reciveData = {};
        _reciveData.id = (bites[1] << 8) | bites[2];
        _reciveData.cx = (bites[3] << 8) | bites[4];
        _reciveData.cy = (bites[5] << 8) | bites[6];
    }
}

ReciveData Camera::getRecive() {
    return _reciveData;
}