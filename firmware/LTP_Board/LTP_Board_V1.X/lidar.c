#include "lidar.h"
#include "mcc_generated_files/mcc.h"
#include "LTP_system.h"
#include <stdlib.h>
#include <stdio.h>

#define FOSC    (32000000ULL)
#define FCY     (FOSC/2)

#include <libpic30.h>

void lidar_init(void) {
    LIDAR1_PE = 0;
    __delay_ms(10);
    LIDAR1_PE = 1;
    __delay_ms(500);
    

    if (!LIDAR_Write(0x02, 0x80)){
        printf("Fail\r\n");
        __delay_us(50);
    }    
    if (!LIDAR_Write(0x04, 0x08)){
        printf("Fail\r\n");
        __delay_us(50);
    }
    if (!LIDAR_Write(0x1C, 0x00)){
        printf("Fail\r\n");
        __delay_us(50);
    }


}

uint16_t lidar_getDistance(void) {
    uint8_t pData[4] = {0x40, 0x00, 0x00, 0x49};

    LIDAR_Write(0x00, 0x04);
    __delay_ms(100);
    uint8_t response = LIDAR_Read(0x01, pData, 1);
    if (response == 1) {
        printf("Reading: %d", pData[0]);
        LIDAR_Read(0x8f, pData, 2);

        uint16_t distance = pData[0] << 8 || pData[1];
        printf("Distance is: %d", distance);
    }

    return 0;
}

uint8_t LIDAR_Read(uint8_t registerAddress, uint8_t *pData, uint8_t length) {

    MSSP2_I2C_MESSAGE_STATUS status = MSSP2_I2C_MESSAGE_PENDING;
    uint8_t writeBuffer[2];
    uint16_t retryTimeOut, slaveTimeOut;
    uint8_t *pD;

    pD = pData;

    // build the write buffer first
    writeBuffer[0] = registerAddress;

    // Now it is possible that the slave device will be slow.
    // As a work around on these slaves, the application can
    // retry sending the transaction
    retryTimeOut = 0;
    slaveTimeOut = 0;

    while (status != MSSP2_I2C_MESSAGE_FAIL) {
        // write the register address to the Lidar that we want to read
        // printf("Writing register for read!\r\n");
        MSSP2_I2C_MasterWrite(writeBuffer,
                1,
                LIDAR_ADDRESS,
                &status);

        // wait for the message to be sent or status has changed.
        while (status == MSSP2_I2C_MESSAGE_PENDING) {
            // add some delay here

            // timeout checking
            // check for max retry and skip this byte
            if (slaveTimeOut == LIDAR_DEVICE_TIMEOUT)
                return (0);
            else
                slaveTimeOut++;
        }

        if (status == MSSP2_I2C_MESSAGE_COMPLETE) {
            break;
        }

        // if status is  MSSP2_I2C_MESSAGE_ADDRESS_NO_ACK,
        //               or MSSP2_I2C_DATA_NO_ACK,
        // The device may be busy and needs more time for the last
        // write so we can retry writing the data, this is why we
        // use a while loop here

        // check for max retry and skip this byte
        if (retryTimeOut == LIDAR_DEVICE_TIMEOUT) {
            //printf("LIDAR_DEVICE_TIMEOUT\r\n");
            break;
        } else
            retryTimeOut++;
    }

    if (status == MSSP2_I2C_MESSAGE_COMPLETE) {
        //printf("Register write complete. \r\n");
        // this portion will read the byte from the memory location.
        retryTimeOut = 0;
        slaveTimeOut = 0;

        while (status != MSSP2_I2C_MESSAGE_FAIL) {
            // Do a read request for the number of bytes that we want
            MSSP2_I2C_MasterRead(pD,
                    length,
                    LIDAR_ADDRESS,
                    &status);

            // wait for the message to be sent or status has changed.
            while (status == MSSP2_I2C_MESSAGE_PENDING) {
                // add some delay here

                // timeout checking
                // check for max retry and skip this byte
                if (slaveTimeOut == LIDAR_DEVICE_TIMEOUT) {
                    //printf("LIDAR_DEVICE_TIMEOUT on read\r\n");
                    return (0);
                } else
                    slaveTimeOut++;
            }

            if (status == MSSP2_I2C_MESSAGE_COMPLETE) {
                //printf("Read: 0x%02x",pD[0]);
                break;
            }

            // if status is  MSSP2_I2C_MESSAGE_ADDRESS_NO_ACK,
            //               or MSSP2_I2C_DATA_NO_ACK,
            // The device may be busy and needs more time for the last
            // write so we can retry writing the data, this is why we
            // use a while loop here

            // check for max retry and skip this byte
            if (retryTimeOut == LIDAR_RETRY_MAX)
                break;
            else
                retryTimeOut++;
        }
    }

    // exit if the last transaction failed
    if (status == MSSP2_I2C_MESSAGE_FAIL) {
        //printf("Read failed!\r\n");
        return (0);
    }

    // Sucessfull read!
    return (1);
}

uint8_t LIDAR_Write(uint8_t registerAddress, uint8_t pData) {

    MSSP2_I2C_MESSAGE_STATUS status = MSSP2_I2C_MESSAGE_PENDING;
    uint8_t writeBuffer[2];
    uint16_t retryTimeOut, slaveTimeOut;

    // build the write buffer first
    writeBuffer[0] = registerAddress;
    writeBuffer[1] = pData;

    // Now it is possible that the slave device will be slow.
    // As a work around on these slaves, the application can
    // retry sending the transaction
    retryTimeOut = 0;
    slaveTimeOut = 0;

    while (status != MSSP2_I2C_MESSAGE_FAIL) {
        // write the register address to the Lidar that we want to read
        //printf("writing!\r\n");
        MSSP2_I2C_MasterWrite(writeBuffer,
                2,
                LIDAR_ADDRESS,
                &status);

        // wait for the message to be sent or status has changed.
        while (status == MSSP2_I2C_MESSAGE_PENDING) {
            // add some delay here

            // timeout checking
            // check for max retry and skip this byte
            if (slaveTimeOut == LIDAR_DEVICE_TIMEOUT)
                return (0);
            else
                slaveTimeOut++;
        }

        if (status == MSSP2_I2C_MESSAGE_COMPLETE)
            break;

        // if status is  MSSP2_I2C_MESSAGE_ADDRESS_NO_ACK,
        //               or MSSP2_I2C_DATA_NO_ACK,
        // The device may be busy and needs more time for the last
        // write so we can retry writing the data, this is why we
        // use a while loop here

        // check for max retry and skip this byte
        if (retryTimeOut == LIDAR_DEVICE_TIMEOUT)
            return (0);
        else
            retryTimeOut++;
    }

    if (status == MSSP2_I2C_MESSAGE_FAIL) {
        return (0);
    }


    // Sucessfull write!
    return (1);
}

/*
switch(pStatus){
    case MSSP2_I2C_MESSAGE_FAIL: 
        printf("MSSP2_I2C_MESSAGE_FAIL\n\r"); break;
    case MSSP2_I2C_MESSAGE_PENDING:
        printf("MSSP2_I2C_MESSAGE_PENDING\n\r");break;
    case MSSP2_I2C_MESSAGE_COMPLETE: 
        printf("MSSP2_I2C_MESSAGE_COMPLETE\n\r");break;
    case MSSP2_I2C_STUCK_START: 
        printf("MSSP2_I2C_STUCK_START\n\r");break;
    case MSSP2_I2C_MESSAGE_ADDRESS_NO_ACK: 
        printf("MSSP2_I2C_MESSAGE_ADDRESS_NO_ACK\n\r");break;
    case MSSP2_I2C_DATA_NO_ACK: 
        printf("MSSP2_I2C_DATA_NO_ACK\n\r");break;
    case MSSP2_I2C_LOST_STATE: 
        printf("MSSP2_I2C_LOST_STATE\n\r");break;
    default: break;
}
 */
