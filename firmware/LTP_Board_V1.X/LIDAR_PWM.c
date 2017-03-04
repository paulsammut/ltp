#include "LIDAR_PWM.h"
#include "LTP_system.h"
#include <xc.h> 

//#define _DEBUG
#include "dbg.h"

void LIDAR_PWM_Initialize(void) {
    //CCPON enabled; MOD Edge Detect; CCSEL enabled; CCPSIDL disabled; TMR32 32 Bit; CCPSLP disabled; TMRPS 1:1; CLKSEL FOSC/2; TMRSYNC disabled; 
    CCP4CON1L = 0x8030;
    // Clearing IF flag before enabling the interrupt.
    IFS0bits.CCP4IF = 0;
    // Enabling SCCP4 interrupt.
    IEC0bits.CCP4IE = 1;

    // Clearing IF flag before enabling the interrupt.
    IFS1bits.CCT4IF = 0;
    // Enabling SCCP4 interrupt.
    IEC1bits.CCT4IE = 1;
    
        /* Start the Timer */
    CCP4CON1Lbits.CCPON = true;

}

//Compare event interrupt

void __attribute__((interrupt, no_auto_psv)) _CCP4Interrupt(void) {
    LATAbits.LATA9 = !PORTAbits.RA9;
    /* Check if the Timer Interrupt/Status is set */
    if (IFS0bits.CCP4IF) {
        IFS0bits.CCP4IF = 0;
    }
}

//Timer interrupt

void __attribute__((interrupt, no_auto_psv)) _CCT4Interrupt(void) {
    LATAbits.LATA9 = !PORTAbits.RA9;
    if (IFS1bits.CCT4IF) {
        IFS1bits.CCT4IF = 0;
    }
}

uint32_t SCCP4_CAPTURE_Data32Read(void) {
    uint32_t captureVal = 0xFFFFFFFF;

    /* get the timer period value and return it */
    captureVal = CCP4BUFL;
    captureVal |= ((uint32_t) CCP4BUFH << 16);
    return (captureVal);
}


/*
 *  Buffer overflow flag
 * CCP4STATLbits.ICOV
 * 
 * Buffer empty flag
 * CCP4STATLbits.ICBNE
 */

/**
 End of File
 */