#pragma once
#ifndef DOBOT_H
#define DOBOT_H

class Dobot
{
    public:
        Dobot();
        void begin();
        void load(uint8_t blockType, uint8_t counter);
        void unload(uint8_t blockType, uint8_t counter);

    private:
        void printPose();
        void move(uint8_t blockType, uint8_t counter);
        void makeSafe();

};

#endif