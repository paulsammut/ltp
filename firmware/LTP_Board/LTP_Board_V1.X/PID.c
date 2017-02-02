#include <stdint.h> 
#include "motor.h"
#include "mcc_generated_files/tmr1.h"
#include "PID.h"
#include <stdio.h>

// we have a 16 bit timer with a 1:256 prescaler on a 32MHz clock cycle
// which means a 16 us timer count. This gives us our PID loop time 
// relative to that timer in counts. 0x139 is 5ms, 0x3F is 1ms.
uint16_t periodPID = 0x139;
uint16_t usecsElapsed;
uint16_t desiredAngle = 0;
uint16_t *actualAngle;

int16_t iteration_time;
int16_t error;
int16_t error_prior = 0;
int16_t integral = 0;
int16_t derivative = 0;
double KP = .15;
double KI = .0002;
double KD = 0;
int16_t output = 0;

void PID_init(void) {
    TMR1_Start();
}

void PID_reset(void) {
    IFS0bits.T1IF = false;
    TMR1 = 0;

    error_prior = 0;
    integral = 0;
}

void PID_setAnglePtr(uint16_t *actualAnglePtr) {
    actualAngle = actualAnglePtr;
}

void PID_poll(void) {
    if (TMR1 >= periodPID) {
        // we run the loop!

        IFS0bits.T1IF = false;

        PID_cycle();
        TMR1 = 0x0000;
    }
}

void PID_cycle(void) {
    usecsElapsed = TMR1 * 16;
    iteration_time = usecsElapsed; //1000000;

    error = desiredAngle - *actualAngle;
    if (error > 1999)
        error = error - 3998;
    if (error < -1999)
        error = error + 3998;
    
    integral = integral + (error * iteration_time);
    derivative = (error - error_prior) / iteration_time;
    output = KP * error + KI * integral + KD*derivative;
    error_prior = error;

    printf("Actual is: %u desired is: %u error is: %d output is: %d\r\n", *actualAngle, desiredAngle, error, output);
    motor_setSpeed(output);
}

void PID_setDesiredAngle(uint16_t p_desiredAngle) {
    desiredAngle = p_desiredAngle;
}

/*
error_prior = 0
integral = 0
KP = Some value you need to come up (see tuning section below)
KI = Some value you need to come up (see tuning section below)
KD = Some value you need to come up (see tuning section below)

while(1) {
    error = desired_value ? actual_value
    integral = integral + (error*iteration_time)
    derivative = (error ? error_prior)/iteration_time
    output = KP*error + KI*integral + KD*derivative + bias
    error_prior = error
    sleep(iteration_time)
}
 */