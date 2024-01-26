#pragma once
#ifndef DOBOT_H
#define DOBOT_H

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "blockMap.h"
#include "irSensor.h"
#include "counter.h"

class Dobot : public irSensor, public blockMap, public Counter
{
    public:
        Dobot();
        void begin();
        void load(uint8_t blockType);
        void unload(uint8_t storageBay);

    private:
        void move(uint8_t blockType, uint8_t counter);
        void makeSafe();
        void suckStart();
        void suckStop();
        //void printPose();

};

#endif