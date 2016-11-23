#include <iostream>
#include <array>
#include <string>
#include <vector>
#include "packet.h"

int main()
{

    long length = 3;
    unsigned char raw[3] = { 1, 0, 3};
    unsigned char stuffed[3];

    StuffData(raw, length, stuffed); 

    for(int i = 0; i < 15; i++)
    {
        std::cout << "Data:" << i << " raw: " << (int)raw[i] 
            << " stuffed: " << (int)stuffed[i] << std::endl;
    } 

    return 0;
}
