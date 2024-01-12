#include "blockMap.h"
#include <vector>
#include <map>

std::vector<std::vector<uint8_t>> bMap = {
    
    {170,170,19,84,3,0,0,0,52,67,0,0,0,0,0,0,0,0,0,0,0,50}, //home
    {170,170,19,84,3,0,0,0,0x48,0x43,0,0,0x70,0xc3,0,0,0x5c,0xc2,0,0,0,0,205},  //loading
    };

blockMap::blockMap(){
    bMap;
};

std::vector<uint8_t> accessValue(uint8_t blockType, uint8_t counterValue){

    return bMap.at(blockType + counterValue);
};