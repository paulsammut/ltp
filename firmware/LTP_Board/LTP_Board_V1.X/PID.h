/* 
 * File:   PID.h
 * Author: paul
 *
 * Created on February 1, 2017, 12:17 PM
 */
#include <stdint.h> 
#include "LTP_message.h"

#ifndef PID_H
#define	PID_H

#ifdef	__cplusplus
extern "C" {
#endif

    /**
     * Goes through a PID cycle
     */
    void PID_cycle(void);

    /**
     * To be launched whenever PID mode is activated. Clears the timer and PID values
     */
    void PID_reset(void);
    
    /**
     * Initializes some timer stuff
     */
    void PID_init(void);
    
    /**
     * Sets the desired angle of the PID loop
     * @param p_desiredAngle desired angle in encoder counts. 0-4000
     */
    void PID_setDesiredAngle(uint16_t p_desiredAngle);


#ifdef	__cplusplus
}
#endif

#endif	/* PID_H */

