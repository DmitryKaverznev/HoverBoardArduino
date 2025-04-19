#ifndef HOVERBOARDCONTROLLER_H
#define HOVERBOARDCONTROLLER_H

#include <Arduino.h>

#define HOVER_SERIAL_BAUD   115200
#define START_FRAME         0xABCD
#define TIME_SEND           100000

typedef struct {
    uint16_t start;
    int16_t  steer;
    int16_t  speed;
    uint16_t checksum;
} SerialCommand;

typedef struct {
    uint16_t start;
    int16_t  cmd1;
    int16_t  cmd2;
    int16_t  speedR_meas;
    int16_t  speedL_meas;
    int16_t  batVoltage;
    int16_t  boardTemp;
    uint16_t cmdLed;
    uint16_t checksum;
} SerialFeedback;

class HoverboardController {
public:
    HoverboardController(USARTClass& hoverSerial);
    void begin();
    void set(int16_t steer, int16_t speed);
    SerialFeedback getFeedback();
    void timerInterrupt();
    void updateReceive();


private:
    USARTClass& _hoverSerial;
    SerialCommand _command;
    SerialFeedback _feedback;
    SerialFeedback _newFeedback;
    unsigned long _lastSendTime;
    uint8_t _idx;
    uint16_t _bufStartFrame;
    byte _incomingByte;
    byte _incomingBytePrev;

    void _send();
};

#endif // HOVERBOARDCONTROLLER_H
