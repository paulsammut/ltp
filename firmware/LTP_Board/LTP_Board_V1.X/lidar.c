#include "lidar.h"
#include "mcc_generated_files/mcc.h"
#include "LTP_system.h"
#include <stdlib.h>


void lidar_init(void){
   
}

uint16_t lidar_getDistance(void){
    uint8_t *pData = malloc(sizeof(*pData));
    *pData = 0x40;
    uint8_t length = 1;
    uint16_t address = 0xC4;
    MSSP2_I2C_MESSAGE_STATUS pStatus =MSSP2_I2C_MESSAGE_COMPLETE;
    
     MSSP2_I2C_MasterWrite(pData, length, address, &pStatus);
    
    switch(pStatus){
        case MSSP2_I2C_MESSAGE_FAIL                        : printf("MSSP2_I2C_MESSAGE_FAIL\n\r"); break;
        case MSSP2_I2C_MESSAGE_PENDING                : printf("MSSP2_I2C_MESSAGE_PENDING\n\r");break;
        case MSSP2_I2C_MESSAGE_COMPLETE            : printf("MSSP2_I2C_MESSAGE_COMPLETE\n\r");break;
        case MSSP2_I2C_STUCK_START                         : printf("MSSP2_I2C_STUCK_START\n\r");break;
        case MSSP2_I2C_MESSAGE_ADDRESS_NO_ACK    : printf("MSSP2_I2C_MESSAGE_ADDRESS_NO_ACK\n\r");break;
        case MSSP2_I2C_DATA_NO_ACK    : printf("MSSP2_I2C_DATA_NO_ACK\n\r");break;
        case MSSP2_I2C_LOST_STATE    : printf("MSSP2_I2C_LOST_STATE\n\r");break;
    }
            
    free(pData); // free the resources!
    return 0;
}