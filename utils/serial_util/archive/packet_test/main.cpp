#include "serial.h"
#include <stdio.h>
#include "test.h"
#include <iostream>
#include <string.h>

#define DELIMITER '\r'

int main(int argc, char *argv[])
{

    char port[] = "/dev/ttyUSB0";
    std::cout << "Program Loaded!" << std::endl;


    if(serialOpen(port, _B230400) < 0)
        exit (0);

    // This flushes the serial port.
    // serialRead(tempBuff,128,false);

    int index=3;
    int size=10;
    unsigned char test[10]; 
    for(int i = 0; i < 10; i++) 
        printf("%u ",test[i]);

    printf("\n\r Returned: %d\r\n",serialGetPacket(test, 13));
    for(int i = 0; i < 10; i++) 
        printf("%u ",test[i]);

    while(1) {
        break;
    }

    serialClose();
    return ( 1 );
}
