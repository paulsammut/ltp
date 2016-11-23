#include <iostream>
#include <array>
#include <string>
#include <vector>
#include "packet.h"

int main()
{

    const long length = 6;
    unsigned char raw[length] = { 0x2F, 0xA2, 0x20, 0x92, 0x73, 0x02 };
    unsigned char stuffed[256];

    // initialize the stuffed array
    for(int i = 0; i < 256 ; i++)
        stuffed[i] = 0;

    StuffData(raw, length, stuffed); 

    for(int i = 0; i < 15; i++)
    {
        std::cout << "Data:" << i << " raw: " << std::hex << (int)raw[i] 
            << " stuffed: " << std::hex << (int)stuffed[i] << std::endl;
    } 

    return 0;
}
