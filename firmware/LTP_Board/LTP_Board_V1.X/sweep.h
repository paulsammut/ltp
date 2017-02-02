/* 
 * File:   sweep.h
 * Author: paul
 *
 * Created on February 1, 2017, 6:14 PM
 */
#include <stdint.h> 

#ifndef SWEEP_H
#define	SWEEP_H

#ifdef	__cplusplus
extern "C" {
#endif

    /**
     * Sets the parameters of the sine wave sweep generator.
     * @param val_a Sweep is defined as clockwise *to* this angle. Encoder units, 0 to 3998.
     * @param val_b Sweep is defined as clockwise *from* this angle. Encoder units, 0 to 3998.
     * @param val_f Frequency in Hertz. 
     */
    void sweep_set(uint16_t val_a, uint16_t val_b, double val_f);

    void sweep_cycle();

#ifdef	__cplusplus
}
#endif

#endif	/* SWEEP_H */

