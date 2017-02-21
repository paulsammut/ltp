/* Sammut Tech LLC. All Rights Reserved.
 */

#ifndef __SERIAL_H_
#define __SERIAL_H_

#include <stdint.h>
#include <stdlib.h>
#include <termios.h>

#define FALSE 0
#define TRUE 1
class SerialClass
{
    private:
        int fd; // file handle for the device
        struct termios oldtio,newtio;

        // Members for packet length
        int BUFF_LENGTH;  
        unsigned char *tempBuff;
        int bytesRead;
        int packetLength;
        bool packetClean;
        bool portOpen;
        
    public:

        SerialClass(void);

        ~SerialClass(void);

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
        int SerialOpen(const char *port, serialSpeed baudrate);

        /**
         * @brief Does a serial port read with an optional print to screen.
         *
         * @param sReadBuf Pointer to the read buffer that will be filled with read bytes.
         * @param maxNumBytes Max number of bytes to read from the port.
         * @param verbose If true, this prints the received bytes
         *
         * @return Returns the number of bytes read.
         */
        int SerialRead(uint8_t *sReadBuf, uint8_t maxNumBytes, bool verbose = false);  


        /**
         * @brief Closes the serial port
         *
         * @return 0 if fail, 1 if successful  
         */
        int SerialClose(void);

        /**
         * @brief  
         *
         * @param packetBuffer
         * @param delimeter
         *
         * @return 
         */
        int SerialGetPacket(unsigned char *packetBuffer, unsigned char delimeter);

        
        /**
         * @brief Writes the array to serial port. 
         *
         * @param write_array
         *
         * @return 
         */
        int SerialWrite(uint8_t *write_array, uint16_t write_array_length);
};
#endif
