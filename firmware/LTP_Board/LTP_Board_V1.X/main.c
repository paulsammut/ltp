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

//#define _DEBUG
#include "mcc_generated_files/mcc.h"
#include "LTP_system.h"
#include "dbg.h"
#define FOSC    (32000000ULL)
#define FCY     (FOSC/2)

#include <libpic30.h>


int main(void) {
    
    // initialize the device with MCC configuration
    SYSTEM_Initialize();
          
    dbg_printf("\r\n");
    dbg_printf("LTP_BOARD_BOOTING..\r\n");

    LTP_system_init();

    DEBUG_RED = 1;
    DEBUG_GREEN = 1;


    LTP_cmdSweep(1500,500,.2);
    
    
    while (1) {    
        LTP_sampleAndSend();
        LTP_poll();
    }

    return -1;
}