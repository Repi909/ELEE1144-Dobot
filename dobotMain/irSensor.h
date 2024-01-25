#pragma once
#ifndef IRSENSOR_H
#define IRSENSOR_H

#include "Arduino.h"

class irSensor{

    public:
        irSensor();
        bool blockPresent();
        uint8_t blockTypeDetector();
    
    private:
        uint8_t readSensor();
};

#endif
