/* 
 * File:   LTP_system.h
 * Author: paul
 *
 * Created on January 24, 2017, 1:56 PM
 */

#ifndef LTP_SYSTEM_H
#define	LTP_SYSTEM_H

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

    /** LTP Modes 

  @Summary
     The type of modes that define behavior during the timer polling phase.
*/
    typedef enum  {
        IDLE,
        SPIN,
        SETPOINT,
        SWEEP,
        STOP
    }LTP_MODE;

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
     * Sets the LTP_modePtr so that we don't have to share data with other parts of the program
     * @param LTP_modePtr LTP mode pointer that contains the address of the value of the current mode
     */
    void LTP_setModePtr(LTP_MODE *modePtr);
    
    /**
     * Checks the uart for bytes to see if we received any control packets. It then acts on these messages.
     */
    void LTP_checkMessages(void);

#ifdef	__cplusplus
}
#endif

#endif	/* LTP_SYSTEM_H */

