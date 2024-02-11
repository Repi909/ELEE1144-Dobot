#include "checksumAlgo.h"

// {170,170,2,10,0,246}; command {header, header, length, ID, r/w, checksum}

//empty constructor
checksumAlgo::checksumAlgo(){};

u_int_8 checksumAlgo::createChecksum(int commandArray[]){

//take size of int array and convert to bytes then multiply by 8 to get size in bits
    size_t result = (8 * sizeof(commandArray));
    return 256 - result
};