#include "motor.h"
#include "LTP_system.h"
#include "mcc_generated_files/mccp1_compare.h"
#include "stdlib.h"

const unsigned int period = 0x03E8 / 2;
int8_t cur_setpoint = 0;

void motor_init(void) {
    motor_setSpeed(cur_setpoint);
}

void motor_setSpeed(int8_t setpoint) {
    //The pwm value is going to be 100  to -100. 
    cur_setpoint = setpoint;
    
    // Do a bounds check and clip if necassary. 
    
    if(cur_setpoint > 100)
        cur_setpoint = 100;
    if(cur_setpoint < -100)
        cur_setpoint = -100;

    // Set the motor direction
    if (cur_setpoint < 0) {
        MOTOR_DIR = 1;
    } else
        MOTOR_DIR = 0;

    uint16_t scaled_setpoint = motor_scaleSetpointPWN(cur_setpoint);

    MCCP1_COMPARE_DualEdgeBufferedConfig(0, scaled_setpoint);

}

uint16_t motor_scaleSetpointPWN(int8_t setpoint) {

    // setpoint is from -100 to 100 while PWM val is 0 to 1000;
    uint16_t tempVal = abs(setpoint);
    return (tempVal * 10);
}

int8_t motor_getSpeed(void){
    return cur_setpoint;
}