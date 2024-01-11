#pragma once
#ifndef BLOCKMAP_H
#define BLOCKMAP_H

#include <vector>
#include <map>

class blockMap
{
    public:
        blockMap();
        // void createMap(); redundant as map created when object instantiated?
        std::vector<uint8_t> accessValue(uint8_t blockType, uint8_t counterValue);

};

#endif