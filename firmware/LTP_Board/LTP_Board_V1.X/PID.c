#include <stdint.h> 
#include "motor.h"
#include "mcc_generated_files/tmr1.h"
#include "PID.h"

// we have a 16 bit timer with a 1:256 prescaler on a 32MHz clock cycle
// which means a 16 us timer count. This gives us our PID loop time 
// relative to that timer in counts. 0x139 is 5ms, 0x3F is 1ms.
uint16_t periodPID = 0x139; 
uint16_t elapsedTime;

void PID_init(void) {
    IFS0bits.T1IF = false;
    TMR1 = 0;

}

void PID_poll(void) {
    if(TMR1 >= periodPID){
        // we run the loop!
        
    }

}

void PID_cycle(void) {

}