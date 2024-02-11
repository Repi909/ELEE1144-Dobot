#include "checksumAlgo.h"
#include <iostream>

int main(){

    checksumAlgo Checksum = new checksumAlgo;
    cout << Checksum.createChecksum(0,0,1,3,5);

    return 0;
}