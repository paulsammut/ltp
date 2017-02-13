#include "serial.h"
#include <stdio.h>
#include <iostream>

int main(int argc, char *argv[])
{

    char port[] = "/dev/ttyUSB0";
    std::cout << "Program Loaded!" << std::endl;

    unsigned char packetBuffer[255];


    if(serialOpen(port, _B230400) < 0)
        exit (0);

    // This flushes the serial port.
    // serialRead(tempBuff,128,false);

    while(1) {
        int packetLength = serialGetPacket(packetBuffer, '\r');
        if(packetLength){
            //printf("Packet received: ");
            //printf("%.*s", packetLength, packetBuffer);
            //fflush(stdout);
        }
    }
    serialClose();
    return ( 1 );
}
