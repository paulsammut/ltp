#include "serialclass.h"
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

SerialClass::SerialClass(void){
    BUFF_LENGTH = 255;  
    tempBuff = new unsigned char [BUFF_LENGTH];
    bytesRead = 0;
    packetLength = 0;
    packetClean = false;
    portOpen = false;
}

SerialClass::~SerialClass(void){
    if(portOpen){
       this->SerialClose();
       portOpen = false;
    }
    delete[] tempBuff;
}

int SerialClass::SerialOpen(const char *port, serialSpeed baudrate) {
    unsigned long val_BAUDRATE;
    switch(baudrate) {
    case _B57600:
        val_BAUDRATE = B57600;
        break;
    case _B115200:
        val_BAUDRATE = B115200;
        break;
    case _B230400:
        val_BAUDRATE = B230400;
        break;
    }

    // open the serial point and get its file handle
    fd = open(port, O_RDWR | O_NOCTTY );
    if (fd <0) {
        perror(port);
        exit(-1);
    }

    tcgetattr(fd,&oldtio); /* save current port settings */

    memset(&newtio,0, sizeof(newtio));
    newtio.c_cflag = val_BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
    newtio.c_iflag = IGNPAR;
    newtio.c_oflag = 0;

    /* set input mode (non-canonical, no echo,...) */
    newtio.c_lflag = 0;

    newtio.c_cc[VTIME]    = 1;   /* inter-character timer unused */
    newtio.c_cc[VMIN]     = 1;   /* blocking read until 5 chars received */

    tcflush(fd, TCIFLUSH);
    tcsetattr(fd,TCSANOW,&newtio);

    return fd;
}

int SerialClass::SerialRead(unsigned char *sReadBuf, uint8_t maxNumBytes, bool verbose) {
    // Number of bytes read
    int res;
    res = read(fd,sReadBuf,maxNumBytes);

    if(verbose) {
        // printf which uses stdout is buffered. The larger the buffer, the slower it
        // will post to the terminal. I can either set the buffer to smaller size like
        // the following, or call fflush(stdout) to force a write to the terminal
        // char buffer[10];
        // setvbuf(stdout, buffer, _IOFBF, sizeof(buffer));
        for(int i = 0; i < res ; i++) {
            printf("%c",sReadBuf[i]);
        }
        fflush(stdout);
    }
    return res;
}

int SerialClass::SerialClose(void) {
    // reset the modem
    return tcsetattr(fd,TCSANOW,&oldtio);
}

int SerialClass::SerialGetPacket(unsigned char *packetBuffer, unsigned char delimeter) {
    // Check to see if our current packet length is greater than our limit
    if(packetLength >= BUFF_LENGTH)
    {
        std::cout << "Buffer overflow" << std::endl;
        packetClean = false;
        packetLength = 0;
    }

    // Do a serial read
    bytesRead = SerialRead(tempBuff+packetLength,128,false);
    packetLength += bytesRead;

    // Check to see if we overflowed after a serial read
    if(packetLength > BUFF_LENGTH)
    {
        std::cout << "Buffer overflow" << std::endl;
        packetClean = false;
        packetLength = 0;
        return 0;
    } else {
        // We scan the "just read portion" for a delimeter
        for(int i = packetLength-bytesRead; i < packetLength; i++)
        {
            if(tempBuff[i] == delimeter)
            {
                // We have found a delimiter
                // set the end of the packet to 0, which terminates the string
                // this replaces the delimeter with 0

                memcpy(packetBuffer, tempBuff, i+1);
                packetLength = packetLength - i - 1;
                memcpy(tempBuff, tempBuff+i+1, packetLength); 

                if(packetClean)
                    return i+1;

                // reach here if previous packet was not clean
                packetClean = true;
            }
        }
    }
    return 0;
}

