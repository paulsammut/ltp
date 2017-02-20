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

//#define _DEBUG
#include "dbg.h"
#include "serialComms.h"
#include "mcc_generated_files/uart1.h"

#include <stdio.h>

/*----- Static Functions -------------------------------------*/

/**
 * Sets the mode of the LTP. 
 * @param _mode The desired mode of the LTP, such as sweep, stop etc.
 */
static void LTP_setMode(LTP_MODE _mode);

/**
 * Keeps track of the serial port and forms packets from incoming byte stream based on 
 * the delimeter.
 * @return 1 if we have a packet, 0 if not. 
 */
static uint8_t LTP_GetPacket(void) ;

// we have a 16 bit timer with a 1:256 prescaler on a 32MHz clock cycle
// which means a 16 us timer count. This gives us our PID loop time 
// relative to that timer in counts. 0x139 is 5ms, 0x3F is 1ms.
uint16_t pollPeriod = 0x139;

LTP_MODE LTP_mode = IDLE;

static uint8_t serial_buffer[255];
static uint16_t serial_buffer_length = 0;
static bool packet_good = false;

// allocate memory for the current sample struct point that is going 
// to get passed to all the subsystems that need it.
struct LtpSample curSampleMem;
struct LtpSample *curSamplePtr = &curSampleMem;

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

    encoder_init();
    LIDAR_init();
    motor_init();
    PID_init();

}

void LTP_sampleAndSend(void) {
    encoder_updateAngle();
    LIDAR_updateDistance();
    //dbg_printf("Angle is: % 4u, and distance is: % 4u\r", *LTP_anglePtr, *LTP_distancePtr);

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
    LTP_GetPacket();

}

static void LTP_setMode(LTP_MODE _mode) {
    LTP_mode = _mode;
}

static uint8_t LTP_GetPacket(void) {
    
    uint8_t max_read_bytes = 20;
    uint8_t read_counter = 0;
    
    // Check to see if we have data in the UART
    while (UART1_StatusGet() == UART1_RX_DATA_AVAILABLE) {
        
        // check to see if we have overflowed the buffer
        if(serial_buffer_length + 1 >= 254){
            serial_buffer_length = 0;
            packet_good = false;
            return 0;
        }
        
        // put the byte into the serial buffer and increment the length
        serial_buffer[serial_buffer_length++] = UART1_Read();
        
        printf("Buffer length : %d\r\n", serial_buffer_length);

        if (serial_buffer[serial_buffer_length - 1] == 'c') {
            if(packet_good)
                return 1;
            else {
                packet_good = true;
                serial_buffer_length = 0;
                return 0;
            }
        }

        // Here we break out of the while loop if we get stuck doing reads for too long.
        // this prevents us from hanging up the rest of the code
        if (++read_counter > max_read_bytes) {
            read_counter = 0;
            return 0;
        }
    }
    
    //should never get here
    return 0;
}