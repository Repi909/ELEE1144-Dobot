#pragma once
#ifndef IRSENSOR_H
#define IRSENSOR_H

class irSensor{

    public:
        irSensor();
        uint8_t blockDetector();
    
    private:
        uint8_t readSensor();
};

#endif