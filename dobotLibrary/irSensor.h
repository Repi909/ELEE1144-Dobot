#pragma once
#ifndef IRSENSOR_H
#define IRSENSOR_H

class irSensor{

    public:
        uint8_t blockDetector();
    
    private:
        uint8_t readSensor();
        uint8_t blockTypeCheck();
}

#endif