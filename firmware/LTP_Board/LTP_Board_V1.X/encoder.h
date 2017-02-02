/* 
 * File:   encoder.h
 * Author: paul
 *
 * Created on January 25, 2017, 10:47 AM
 */
#include <stdint.h>

#ifndef ENCODER_H
#define	ENCODER_H

#ifdef	__cplusplus
extern "C" {
#endif

    
void encoder_init(void);

int16_t encoder_getAngle(void);

void testEncoder(void);

/**
 * Sets the angle pointer that gets updated when encoder_updateAngle() gets called
 * @param anglePtr pointer to be held by the encoder
 */
void encoder_setAnglePtr(uint16_t *anglePtr);

/**
 * Does an encoder read and sets the pointer to the value.
 */
void encoder_updateAngle(void);


#ifdef	__cplusplus
}
#endif

#endif	/* ENCODER_H */

