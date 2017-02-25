#include "motor.h"
#include "LTP_system.h"
#include "sweep.h"
#include "mcc_generated_files/mccp1_compare.h"
#include "stdlib.h"
#include "math.h"
#include "dbg.h"
#include "PID.h"


int16_t val_a = 0;
int16_t val_b = 0;
int16_t val_d = 0;
int16_t amplitude;
int16_t genPoint;
double val_f = 0;
double val_time = 0;

void sweep_set(uint16_t arg_a, uint16_t arg_b, double arg_f) {
    val_a = arg_a;
    val_b = arg_b;
    val_f = arg_f;

    if (val_a > val_b) {
        // Case 0: we do NOT cross the 0 mark
        amplitude = (val_a - val_b) / 2;
        val_d = val_a - amplitude;
    } else if (val_a < val_b) {
        // Case 1: we crossed 0
        amplitude = ((3998 - val_b) + val_a) / 2;
        val_d = val_a - amplitude;
    } else
        val_d = val_a;
}

void sweep_cycle(void) {
    val_time += TMR1 * 0.000016;
    genPoint = amplitude * sin(2 * 3.14159 * val_f * val_time) + val_d;

    if (genPoint < 0) {
        genPoint = 3998 + genPoint;
    }
    PID_setDesiredAngle(genPoint);
}
