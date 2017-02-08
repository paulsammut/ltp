#include "serial.h"
#include <stdio.h>
#include "test.h"
#include <iostream>

int main(int argc, char *argv[])
{
    unsigned char readBuf[255];
    char port[] = "/dev/ttyUSB0";
    printf("Hello!");

    if(serialOpen(port, _B230400) < 0)
        exit (0);


    while(1) {
        serialRead(readBuf,255,true);
        //printf("Hi!");
    }

    serialClose();
    return ( 1 );
}
