#pragma once
#ifndef DOBOT_H
#define DOBOT_H

#include "Arduino.h"
#include "SoftwareSerial.h"
//#include "blockMap.h"
#include "irSensor.h"
#include "counter.h"

class Dobot : public irSensor, public Counter {
  
    public:
        Dobot();
        void init();
        void load();
        void unload(uint8_t storageBay);

    private:
        void move(uint8_t blockType, uint8_t counter);
        void makeSafe();
        void suckStart();
        void suckStop();
        [[nodiscard]] uint8_t getLocation(uint8_t blockType, uint8_t counterValue, uint8_t loopIndex);
        void commandFrame(byte comFrame[]);
        //void printPose();

};

#endif
