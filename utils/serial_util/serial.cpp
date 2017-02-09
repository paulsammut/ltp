#include "serial.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


int fd; // file handle for the device
int c;  //
int res;

struct termios oldtio,newtio;

volatile int STOP=FALSE;

int serialOpen(char *port, serialSpeed baudrate) {
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
        perror(MODEMDEVICE);
        exit(-1);
    }

    tcgetattr(fd,&oldtio); /* save current port settings */

    memset(&newtio,0, sizeof(newtio));
    newtio.c_cflag = val_BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
    newtio.c_iflag = IGNPAR;
    newtio.c_oflag = 0;

    /* set input mode (non-canonical, no echo,...) */
    newtio.c_lflag = 0;

    newtio.c_cc[VTIME]    = 0;   /* inter-character timer unused */
    newtio.c_cc[VMIN]     = 1;   /* blocking read until 5 chars received */

    tcflush(fd, TCIFLUSH);
    tcsetattr(fd,TCSANOW,&newtio);

    return fd;
}


/**
 * @brief Does a serial port read with an optional print to screen.
 *
 * @param sReadBuf Pointer to the read buffer that will be filled with read bytes.
 * @param maxNumBytes Max number of bytes to read from the port.
 * @param verbose If true, this prints the received bytes
 *
 * @return Returns the number of bytes read.
 */
int serialRead(unsigned char *sReadBuf, uint8_t maxNumBytes, bool verbose) {
    int res;
    res = read(fd,sReadBuf,maxNumBytes);

    if(verbose) {
        // printf which uses stdout is buffered. The larger the buffer, the slower it
        // will post to the terminal. I can either set the buffer to smaller size like
        // the following, or call fflush(stdout) to force a write to the terminal
        // char buffer[10];
        // setvbuf(stdout, buffer, _IOFBF, sizeof(buffer));
        int i = 0;
        for(i = 0; i < res ; i++) {
            printf("%c",sReadBuf[i]);
        }
        fflush(stdout);
    }

    return res;
}


/**
 * @brief Closes the serial port
 *
 * @return 0 on success, negative 1 on failure.
 */
int serialClose(void) {
    // reset the modem
    return tcsetattr(fd,TCSANOW,&oldtio);
}

