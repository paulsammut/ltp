/*
 * File:   lidar.h
 * Author: paul
 *
 * Created on January 26, 2017, 12:33 PM
 */
#include <stdint.h> // needed for the return types of the 

#ifndef LIDAR_H
#define	LIDAR_H

#define LIDAR_RETRY_MAX       100  // define the retry count
#define LIDAR_ADDRESS         0x62 // slave device address
#define LIDAR_DEVICE_TIMEOUT  50   // define slave timeout 

#ifdef	__cplusplus
extern "C" {
#endif


void lidar_init();

uint16_t lidar_getDistance(void);

/**
    @Summary
        Reads a specified number of bytes from the Lidar.

    @Description
        This function does an I2C read by first writing a byte that is the
        register address to the LIDAR with the address specified. It then
        waits a delay while checking on this write message to make sure
        it was sent. Once this write message was sent succesfully, it then
        sends a read command with the specified number of read bytes.

    @Preconditions
        None

    @Param
        address - The address of the i2c peripheral to be accessed

    @Param
        length - The number of bytes to read.

    @Param
        *pdata - A pointer to the memory location where received data will
                 be stored

    @Returns
        0 if read was unsuccessful, 1 if the read was successful
*/

uint8_t LIDAR_Read(uint8_t registerAddress, uint8_t *pData, uint8_t length);


#ifdef	__cplusplus
}
#endif

#endif	/* LIDAR_H */

