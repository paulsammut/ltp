#include "lidar.h"
#include "mcc_generated_files/mcc.h"
#include "LTP_system.h"
#include "motor.h"

#define _DEBUG
#include "dbg.h"
#include "LTP_message.h"

#define FOSC    (32000000ULL)
#define FCY     (FOSC/2)

#include <libpic30.h>

uint8_t lidar_numCal = 0;

void LIDAR_init(void) {
    
    // turn off the motor while we do this
    motor_setSpeed(0);
    curSamplePtr->angle = 11;
 printf("LIDAR WORK: %d\r\n",curSamplePtr->angle);
    dbg_printf("Initializing LIDAR with reset. \r\n");
    LIDAR1_PE = 0;
    __delay_ms(50);
    LIDAR1_PE = 1;
    __delay_ms(500);

    LIDAR_CONFIG lidar_config;
    lidar_config.SIG_COUNT_VAL = 0x80;
    lidar_config.ACQ_CONFIG_REG = 0x08;
    lidar_config.THRESHOLD_BYPASS = 0x00;

    LIDAR_configure(&lidar_config);
}

uint8_t LIDAR_configure(LIDAR_CONFIG *lidar_config) {
    uint8_t write_success = 0;
    write_success += LIDAR_Write(0x02, lidar_config ->SIG_COUNT_VAL);
    write_success += LIDAR_Write(0x04, lidar_config ->ACQ_CONFIG_REG) << 1;
    write_success += LIDAR_Write(0x1C, lidar_config ->THRESHOLD_BYPASS) << 2;

    if (write_success == 0b0000111)
        return (1);
    else {
        dbg_printf("Configuration failed.\r\n");
        return (0);
    }
}

uint8_t LIDAR_updateDistance(void) {
    uint8_t response;
    uint8_t pData[4];
    uint8_t busy_flag;
    uint16_t busy_counter;
    uint8_t readReq = 0x03; //receiver bias disabled

    if (lidar_numCal == 100) {
        readReq = 0x04;
        lidar_numCal = 0;
    }else
        lidar_numCal ++;
    
    // Send a distance measurement request
    response = LIDAR_Write(0x00, readReq);

    if (response == 0) {
        dbg_printf("Failed to write sample request!\r\n");
        LIDAR_init();
        return 0;
    }

    // Read the System Status bit
    response = LIDAR_Read(0x01, pData, 1);
    if (response == 0) {
        dbg_printf("Failed to  read the System Status bit!\r\n");
        return 0;
    }

    busy_flag = 0x01 & pData[0];

    while (busy_flag == 1) {
        busy_counter++;
        //we are busy so check again!
        __delay_us(500);
        // Read the System Status bit
        response = LIDAR_Read(0x01, pData, 1);
        if (response == 0) {
            dbg_printf("Failed to  read the System Status bit!\r\n");
            return 0;
        }
        busy_flag = 0x01 & pData[0];

        if (busy_flag >= LIDAR_BUSY_FLAG_TIMEOUT) {
            dbg_printf("LIDAR busy flag timeout!\r\n");
            return 0;
        }
    }

    // we are no longer busy!
    response = LIDAR_Read(0x8F, pData, 2);
    if (response == 0) {
        dbg_printf("Failed to  read the measurement!\r\n");
        return 0;
    }

    curSamplePtr->distance = (pData[0] << 8) + pData[1];    
    return 1;
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

    // Successful read!
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

