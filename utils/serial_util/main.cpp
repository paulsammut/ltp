#include "serial.h"
#include <stdio.h>
#include "test.h"
#include <iostream>

#define DELIMITER '\r'

int main(int argc, char *argv[])
{
    unsigned char tempBuff[255];
    int bytesRead = 0;
    int packetLength = 0;
    // Here we make sure that the packet was read from start to finish.
    bool packetClean = false;

    char port[] = "/dev/ttyUSB0";
    std::cout << "Program Loaded!" << std::endl;


    if(serialOpen(port, _B230400) < 0)
        exit (0);

    // This flushes the serial port.
    serialRead(tempBuff,128,false);


    while(1) {
        if(packetLength >= 255)
        {
            std::cout << "Buffer overflow" << std::endl;
            packetClean = false;
            packetLength = 0;
        }

        bytesRead = serialRead(tempBuff+packetLength,128,false);

        packetLength += bytesRead;

        if(packetLength >= 255)
        {
            std::cout << "Buffer overflow" << std::endl;
            packetClean = false;
            packetLength = 0;
        } else {
            // We scan the "just read portion" for a delimeter
            for(int i = packetLength-bytesRead; i < packetLength; i++)
            {
                if(tempBuff[i] == DELIMITER)
                {
                    // set the end of the packet to 0, which terminates the string
                    tempBuff[packetLength] = 0;

                    if(packetClean)
                    {
                        if(packetLength != 38)
                            std::cout << tempBuff << std::endl;
                    }

                    // reset the packet length
                    packetLength = 0;
                    packetClean = true;
                }
            }
        }
    }

    serialClose();
    return ( 1 );
}