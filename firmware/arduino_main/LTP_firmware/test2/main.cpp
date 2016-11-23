#include <iostream>
#include <array>
#include <string>
#include <vector>
#include "cobs2.h"

// I tried to use this other library from here but i don't need it. 
// https://github.com/jacquesf/COBS-Consistent-Overhead-Byte-Stuffing

int main()
{

    size_t length = 3;
    uint8_t raw[3] = { 11, 22, 23};
    uint8_t stuffed[3];
    size_t length_stuffed;

    cobs_encode(raw, length, stuffed);


    for(int i = 0; i < 15; i++)
    {
        std::cout << "Data:" << i << " raw: " << (int)raw[i] 
            << " stuffed: " << (int)stuffed[i] << std::endl;
    } 

    return 0;
}
