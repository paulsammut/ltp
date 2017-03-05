#include <p24FV16KM204.h>
#include "LTP_system.h"
#include "encoder.h"
#include "lidar.h"
#include "motor.h"
#include "PID.h"
#include "mcc_generated_files/tmr1.h"
#include "sweep.h"
#include "ltpmessage.h"
#include <stdlib.h>
#include "serialComms.h"

#define FOSC    (32000000ULL)
#define FCY     (FOSC/2)

#include <libpic30.h>

//#define _DEBUG
#include "dbg.h"
#include "mcc_generated_files/mssp2_i2c.h"
#include "LIDAR_PWM.h"


#include <stdio.h>

/*----- Static Functions -------------------------------------*/

/**
 * Sets the mode of the LTP. 
 * @param _mode The desired mode of the LTP, such as sweep, stop etc.
 */
static void LTP_setMode(LTP_MODE _mode);

int num_i2c_errors = 0;


// we have a 16 bit timer with a 1:256 prescaler on a 32MHz clock cycle
// which means a 16 us timer count. This gives us our PID loop time 
// relative to that timer in counts. 0x139 is 5ms, 0x3F is 1ms.
uint16_t pollPeriod = 0x139;

LTP_MODE LTP_mode = IDLE;


// allocate memory for the current sample struct point that is going 
// to get passed to all the subsystems that need it.
struct LtpSample curSampleMem;
struct LtpSample *curSamplePtr = &curSampleMem;

struct LtpCommand ltp_command;

void LTP_system_init(void) {
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
    DP1 = 0;
    DP2 = 0;

    encoder_init();
    LIDAR_init();
    motor_init();
    PID_init();
    //LIDAR_PWM_Initialize();

}

void LTP_sampleAndSend(void) {
    
    
    if (!LIDAR_updateDistance()) {
        LTP_recover();
    } else
        sendLTPSample(curSamplePtr);
    
    dbg_printf("Angle is: % 4u, and distance is: % 4u\r", *LTP_anglePtr, *LTP_distancePtr);
    
    // PWM system
    // curSamplePtr->distance_ = LIDAR_PWM_Poll();
    
    
    encoder_updateAngle();   
    sendLTPSample(curSamplePtr);    
}

void LTP_poll(void) {
    // This polls TMR1 to see if it is greater than our polling period.
    if (TMR1 >= pollPeriod) {
        // we run the loop!

        // Here we just reset the timer flag.
        IFS0bits.T1IF = false;

        switch (LTP_mode) {
            case IDLE:
                // do nothing!
                break;
            case SPIN:
                // not much to do here either, we are spinning
                break;
            case SETPOINT:
                // ok now something for us! SETPOINT mode means we just run the 
                // PID_cycle function. We are confident that whoever put us in setpoint
                // mode also set the setpoint. haha!
                PID_cycle();
                break;
            case SWEEP:
                // almost same deal as SETPOINT, with the exception that we have a master
                // sweep control loop that sets the setpoint that we also have to run. Cool!
                sweep_cycle();
                PID_cycle();
                break;
            case STOP:
                motor_setSpeed(0);
                LTP_setMode(IDLE);
                break;

        }
        TMR1 = 0x0000;
    }
}

void LTP_cmdSweep(uint16_t arg_a, uint16_t arg_b, double val_f) {
    sweep_set(arg_a, arg_b, val_f);
    LTP_setMode(SWEEP);
}

void LTP_cmdSpin(uint16_t motorSpeed) {
    motor_setSpeed(motorSpeed);
    LTP_setMode(SPIN);
}

void LTP_cmdStop(void) {
    motor_setSpeed(0);
    LTP_setMode(IDLE);
}

void LTP_cmdSetpoint(uint16_t setpoint) {
    PID_setDesiredAngle(setpoint);
    LTP_setMode(SETPOINT);
}

void LTP_checkMessages(void) {
    if (ReadLtpCommand(&ltp_command)) {
        switch (ltp_command.cmdtype_) {
            case MSG_STOP:
                LTP_cmdStop();
                break;
            case MSG_SPIN:
                LTP_cmdSpin(ltp_command.param1_);
                //wLTP_recover();
                break;
            case MSG_SWEEP:
                LTP_cmdSweep(ltp_command.param1_, ltp_command.param2_, ((double) ltp_command.param3_) / 10);
                break;
            case MSG_POSITION:
                LTP_cmdSetpoint(ltp_command.param1_);
                break;
        }
    }
}

static void LTP_setMode(LTP_MODE _mode) {
    LTP_mode = _mode;
}

void LTP_recover(void) {
    DEBUG_RED = 1;
    num_i2c_errors ++;
    DP2 = 1; // this is my debug test point out so i can trigger my scope
    SSP2CON1bits.SSPEN = 0; // disable the i2c peripheral
    SCL_TRIS = 0; //output
    SDA_TRIS = 1; //input

    //SDA input and let float
    // Toggle the SCL line to get any data out of the slave
    int i;
    for (i = 0; i < 9; i++) {
        SCL = 0;        __delay_us(10);        SCL = 1;        __delay_us(10);
    }

    //START CONDITION
    SDA_TRIS = 0; //output
    __delay_us(5);    SDA = 0;    __delay_us(5);    SCL = 0;    __delay_us(5);

    //STOP CONDITION
    SCL = 1;    __delay_us(5);    SDA = 1;    __delay_us(5);

    // Set the pins to input which is required to re-enable the i2c peripheral
    SCL_TRIS = 1;
    SDA_TRIS = 1;

    MSSP2_I2C_Initialize();
    DP2 = 0;
    DEBUG_RED = 0;
}