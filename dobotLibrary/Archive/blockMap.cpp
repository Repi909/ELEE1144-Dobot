#include "blockMap.h"
#include "ArduinoSTL.h"
//#include <vector>
#include <map>

int bMap[33][23] = {
    //block type 0 (white)
    {170,170,19,84,3,0,0,0,25,67,0,0,24,67,0,0,79,194,0,0,0,0,225},
    {170,170,19,84,3,0,0,0,43,67,0,0,38,67,0,0,79,194,0,0,0,0,193},
    {170,170,19,84,3,0,0,0,64,67,0,0,53,67,0,0,79,194,0,0,0,0,157},
    {170,170,19,84,3,0,0,0,85,67,0,0,67,67,0,0,79,194,0,0,0,0,122},
    {170,170,19,84,3,0,0,0,106,67,0,0,82,67,0,0,79,194,0,0,0,0,86},
    {170,170,19,84,3,0,0,0,106,67,0,0,82,67,0,0,210,193,0,0,0,0,212},
    {170,170,19,84,3,0,0,0,85,67,0,0,67,67,0,0,210,193,0,0,0,0,248},
    {170,170,19,84,3,0,0,0,68,67,0,0,52,67,0,0,210,193,0,0,0,0,24},
    {170,170,19,84,3,0,0,0,48,67,0,0,38,67,0,0,210,193,0,0,0,0,58},
    {170,170,19,84,3,0,0,0,31,67,0,0,25,67,0,0,210,193,0,0,0,0,88},
    
    //block type 1 (red)
    {170,170,19,84,3,0,0,0,55,67,0,0,85,193,0,0,79,194,0,0,0,0,8},
    {170,170,19,84,3,0,0,0,78,67,0,0,246,255,0,0,79,194,0,0,0,0,18},
    {170,170,19,84,3,0,0,0,103,67,0,0,102,193,0,0,79,194,0,0,0,0,199},
    {170,170,19,84,3,0,0,0,67,185,0,0,193,180,0,0,79,194,0,0,0,0,39},
    {170,170,19,84,3,0,0,0,137,67,0,0,90,193,0,0,79,194,0,0,0,0,177},
    {170,170,19,84,3,0,0,0,55,67,0,0,85,193,0,0,210,194,0,0,0,0,133},
    {170,170,19,84,3,0,0,0,78,67,0,0,246,255,0,0,210,194,0,0,0,0,143},
    {170,170,19,84,3,0,0,0,103,67,0,0,102,193,0,0,210,194,0,0,0,0,68},
    {170,170,19,84,3,0,0,0,67,185,0,0,193,180,0,0,210,194,0,0,0,0,164},
    {170,170,19,84,3,0,0,0,137,67,0,0,90,193,0,0,210,194,0,0,0,0,46},

    //block type 2(black)
    {170,170,19,84,3,0,0,0,166,66,0,0,65,195,0,0,79,194,0,0,0,0,172},
    {170,170,19,84,3,0,0,0,185,66,0,0,88,195,0,0,79,194,0,0,0,0,130},
    {170,170,19,84,3,0,0,0,198,66,0,0,110,195,0,0,79,194,0,0,0,0,95},
    {170,170,19,84,3,0,0,0,215,66,0,0,130,195,0,0,79,194,0,0,0,0,58},
    {170,170,19,84,3,0,0,0,229,66,0,0,142,195,0,0,79,194,0,0,0,0,32},
    {170,170,19,84,3,0,0,0,166,66,0,0,65,195,0,0,210,194,0,0,0,0,41},
    {170,170,19,84,3,0,0,0,185,66,0,0,88,195,0,0,210,194,0,0,0,0,255},
    {170,170,19,84,3,0,0,0,198,66,0,0,110,195,0,0,210,194,0,0,0,0,158},
    {170,170,19,84,3,0,0,0,215,66,0,0,130,195,0,0,210,194,0,0,0,0,183},
    {170,170,19,84,3,0,0,0,229,66,0,0,142,195,0,0,210,194,0,0,0,0,157},

    {170,170,19,84,3,0,0,0,52,67,0,0,0,0,0,0,0,0,0,0,0,50}, //home
    {170,170,19,84,3,0,0,0,255,65,0,0,125,67,0,0,79,194,0,0,0,0,152},  //import bay
    {170,170,19,84,3,0,0,0,8,66,0,0,149,195,0,0,81,194,0,0,0,0,244}// export bay
    //suckStart
    //suckStop
}

blockMap::blockMap(){
    bMap;
}

std::vector<uint8_t> getLocation(uint8_t blockType, uint8_t counterValue){

    return bMap.at(blockType + counterValue);
}
