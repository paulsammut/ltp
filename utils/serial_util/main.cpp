#include "serial.h"
 #include <stdio.h>
#include "test.h"
#include <iostream>

int main(int argc, char *argv[])
{
    unsigned char readBuf[255];
    char port[] = "/dev/ttyUSB0";
    printf("Hello!");

    serialOpen(port, _B57600);

    while(1) {
        serialRead(readBuf,255,true);
        //printf("Hi!");
    }

    serialClose();
    return ( 1 );
}
