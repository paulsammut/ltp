/*
 * File:   lidar.h
 * Author: paul
 *
 * Created on January 26, 2017, 12:33 PM
 */
#include <stdint.h> // needed for the return types of the 

#ifndef LIDAR_H
#define	LIDAR_H

#define LIDAR_ADDRESS         0x62 // slave device address

// The following retry counts were tweaked. Lower counts of 100, and 50 
// cause the system to not work!!
#define LIDAR_RETRY_MAX       10000  // define the retry count 
#define LIDAR_DEVICE_TIMEOUT  5000   // define slave timeout 

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct
{
    uint8_t SIG_COUNT_VAL; // maximum number of acquisitions during measurement
    uint8_t ACQ_CONFIG_REG; // acquisition mode control
    uint8_t THRESHOLD_BYPASS; // Peak detection threshold bypass   
} LIDAR_CONFIG;

void lidar_init();

uint16_t lidar_getDistance(void);

/**
    @Summary
        Writes one byte to the LIDAR. 

    @Description
        This function does an I2C write with error checking and monitoring.

    @Preconditions
        None

    @Param
        registerAddress - The address of the register to be accessed

    @Param
        *pdata - A pointer to the memory location where received data will
                 be stored

    @Returns
        0 if read was unsuccessful, 1 if the read was successful
*/

uint8_t LIDAR_Write(uint8_t registerAddress, uint8_t pData);

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
        registerAddress - The address of the register to be accessed

    @Param
        *pdata - A pointer to the memory location where received data will
                 be stored
    @Param
        length - The number of bytes to read.


    @Returns
        0 if read was unsuccessful, 1 if the read was successful
*/

uint8_t LIDAR_Read(uint8_t registerAddress, uint8_t *pData, uint8_t length);

/**
    @Summary
        Writes the configuration to the LIDAR.

    @Description
        Writes the values of the LIDAR_CONFIG struct to the appropriate registers on the LIDAR.

    @Preconditions
        None

    @Param
        *lidar_config  - Pointer to a LIDAR_CONFIG struct containing the configuration values.

    @Returns
        0 if configuration was unsuccessful, 1 if the configuration was successful
*/

uint8_t LIDAR_configure(LIDAR_CONFIG *lidar_config );


#ifdef	__cplusplus
}
#endif

#endif	/* LIDAR_H */

