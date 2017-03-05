#include "LIDAR_PWM.h"
#include "LTP_system.h"
#include <xc.h> 
#include "mcc_generated_files/uart1.h"

//#define _DEBUG
#include "dbg.h"

// Here we define the number of useconds per count. This is Fosc/20000
#define USECS_PER_COUNT 160


uint32_t capture_start = 0;
uint32_t pwm_measurement = 0;
bool capture_valid = false;
bool pwm_measurement_ready = false;

void LIDAR_PWM_Initialize(void) {
    // empty  out the buffer
    uint32_t dummy;
    while (CCP4STATLbits.ICBNE) {
        dummy = CCP4BUFL;
        dummy = CCP4BUFH;
    }

    LIDAR_PWM_TRIS = 1;
    //CCPON enabled; MOD Edge Detect; CCSEL enabled; CCPSIDL disabled; TMR32 32 Bit; CCPSLP disabled; TMRPS 1:1; CLKSEL FOSC/2; TMRSYNC disabled; 
    CCP4CON1L = 0x8030;
    // Clearing IF flag before enabling the interrupt.
    IFS0bits.CCP4IF = 0;
    // Enabling SCCP4 interrupt.
    IEC0bits.CCP4IE = 1;

    // Clearing IF flag before enabling the interrupt.
    IFS1bits.CCT4IF = 0;
    // Enabling SCCP4 interrupt.
    IEC1bits.CCT4IE = 0;

    /* Start the Timer */
    CCP4CON1Lbits.CCPON = true;

}

//Compare event interrupt
/*
 * The goal is to measure the high pulse of the signal. 
 * This function gets fired on every edge, both rising and falling. 
 * Every time it gets fired, a timer value is written to a buffer.
 * This is a 32 bit timer that overflows every ~4 minutes
 * 
 */
void __attribute__((interrupt, no_auto_psv)) _CCP4Interrupt(void) {
    // Read the buffer value
    uint32_t captureVal = 0xFFFFFFFF;  //don't really have to set it this number. 
    captureVal = CCP4BUFL;
    captureVal |= ((uint32_t) CCP4BUFH << 16);
    DEBUG_GREEN = !DEBUG_GREEN;


    // we are going from low to high. Start of measurement
    if (LIDAR_PWM_PIN) {
        capture_valid = true;
        capture_start = captureVal;
    }// we are going from high to low, so end of measurement
    else if (capture_valid && (captureVal > capture_start)) {
        pwm_measurement = captureVal - capture_start;
        pwm_measurement_ready = true;
        capture_valid = false;
    }
    
    // This is in case we overflow. We just do a simple calculate
   else if (capture_valid && (captureVal < capture_start)) {
        pwm_measurement = (0xFFFFFFFF - capture_start) + captureVal;
        pwm_measurement_ready = true;
    } else
        capture_valid = false;


    /* Check if the Timer Interrupt/Status is set */
    if (IFS0bits.CCP4IF) {
        IFS0bits.CCP4IF = 0;
    }
}


int16_t LIDAR_PWM_Poll(void)
{
    uint32_t poll_timeout_threshold = 0x0FFFFFFF;
    uint32_t poll_timeout_counter = 0;
    
    // This is if we time out, so we can try to recover
    while(!pwm_measurement_ready && (poll_timeout_threshold > poll_timeout_counter))
    {
        Nop();
    }
    
    if(pwm_measurement_ready)
    {
        pwm_measurement_ready = false;
        pwm_measurement = pwm_measurement / USECS_PER_COUNT;
        
        return pwm_measurement;
    }
    
    // this means we timed out
    else
    {
        return 0;
    }  
}
