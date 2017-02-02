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

int16_t getAngle(void);

void testEncoder(void);



#ifdef	__cplusplus
}
#endif

#endif	/* ENCODER_H */
