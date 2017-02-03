/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - pic24-dspic-pic32mm : v1.25
        Device            :  PIC24FV16KM202
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC16 1.26
        MPLAB             :  MPLAB X 3.45
 */

#define _DEBUG
#include "mcc_generated_files/mcc.h"
#include "LTP_system.h"
#include "lidar.h"
#include "encoder.h"
#include "mcc_generated_files/mccp1_compare.h"
#include "motor.h"
#include "PID.h"
#include "dbg.h"
#include "sweep.h"
#include "tests.h"

#define FOSC    (32000000ULL)
#define FCY     (FOSC/2)

#include <libpic30.h>

uint16_t curAngle;
uint16_t curDistance;
LTP_MODE curMode = IDLE;


int main(void) {
    
    // initialize the device
    SYSTEM_Initialize();
    
    dbg_printf("\r\n");
    dbg_printf("LTP_BOARD_BOOTING..\r\n");

    LTP_system_init();

    DEBUG_RED = 1;
    DEBUG_GREEN = 1;

    PID_setAnglePtr(&curAngle);
    encoder_setAnglePtr(&curAngle);
    LIDAR_setDistancePtr(&curDistance);
    LTP_setPtrs(&curMode, &curAngle, &curDistance);
    
    PID_setDesiredAngle(100);
    
    sweep_set(3000,2000,.5);
    
    while (1) {    
        LTP_sampleAndSend();
        LTP_poll();
    }

    return -1;
}