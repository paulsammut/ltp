#include <p24FV16KM204.h>
#include "LTP_system.h"
#include "encoder.h"
#include "lidar.h"
#include "motor.h"
#include "PID.h"
#include "mcc_generated_files/tmr1.h"
#include "sweep.h"
#include "dbg.h"


// we have a 16 bit timer with a 1:256 prescaler on a 32MHz clock cycle
// which means a 16 us timer count. This gives us our PID loop time 
// relative to that timer in counts. 0x139 is 5ms, 0x3F is 1ms.
uint16_t pollPeriod = 0x139;

void LTP_system_init(void) {
    // any system initializations for the LTP

    //All TRIS pins set for ALL peripherals
    TRISBbits.TRISB6 = 0; //output - motor direction
    TRISCbits.TRISC3 = 0; //output - DEBUG_RED led
    TRISAbits.TRISA9 = 0; //output - DEBUG_GREEN led
    TRISCbits.TRISC2 = 0; //output - DP1 port
    TRISCbits.TRISC1 = 0; //output - DP2 port
    TRISBbits.TRISB12 = 0; //output - Slave select of pulse counter
    TRISBbits.TRISB5 = 0; //output - LIDAR Power enable 

    SS_ENCODER = 1; //idle high
    LIDAR1_PE = 1; // turn on lidar
    DEBUG_GREEN = 0;
    DEBUG_RED = 0;

    encoder_init();
    LIDAR_init();
    motor_init();
    PID_init();

}

void LTP_poll(void) {
    if (TMR1 >= pollPeriod) {
        // we run the loop!

        IFS0bits.T1IF = false;

        //sweep_cycle();
        PID_cycle();
        TMR1 = 0x0000;
    }
}
