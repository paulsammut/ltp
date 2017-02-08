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
        bytesRead = serialRead(tempBuff,255,true);

        std::copy(tempBuff, tempBuff+bytesRead, packetBuff + packetLength);

        for(int i = 0; i <= bytesRead; i++)
        {
            if(tempBuff[i] == DELIMITER)
            {
                std::cout << "Yay we got a message!" << std::endl;
                // end of message!
                // take what we have so far and f
            }
        }
        //iterate through tempBuff and see what we got

    }

    serialClose();
    return ( 1 );
}
