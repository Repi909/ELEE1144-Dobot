#ifndef Dobot_h
#define Dobot_h

#include "Arduino.h"
class Dobot
{
    public:
        Dobot();
        void printPose();
        void begin();
        void commandFrame(byte comFrame[]);
};

#endif