/* 
 * File:   LTP_system.h
 * Author: paul
 *
 * Created on January 24, 2017, 1:56 PM
 */

#ifndef LTP_SYSTEM_H
#define	LTP_SYSTEM_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

    // Pin definitions
#define DEBUG_GREEN LATAbits.LATA9
#define DEBUG_RED LATCbits.LATC3
#define DP1 LATCbits.LATC2
#define DP2 LATCbits.LATC1
#define MOTOR_DIR LATBbits.LATB6
#define SS_ENCODER LATBbits.LATB12
#define LIDAR1_PE LATBbits.LATB5

    extern struct LtpSample *curSamplePtr;

    /** LTP Modes 

  @Summary
     The type of modes that define behavior during the timer polling phase.
     */
    typedef enum {
        IDLE,
        SPIN,
        SETPOINT,
        SWEEP,
        STOP
    } LTP_MODE;


    /**
     * Initializes the LTP stuff
     */
    void LTP_system_init(void);

    /**
     * Runs the polling of TMR1 to run the time operations based on the current mode. 
     */
    void LTP_poll(void);

    /**
     * Reads the encoder and the lidar, forms a COBS packet and sends it on the UART
     */
    void LTP_sampleAndSend(void);



    /**
     * Sets the pointers  used in the LTP_system to keep track of things
     * @param modePtr Current mode that the system is in
     * @param anglePtr Memory location that holds the latest encoder sample
     * @param distancePtr Memory location that holds the latest distance sample
     */
    void LTP_setPtrs(LTP_MODE *_modePtr, uint16_t *_anglePtr, uint16_t *_distancePtr);

    /**
     * Checks the uart for bytes to see if we received any control packets. It then acts on these messages.
     */
    void LTP_checkMessages(void);


    /**
     * Sets the mode of the LTP. 
     * @param _mode The desired mode of the LTP, such as sweep, stop etc.
     */
    void LTP_setMode(LTP_MODE _mode);

    /**
     * Sets the parameters of the sine wave sweep generator.
     * @param arg_a Sweep is defined as clockwise *to* this angle. Encoder units, 0 to 3998.
     * @param arg_b Sweep is defined as clockwise *from* this angle. Encoder units, 0 to 3998.
     * @param val_f Frequency in Hertz.
     */
    void LTP_cmdSweep(uint16_t arg_a, uint16_t arg_b, double val_f);

    /**
     * Sets the motor speed and direction based on a -100 to 100 setpoint. Negative is counterclockwise
     * and positive is clockwise
     * @param setpoint -100 to 100 setpoint
     */
    void LTP_cmdSpin(uint16_t motorSpeed);

    /**
     * Tells the LIDAR to stop. Simple!
     */
    void LTP_cmdStop(void);

    void LTP_cmdSetpoint(uint16_t setpoint);
#ifdef	__cplusplus
}
#endif

#endif	/* LTP_SYSTEM_H */