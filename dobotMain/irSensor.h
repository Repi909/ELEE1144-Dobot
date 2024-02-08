#pragma once
#ifndef IRSENSOR_H
#define IRSENSOR_H

#include "Arduino.h"

class irSensor{

    public:
      uint16_t whiteLowerBound = 400;
      uint16_t whiteUpperBound = 499;
      uint16_t redLowerBound = 500;
      uint16_t redUpperBound = 599;
      uint16_t blackLowerBound = 850;
      uint16_t blackUpperBound = 949;
      
      irSensor();
      bool blockPresent();
      uint16_t blockTypeDetector();
//      void BlockTypeCalibrator();
    
    private:
        uint16_t readSensor();
};

#endif
