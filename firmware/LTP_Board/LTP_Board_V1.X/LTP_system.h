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
#define LIDAR1_PE LATBbits.LATB7
    

void LTP_system_init(void);
    

#ifdef	__cplusplus
}
#endif

#endif	/* LTP_SYSTEM_H */

