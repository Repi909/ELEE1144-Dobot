#pragma once
#ifndef IRSENSOR_H
#define IRSENSOR_H

#include "Arduino.h"

class IrSensor{

    public:
        IrSensor();
        bool BlockPresent();
        uint16_t BlockTypeDetector();
    
    private:
        uint16_t ReadSensor();
};

#endif
