#include "Device.h"

bool dev::goToHouse() {
    hoverBoardSetSoft(0, 1000, HOVERBOART_SPEED);
    delay(1000);

    while (true) {  
        ReciveData data = camera.getRecive();
        uint dist = getSonarAverage(10);
        
        bool sonar = dist != 0 && dist < SONAR_DIST;
        bool camera = data.id == CAMERA_CODE && data.w < CAMERA_DIST;
        

        if (camera) { 
            return true; 
        } else if (sonar) {
            return false;
        }
        

        hoverBoardSet(0, HOVERBOART_SPEED);
    }
}

int sign(int x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

void dev::goMeters(uint8_t meters) {
    uint time = abs(meters * HOVERBOART_TIME_METER);

    hoverBoardSetSoft(0, time / 4, HOVERBOART_SPEED * sign(meters));
    delay(time / 4);
    hoverBoardSet(0, HOVERBOART_SPEED * sign(meters));
    delay(time / 2);
    hoverBoardSetSoft(0, time / 4, 0);
    delay(time / 4);

    hoverBoardSet(0, 0);
}