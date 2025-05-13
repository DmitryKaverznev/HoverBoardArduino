#include <Arduino.h>
#include "Device.h"



void setup() {
    Serial.begin(115200);
 

    dev::hoverBoardInit();

    dev::hoverBoardSet(0, 0);
    delay(1000);

    dev::cameraInit();
    dev::sonarInit();
    dev::motorInit();
    dev::motorCalibration();
    dev::servoInit();
    dev::closeCap();
    dev::timersInit();


    uint dist = dev::sonar1.readAverage();
    while (dist == 0 || dist > 50) {
        dist = dev::sonar1.readAverage();
    }
    delay(500);
    
    dev::goToHouse();
    dev::hoverBoardSet(0, 0);
    
    delay(500);
    dev::hoverBoardSet(0, -50);
    delay(750);
    dev::hoverBoardSet(0, 0);
    delay(500);
    dev::hoverBoardRotate180();
    dev::hoverBoardSet(0, 0);
    dev::goMeters(2);

    delay(2000);
    dev::openCap();
    dev::upMotor();
}



void loop() {
    Serial.println(dev::getSonar());
}