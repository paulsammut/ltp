#include "serial.h"
#include <stdio.h>
#include "test.h"
#include <iostream>

#define DELIMITER '\r'

int main(int argc, char *argv[])
{
    unsigned char tempBuff[255];
    int bytesRead = 0;
    unsigned char packetBuff[255];
    int packetLength = 0;

    char port[] = "/dev/ttyUSB0";
    printf("Hello!");

    if(serialOpen(port, _B230400) < 0)
        exit (0);


    while(1) {
        bytesRead = serialRead(tempBuff+packetLength,255,false);
        
//        std::copy(tempBuff, tempBuff+bytesRead, packetBuff + packetLength);
       packetLength += bytesRead;

        for(int i = packetLength-bytesRead; i < packetLength; i++)
        {
            if(tempBuff[i] == DELIMITER)
            {
                std::cout << "Yay we got a message!: " << packetLength << " : " ;
                // end of message!
                // take what we have so far and f
               
                tempBuff[packetLength] = 0;
                // reset the packet length
                std::cout << tempBuff << std::endl;
                packetLength = 0;
            }
        }
        //iterate through tempBuff and see what we got

    }

    serialClose();
    return ( 1 );
}
