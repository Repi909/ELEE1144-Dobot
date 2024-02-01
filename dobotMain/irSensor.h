#pragma once
#ifndef IRSENSOR_H
#define IRSENSOR_H

#include "Arduino.h"

class irSensor{

    public:
        irSensor();
        bool blockPresent();
        uint16_t blockTypeDetector();
    
    private:
        uint16_t readSensor();
};

#endif
