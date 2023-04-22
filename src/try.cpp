#include "main.h"

void powerDrive(int forwardpower, int turningpower){
left1 = forwardpower + turningpower;
left2 = forwardpower + turningpower;
left3 = forwardpower + turningpower;
left4 = forwardpower + turningpower;
right1 = forwardpower - turningpower;
right2 = forwardpower - turningpower;
right3 = forwardpower - turningpower;
right4 = forwardpower - turningpower;
}

void drivetime( int time ){
    int starttime = millis();


    while (time> millis()-starttime){ 

        powerDrive(127, 0);
    }

        powerDrive(0, 0);
}