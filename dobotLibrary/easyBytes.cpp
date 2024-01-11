#include "easyBytes.h"
#include <vector>
#include <iterator>

template <typename OutIter>
void writeBytes(OutIter iter)
{
    for (...) { *iter = data(); ++iter; }
}

std::vector<uint8_t> toBytes(std::vector<uint8_t> result){

    writeBytes(std::back_inserter(result));
    return result;
}

uint8_t checksumCalc(std::vector<uint8_t> payload){
    
    return (sizeof(payload) + sizeof(uint8_t) * payload.size());
}