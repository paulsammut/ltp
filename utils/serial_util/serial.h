/* Sammut Tech LLC. All Rights Reserved.
 */

#ifndef __SERIAL_H_
#define __SERIAL_H_

#include <stdint.h>
#include <stdlib.h>
#include <termios.h>

#define BAUDRATE B230400
#define MODEMDEVICE "/dev/ttyUSB0"
#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define FALSE 0
#define TRUE 1

/**
 * @brief Enum used to set the speed of the serial port.
 */
typedef enum {
    _B57600,
    _B115200,
    _B230400
} serialSpeed;

/**
 * @brief Configures and opens the serial port.
 *
 * @param port character array string containing the port
 * @param baudrate baudrate of the port with serialSpeed enum type
 *
 * @return -1 if failed, device handler if succeeded
 */
int serialOpen(char *port, serialSpeed baudrate);

/**
 * @brief Does a serial read and puts the bytes read in the sReadBuf. It will do a
 * read once the VMIN buffer is full. This buffer is set in the configuration.
 *
 * @param sReadBuf A pointer to a character array where the data read will be stored.
 * @param maxNumBytes 
 *
 * @return 
 */
int serialRead(unsigned char *sReadBuf, uint8_t maxNumBytes, bool verbose = false);  


/**
 * @brief Closes the serial port
 *
 * @return 0 if fail, 1 if successful  
 */
int serialClose(void);

#endif
