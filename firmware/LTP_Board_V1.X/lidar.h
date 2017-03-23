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
#define LIDAR_BUSY_FLAG_TIMEOUT 1000 // define the busy flag timeout

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct
{
    uint8_t SIG_COUNT_VAL; // maximum number of acquisitions during measurement
    uint8_t ACQ_CONFIG_REG; // acquisition mode control
    uint8_t THRESHOLD_BYPASS; // Peak detection threshold bypass   
    uint8_t OUTER_LOOP_COUNT; // burst measurement count control
    uint8_t MEASURE_DELAY; // Delay between automatic measurements
} LIDAR_CONFIG;

/**
 * Resets the LIDAR and Initializes a default configuration.
 */
void LIDAR_init();

/**
 * Gets a distance measurement from the LIDAR. First it sends a sample request,
 * then it polls the LIDAR to see if the sample request is ready. Then it does a 2 byte read to get
 * the 16 bit distance number. Every 100 samples, it does a calibrated sample. 
 * @return Returns 0 if failed, 1 if successful
 */
uint8_t LIDAR_updateDistance(void);

/**
 * This function does an I2C write of one byte with error checking and monitoring.
 * @param registerAddress The address of the register to be accessed
 * @param pData A pointer to the memory location where received data will be stored
 * @return  0 if read was unsuccessful, 1 if the read was successful
 */
uint8_t LIDAR_Write(uint8_t registerAddress, uint8_t pData);


/**
 * This function does an I2C read by first writing a byte that is the
        register address to the LIDAR with the address specified. It then
        waits a delay while checking on this write message to make sure
        it was sent. Once this write message was sent successfully, it then
        sends a read command with the specified number of read bytes.
 * @param registerAddress   The address of the register to be accessed
 * @param pData     A pointer to the memory location where received data will be stored
 * @param length    The number of bytes to read.
 * @return  0 if read was unsuccessful, 1 if the read was successful
 */
uint8_t LIDAR_Read(uint8_t registerAddress, uint8_t *pData, uint8_t length);

/**
 * Writes the values of the LIDAR_CONFIG struct to the appropriate registers on the LIDAR.
 * @param lidar_config  Pointer to a LIDAR_CONFIG struct containing the configuration values.
 * @return  0 if configuration was unsuccessful, 1 if the configuration was successful
 */
uint8_t LIDAR_configure(LIDAR_CONFIG *lidar_config );


#ifdef	__cplusplus
}
#endif

#endif	/* LIDAR_H */

