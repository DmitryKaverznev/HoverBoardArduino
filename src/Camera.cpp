#include "Camera.h"


Camera::Camera(USARTClass& cameraSerial) : _cameraSerial(cameraSerial) {}

void Camera::begin() {
  _cameraSerial.begin(115200);
}

void Camera::timerInterrupt() {
    _receive();
}

void Camera::_receive() {
    if (_cameraSerial.available() > 3)
    {
        uint8_t bites[BITE_LEN];
        _cameraSerial.readBytes(bites, BITE_LEN);

        if (bites[0] == START_BITE)
        {
            _code = ((uint16_t)bites[1] << 8) | bites[2];
        }
    }
}

uint16_t Camera::getCode() {
    return _code;
}