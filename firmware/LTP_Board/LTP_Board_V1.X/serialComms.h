/* 
 * File:   serialComms.h
 * Author: paul
 *
 * Created on February 19, 2017, 4:29 PM
 */

#ifndef SERIALCOMMS_H
#define	SERIALCOMMS_H

#include "ltpmessage.h"

#ifdef	__cplusplus
extern "C" {
#endif
/**
 * This function takes an LTPSample, converts it a byte array, then encodes it with COBS and then sends
 * it out on the UART
 * @param sendSample Pointer to the sample we want to send out.
 * @return 0 if failed, 1 if successful
 */
    int sendLTPSample(struct LtpSample *sendSample);


#ifdef	__cplusplus
}
#endif

#endif	/* SERIALCOMMS_H */

