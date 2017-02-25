#include "tests.h"
#include "dbg.h"
#include <stdint.h>
#include "mcc_generated_files/mcc.h"
#include "lidar.h"
#include "encoder.h"
#include "LTP_system.h"
#include "PID.h"

#define FOSC    (32000000ULL)
#define FCY     (FOSC/2)

#include <libpic30.h>

void test1(void) {
    //uint16_t distance;

    //distance = LIDAR_getDistance();
    //dbg_printf("PWM val is %d, and head angle is %d and the distance is %d\r\n", sweepVal, curAngle, distance);
}


// I2C test

void test2(void) {
    //LIDAR_getDistance();
}

void test3(void) {
    PID_setDesiredAngle(3998);
    encoder_updateAngle();
    LTP_poll();
}

void test4() {
    dbg_printf("Timer val: %u\r\n", TMR1);
    if (IFS0bits.T1IF) {
        //TMR1 = 0;
        dbg_printf("Timer reset!\r\n");
        IFS0bits.T1IF = false;
    }
}

void test5() {
    encoder_updateAngle();
    LTP_poll();
}