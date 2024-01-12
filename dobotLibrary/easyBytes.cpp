#include "easyBytes.h"
#include <vector>
#include <iterator>
#include <iostream>

template <typename OutIter>
easyBytes::easyBytes(){

};

template <typename OutIter>
void easyBytes::writeBytes(OutIter iter)
{
    for (...) { *iter = data(); ++iter; }
}

template <typename OutIter>
std::vector<uint8_t> easyBytes::toBytes(std::vector<uint8_t> result){

    easyBytes::writeBytes(std::back_inserter(result));
    return result;
}

template <typename OutIter>
uint8_t easyBytes::checksumCalc(std::vector<uint8_t> payload){
    
    return (sizeof(payload) + sizeof(uint8_t) * payload.size());
}