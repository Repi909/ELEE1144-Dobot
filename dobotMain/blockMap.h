#pragma once
#ifndef BLOCKMAP_H
#define BLOCKMAP_H

class blockMap
{
    public:
        blockMap();
        uint8_t GetLocation(uint8_t blockType, uint8_t counterValue, uint8_t loopIndex);
};

#endif