#include <p24FV16KM204.h>
#include "LTP_system.h"
#include "encoder.h"
#include "lidar.h"

void LTP_system_init(void)
{
    // any system initializations for the LTP
    
    //All TRIS pins set for ALL peripherals
    TRISBbits.TRISB6 = 0;   //output - motor direction
    TRISCbits.TRISC3 = 0;   //output - DEBUG_RED led
    TRISAbits.TRISA9 = 0;   //output - DEBUG_GREEN led
    TRISCbits.TRISC2 = 0;   //output - DP1 port
    TRISCbits.TRISC1 = 0;   //output - DP2 port
    TRISBbits.TRISB12 = 0; //output - Slave select of pulse counter
     TRISBbits.TRISB5 = 0;   //output - LIDAR Power enable 
     
    SS_ENCODER = 1; //idle high
    LIDAR1_PE = 1;  // turn on lidar
    DEBUG_GREEN = 0;
    DEBUG_RED =0;
     
    encoder_init();
    lidar_init();
    
    
}
