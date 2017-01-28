/* 
 * File:   lidar.h
 * Author: paul
 *
 * Created on January 26, 2017, 12:33 PM
 */
#include <stdint.h> // needed for the return types of the 

#ifndef LIDAR_H
#define	LIDAR_H

#ifdef	__cplusplus
extern "C" {
#endif

    
    void lidar_init();
    
    uint16_t lidar_getDistance(void);


#ifdef	__cplusplus
}
#endif

#endif	/* LIDAR_H */

