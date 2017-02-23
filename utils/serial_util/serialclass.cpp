#include "serialclass.h"
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

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


    fd = open(port, O_RDWR | O_NOCTTY);
    if (fd < 0) {
        fprintf(stderr, "error, counldn't open file %s\n", port);
        return 1;
    }
    if (tcgetattr(fd, &old_termios) != 0) {
        fprintf(stderr, "tcgetattr(fd, &old_termios) failed: %s\n", strerror(errno));
        return 1;
    }
    memset(&new_termios, 0, sizeof(new_termios));
    new_termios.c_iflag = IGNPAR;
    new_termios.c_oflag = 0;
    new_termios.c_cflag = CS8 | CREAD | CLOCAL | HUPCL;
    new_termios.c_lflag = 0;
    new_termios.c_cc[VINTR]    = 0;
    new_termios.c_cc[VQUIT]    = 0;
    new_termios.c_cc[VERASE]   = 0;
    new_termios.c_cc[VKILL]    = 0;
    new_termios.c_cc[VEOF]     = 4;
    new_termios.c_cc[VTIME]    = 1;
    new_termios.c_cc[VMIN]     = 1;
    new_termios.c_cc[VSWTC]    = 0;
    new_termios.c_cc[VSTART]   = 0;
    new_termios.c_cc[VSTOP]    = 0;
    new_termios.c_cc[VSUSP]    = 0;
    new_termios.c_cc[VEOL]     = 0;
    new_termios.c_cc[VREPRINT] = 0;
    new_termios.c_cc[VDISCARD] = 0;
    new_termios.c_cc[VWERASE]  = 0;
    new_termios.c_cc[VLNEXT]   = 0;
    new_termios.c_cc[VEOL2]    = 0;

    if (cfsetispeed(&new_termios, val_BAUDRATE) != 0) {
        fprintf(stderr, "cfsetispeed(&new_termios, val_BAUDRATE) failed: %s\n", strerror(errno));
        return 1;
    }
    if (cfsetospeed(&new_termios, val_BAUDRATE) != 0) {
        fprintf(stderr, "cfsetospeed(&new_termios, val_BAUDRATE) failed: %s\n", strerror(errno));
        return 1;
    }
    if (tcsetattr(fd, TCSANOW, &new_termios) != 0) {
        fprintf(stderr, "tcsetattr(fd, TCSANOW, &new_termios) failed: %s\n", strerror(errno));
        return 1;
    }

    portOpen = true;

    return fd;
}

int SerialClass::SerialRead(uint8_t *sReadBuf, uint8_t maxNumBytes, bool verbose) {
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
    close(fd);
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
    } else if(bytesRead > 0) {
        // We scan the "just read portion" for a delimeter
        for(int i = packetLength-bytesRead; i < packetLength; i++)
        {
            if(tempBuff[i] == delimeter)
            {
                // We have found a delimiter

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

int SerialClass::SerialWrite(uint8_t *write_array, uint16_t write_array_length){
  if(portOpen)
    return (write(fd, write_array, write_array_length));
  return 0;
} 
