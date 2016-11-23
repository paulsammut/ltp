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
    unsigned char unStuffed[256];

    // initialize the stuffed array
    for(int i = 0; i < 256 ; i++)
        stuffed[i] = 0;

    StuffData(raw, length, stuffed); 


    unsigned long packetLength = 0;
    for(int i = 0; i < 255; i++)
        if(stuffed[i] == 0)
        {
            packetLength = (unsigned long)i;
            std::cout << "breaking at: " << i << std::endl;
            break;
        }

    UnStuffData(stuffed, packetLength, unStuffed); 

    for(int i = 0; i < 15; i++)
    {
        std::cout << "Data:" << i << "\traw: " << std::hex << (int)raw[i] 
            << "\t\tstuffed: " << std::hex << (int)stuffed[i] 
            << "\tunstuffed: " << std::hex << (int)unStuffed[i] << std::endl;

    } 
    return 0;
}
