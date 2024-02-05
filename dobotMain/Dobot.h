#pragma once
#ifndef DOBOT_H
#define DOBOT_H

#include "Arduino.h"
#include "SoftwareSerial.h"
//#include "blockMap.h"
#include "IrSensor.h"
#include "counter.h"

class Dobot : public IrSensor, public Counter {
  
    public:
        Dobot(uint8_t rx, uint8_t tx);
        void Init();
        void Load();
        void Unload(uint8_t storageBay);

    private:
        void Move(uint8_t blockType, uint8_t counter);
        void MakeSafe();
        void SuckStart();
        void SuckStop();
        [[nodiscard]] uint8_t GetLocation(uint8_t blockType, uint8_t counterValue, uint8_t loopIndex);
        void CommandFrame(byte comFrame[]);
        //void printPose();

};

#endif
