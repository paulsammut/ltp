/* 
 * File:   motor.h
 * Author: paul
 *
 * Created on January 31, 2017, 3:22 PM
 */
#include <stdint.h> 


#ifndef MOTOR_H
#define	MOTOR_H

#ifdef	__cplusplus
extern "C" {
#endif

    /**
     * Initializes the PWM signal generator and sets it 0
     */
    void motor_init(void);

    /**
     * Sets the motor speed and direction based on a -100 to 100 setpoint. Negative is counterclockwise
     * and positive is clockwise
     * @param setpoint -100 to 100 setpoint
     */
    void motor_setSpeed(int16_t setpoint);

    /**
     * Scales the -100 to 100 setpoint to PWM value numbers. Gets rid of sign.
     * @param setpoint
     * @return PWM scaled number ready to go into the MCCP compare function.
     */
   uint16_t motor_scaleSetpointPWN(int16_t setpoint);
   
   int8_t motor_getSpeed(void);

#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_H */

