#include "HoverboardController.h"
#include <DueTimer.h>

HoverboardController::HoverboardController(USARTClass& hoverSerial) : _hoverSerial(hoverSerial) {
    _lastSendTime = 0;
    _idx = 0;
    _bufStartFrame = 0;
    _incomingByte = 0;
    _incomingBytePrev = 0;
}


void HoverboardController::begin() {

    _hoverSerial.begin(HOVER_SERIAL_BAUD);
}

void HoverboardController::set(int16_t steer, int16_t speed) {
    _command.steer = steer;
    _command.speed = speed;
}

SerialFeedback HoverboardController::getFeedback() {
    return _feedback;
}

void HoverboardController::_send() {
    _command.start = (uint16_t)START_FRAME;
    _command.checksum = (uint16_t)(_command.start ^ _command.steer ^ _command.speed);

    _hoverSerial.write((uint8_t *) &_command, sizeof(_command));
}

void HoverboardController::updateReceive() {
    if (_hoverSerial.available()) {
        _incomingByte = _hoverSerial.read();
        _bufStartFrame = ((uint16_t)(_incomingByte) << 8) | _incomingBytePrev;
    }
    else {
        return;
    }

    if (_bufStartFrame == START_FRAME) {
        byte *p = (byte *)&_newFeedback;
        *p++ = _incomingBytePrev;
        *p++ = _incomingByte;
        _idx = 2;	
    } else if (_idx >= 2 && _idx < sizeof(SerialFeedback)) {
        byte *p = (byte *)&_newFeedback;
        *p++ = _incomingByte; 
        _idx++;
    }	
    
    if (_idx == sizeof(SerialFeedback)) {
        uint16_t checksum;
        checksum = (uint16_t)(_newFeedback.start ^ _newFeedback.cmd1 ^ _newFeedback.cmd2 ^ _newFeedback.speedR_meas ^ _newFeedback.speedL_meas
                            ^ _newFeedback.batVoltage ^ _newFeedback.boardTemp ^ _newFeedback.cmdLed);

        if (_newFeedback.start == START_FRAME && checksum == _newFeedback.checksum) {
            memcpy(&_feedback, &_newFeedback, sizeof(SerialFeedback));
        }
        _idx = 0;
    }

    _incomingBytePrev = _incomingByte;
}

void HoverboardController::timerInterrupt() {
    _send();
}
