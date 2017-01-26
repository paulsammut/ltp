#include <p24FV16KM204.h>

#include "LTP_system.h"

void LTP_system_init(void)
{
    // any system initializations for the LTP
    TRISBbits.TRISB12 = 0; //output - Slave select of pulse counter
    TRISBbits.TRISB6 = 0;   //output - motor direction
    TRISBbits.TRISB5 = 0;   //output - LIDAR Power enable 
    TRISCbits.TRISC3 = 0;   //output - DEBUG_RED led
    TRISAbits.TRISA9 = 0;   //output - DEBUG_GREEN led
    TRISCbits.TRISC2 = 0;   //output - DP1 port
    TRISCbits.TRISC1 = 0;   //output - DP2 port
    
}
