#include <stdint.h> 
#include "motor.h"
#include "mcc_generated_files/tmr1.h"
#include "PID.h"

void PID_init(void) {
    IFS0bits.T1IF = false;
    TMR1 = 0;

}

void PID_poll(void) {

}

void PID_cycle(void) {

}