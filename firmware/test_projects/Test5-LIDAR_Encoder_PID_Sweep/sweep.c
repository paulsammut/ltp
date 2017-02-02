#include "motor.h"
#include "LTP_system.h"
#include "sweep.h"
#include "mcc_generated_files/mccp1_compare.h"
#include "stdlib.h"
#include "math.h"
#include "dbg.h"
#include "PID.h"


uint16_t val_a = 0;
uint16_t val_b = 0;
uint16_t val_d = 0;
uint16_t amplitude;
uint16_t genPoint;
double val_f = 0;
double val_time = 0;

void sweep_set(uint16_t arg_a, uint16_t arg_b, double arg_f) {
    val_a = arg_a;
    val_b = arg_b;
    val_f = arg_f;
    
    if(val_a > val_b){
        // Case 0: we do NOT cross the 0 mark
        amplitude = (val_a-val_b)/2;
        val_d = amplitude + val_b;
    }else if( val_a < val_b) {
        
    } else
        val_d = val_a;
    
    
}

void sweep_cycle(void) {
    val_time += TMR1 * 0.0000016;
    genPoint = amplitude*sin(2*3.14159*val_f*val_time)+val_d;
    PID_setDesiredAngle(genPoint);
}
