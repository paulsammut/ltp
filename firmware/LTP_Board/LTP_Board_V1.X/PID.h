/* 
 * File:   PID.h
 * Author: paul
 *
 * Created on February 1, 2017, 12:17 PM
 */
#include <stdint.h> 

#ifndef PID_H
#define	PID_H

#ifdef	__cplusplus
extern "C" {
#endif

    /**
     * To be launched whenever PID mode is activated. Clears the timer
     * and PID values.
     */
    void PID_int(void);
    
    /**
     * Checks timer 1 to see if it is time to fire
     */
    void PID_poll(void);
    
    /**
     * Goes through a PID cycle
     */
    void PID_cycle(void);
    
    void PID_setAnglePtr(uint16_t *actualAnglePtr);


#ifdef	__cplusplus
}
#endif

#endif	/* PID_H */

