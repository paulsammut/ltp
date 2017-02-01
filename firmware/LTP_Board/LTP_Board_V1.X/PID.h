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
     * Sets the pointer to the actual angle
     * @param actualAnglePtr Pointer to the actual angle from the encoder.
     */
    void PID_setAnglePtr(uint16_t *actualAnglePtr);

    /**
     * Checks timer 1 to see if it is time to fire
     */
    void PID_poll(void);

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


#ifdef	__cplusplus
}
#endif

#endif	/* PID_H */

