#pragma once
#ifndef EASYBYTES_H
#define EASYBYTES_H

#include <vector>
#include <iterator>

class easyBytes{

    public:

    std::vector<uint8_t> toBytes(std::vector<uint8_t> result);
    uint8_t checksumCalc(std::vector<uint8_t> payload);
};

#endif
