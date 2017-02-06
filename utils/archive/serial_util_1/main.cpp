/*
 * My first serial terminal program!!!
 * This takes in serial packets from the LTP firmware and unpacks them properly.
 *  - At first it will take a cob packet and display it
 *
 *
 */

// This is an example from https://tty1.net/blog/2009/linux-serial-programming-example_en.html
// This compiles but i don't see how to read and write!

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <iostream>

#define dev "/dev/ttyACM0"

int main(void)
{
    int fd;
    struct termios old_termios;
    struct termios new_termios;

    fd = open(dev, O_RDWR | O_NOCTTY);
    if (fd < 0) {
        fprintf(stderr, "error, counldn't open file %s\n", dev);
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
    new_termios.c_cc[VTIME]    = 0;
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

    if (cfsetispeed(&new_termios, B115200) != 0) {
        fprintf(stderr, "cfsetispeed(&new_termios, B57600) failed: %s\n", strerror(errno));
        return 1;
    }
    if (cfsetospeed(&new_termios, B115200) != 0) {
        fprintf(stderr, "cfsetospeed(&new_termios, B57600) failed: %s\n", strerror(errno));
        return 1;
    }
    if (tcsetattr(fd, TCSANOW, &new_termios) != 0) {
        fprintf(stderr, "tcsetattr(fd, TCSANOW, &new_termios) failed: %s\n", strerror(errno));
        return 1;
    }


    cfmakeraw(&new_termios);
    // Now read() and write() to the device at your heart's delight

    // Before leaving, reset the old serial settings.
    tcsetattr(fd, TCSANOW, &old_termios);
    return 0;
}
