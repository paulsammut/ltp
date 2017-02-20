#include "serial.h"
#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include "LTP_message.h"
#include "LtpClass.h"

extern "C" 
{ 
    #include "cobs.h" 
}

int decodePacket(const uint8_t *rawPacket, size_t rawPacketLength, struct LTPSample *sample1);

int main(int argc, char *argv[])
{

    char port[] = "/dev/ttyUSB0";
    std::cout << "Program Loaded!" << std::endl;

    unsigned char packetBuffer[255];

    SerialClass serialPortLTP;


    if(serialPortLTP.serialOpen(port, SerialClass::_B230400) < 0)
        exit (0);

    // This flushes the serial port.
    // serialRead(tempBuff,128,false);

    while(1) {
        //serialPortLTP.serialRead(packetBuffer, 128, true);

        int packetLength = serialPortLTP.serialGetPacket(packetBuffer,0x00);
        if(packetLength) {
            printf("\r\nPacket received: ");
            //int i;
            //for (i = 0; i < packetLength; i++)
            //    printf(" 0x%02X ", packetBuffer[i]);

            struct LTPSample curSample;
            if(decodePacket(packetBuffer, packetLength,&curSample))
                printf("Angle: %04d distance: %04d\r\n", curSample.angle, curSample.distance);
            fflush(stdout);
        }
    }
    return ( 1 );
}


/**
 * @brief Decodes a raw COBS packet into an LTP sample.
 *
 * @param rawPacket
 * @param decodedPacket
 *
 * @return
 */
int decodePacket(const uint8_t *rawPacket, size_t rawPacketLength, struct LTPSample *sample1)
{
    uint8_t tempBuff[255];
    size_t tempBuffLength;
    // Make sure the packet is not longer than the limit
    // and that the end of the raw packet has the 0 terminator
    if(rawPacketLength >= 254 || rawPacket[rawPacketLength-1] != 0x00)
        return 0;

    // we decrement rawPacketLength to get rid of the trailing zero
    --rawPacketLength; 
    
    tempBuffLength = cobs_decode(rawPacket, rawPacketLength, tempBuff);

    if(!tempBuffLength)
    {
        return 0;
    }

    *sample1 = *(struct LTPSample*)tempBuff;
    return 1;
}
