#include "Device.h"

#include <Arduino.h>
#include <DueTimer.h>

HoverboardController dev::hoverUp(UART_HOVER_UP);
HoverboardController dev::hoverDown(UART_HOVER_DOWN);

Camera dev::camera(UART_CAMERA);

Sonar dev::sonar1(PIN_SONAR_TRIK_1, PIN_SONAR_ECHO_1);
Sonar dev::sonar2(PIN_SONAR_TRIK_2, PIN_SONAR_ECHO_2);

uint dev::distsStep = 0;
uint dev::dists[SIZE_AVERAGE];



Motor dev::motor(PIN_MOTOR_PWM,
                 PIN_MOTOR_DIR_1,
                 PIN_MOTOR_DIR_2,
                 PIN_MOTOR_ENC_DIR,
                 PIN_MOTOR_ENC_INT,
                 PIN_MOTOR_CURR);

Servo dev::servoCap;

void timerInterrupt() {
    dev::hoverUp.timerInterrupt();
    dev::hoverDown.timerInterrupt();

    dev::camera.timerInterrupt();
}

void encoderInterrupt() {
    dev::motor.encoderInterrupt();
}

void dev::hoverBoardSet(int16_t steer, int16_t speed) {
    dev::hoverUp.set(steer, speed);
    dev::hoverDown.set(steer, speed);
}

void dev::hoverBoardSetSoft(int16_t steer, int16_t time, int16_t speedEnd) {
    dev::hoverUp.setSoft(steer, time, speedEnd);
    dev::hoverDown.setSoft(steer, time, speedEnd);
}

void dev::hoverBoardInit() {
    hoverUp.begin();
    hoverDown.begin();

    hoverBoardSet(0, 0);
    delay(1000);
}

void dev::cameraInit() {
    camera.begin();
}

void dev::servoInit()
{
    servoCap.attach(PIN_SERVOCAP);
}

void dev::motorInit()
{
    motor.init();
    
    attachInterrupt(digitalPinToInterrupt(PIN_MOTOR_ENC_INT), encoderInterrupt, RISING);
}

void dev::timersInit() {
    Timer1.attachInterrupt(timerInterrupt);
    Timer1.start(TIME_SEND);
}

void dev::sonarInit()
{
    sonar1.begin();
    sonar2.begin();

    for (int i = 0; i < 10; i++) {
        dists[i] = getSonar();
    }
}

void dev::buttonInit() {
    pinMode(PIN_BTN_START, INPUT_PULLUP);
}

bool dev::getButton() {
    return digitalRead(PIN_BTN_START);
}

void dev::waitButton() {
    while (! getButton());
    while (getButton());
}

uint dev::getSonar() {
    uint dist1 = dev::sonar1.read();
    uint dist2 = dev::sonar2.read();

    if ((dist1 == 0 && dist2 != 0) || (dist1 != 0 && dist2 == 0)) {
        return max(dist1, dist2);
    } else if (dist1 == 0 || dist2 == 0) {
        return 0;
    }
    
    
    return (dist1 + dist2) / 2;
}


void dev::waitSonarAvarage(uint time)
{
    uint dist = getSonarAverage(time);
    while (dist > SONAR_DIST || dist == 0) {
        dist = getSonarAverage(time);
    }
}

void dev::openCap()
{
    for (int i = servoCap.read(); i < SERVOCAP_OPEN; i++)
    {
        servoCap.write(i);
        delay(33);
    }
}

void dev::closeCap()
{
    servoCap.write(SERVOCAP_CLOSE);
}

void dev::upMotor()
{
    motorRun(SPEED_MOTOR_OPEN, TIME_MOTOR_OPEN);
    motor.set(0);
}

void dev::waitMotorMaxCurr(uint max)
{
    while (dev::motor.getCurr() < max);
}

void dev::motorRun(int16_t speed, int16_t time)
{
    while (abs(motor.getEnc()) < time) {
        motor.set(speed);
    }
}

void dev::motorCalibration()
{
    motor.encReset();
    motor.set(SPEED_MOTOR_CALIB);
    delay(500);
    motor.set(-SPEED_MOTOR_CALIB);
    delay(250);
    waitMotorMaxCurr(MOTOR_MAX_CURR);
    motor.set(0);
    motor.encReset();
}

void dev::hoverBoardRotate180() {
    hoverBoardSet(HOVERBOARD_ROTATE_180_SPEED, 0);
    delay(HOVERBOARD_ROTATE_180_TIME);
    hoverBoardSet(0, 0);
}

// uint dev::getSonarAverage(uint time) {
//     distsStep++;
//     distsStep %= SIZE_AVERAGE;
//     dists[distsStep] = getSonar();

//     ace_sorting::shellSortKnuth(dists, SIZE_AVERAGE);
//     uint average = dists[SIZE_AVERAGE / 2];

//     delay(time);

//     return average;
// }