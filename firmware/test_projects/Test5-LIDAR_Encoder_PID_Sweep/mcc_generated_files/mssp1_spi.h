/**
  MSSP1_SPI Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    mssp1_spi.h

  @Summary
    This is the generated header file for the MSSP1_SPI driver using MPLAB(c) Code Configurator

  @Description
    This header file provides APIs for driver for MSSP1_SPI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - pic24-dspic-pic32mm : v1.25
        Device            :  PIC24FV16KM204
        Driver Version    :  0.5
    The generated drivers are tested against the following:
        Compiler          :  XC16 1.26
        MPLAB 	          :  MPLAB X 3.45
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#ifndef _MSSP1_SPI_H
#define _MSSP1_SPI_H

/**
  Section: Included Files
*/
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
 Section: Data Type Definitions
*/
//This definition is used during read operation of SPI
#define MSSP1_SPI_DUMMY_DATA 0x0
        
/**
  Section: Interface Routines
*/

/**
  @Summary
    Initializes the MSSP instance : 1

  @Description
    This routine initializes the mssp1_spi driver instance for : 1
    index, making it ready for clients to open and use it.
    This routine must be called before any other MSSP1_SPI routine is called.
    This routine should only be called once during system initialization.

  @Preconditions
    None.

  @Param
    None.

  @Returns
    None.

  @Example
    <code>
    uint16_t   myWriteBuffer[MY_BUFFER_SIZE];
    uint16_t   myReadBuffer[MY_BUFFER_SIZE];
    uint16_t writeData;
    uint16_t readData;
    unsigned int    total;
    MSSP1_SPI_Initialize;
 
    total = 0;
    do
    {
        total  = MSSP1_SPI_Exchange8bitBuffer( &myWriteBuffer[total], MY_BUFFER_SIZE - total, &myWriteBuffer[total]);

        // Do something else...

    } while( total < MY_BUFFER_SIZE );

    readData = MSSP1_SPI_Exchange8bit( writeData);

    </code>

*/
void MSSP1_SPI_Initialize (void);

/**
  @Summary
    Exchanges one byte of data from MSSP1_SPI

  @Description
    This routine exchanges one byte of data from the MSSP1_SPI.
    This is a blocking routine.

  @Preconditions
    The MSSP1_SPI_Initialize routine must have been called for the specified
    MSSP1_SPI driver instance.

  @Param
    data         - Data to be written onto MSSP1_SPI.

  @Returns
    Data read from MSSP1_SPI

  @Example 
    Refer to MSSP1_SPI_Initialize() for an example	
 
*/
uint8_t MSSP1_SPI_Exchange8bit( uint8_t data );

/**
  @Summary
    Exchanges data from a buffer of size one byte from MSSP1_SPI

  @Description
    This routine exchanges data from a buffer of size one byte from the MSSP1_SPI.
    This is a blocking routine.

  @Preconditions
    The MSSP1_SPI_Initialize routine must have been called for the specified
    MSSP1_SPI driver instance.

  @Param
    dataTransmitted         - Buffer of data to be written from MSSP1_SPI.
    bufLen         - Number of words to be exchanged.
    dataReceived         - Buffer of data to be read into MSSP1_SPI.

  @Returns
    Number of words written/read.

  @Example 
    Refer to MSSP1_SPI_Initialize() for an example	
 
*/
uint8_t MSSP1_SPI_Exchange8bitBuffer(uint8_t *dataTransmitted, uint8_t bufLen, uint8_t *dataReceived);

/**
  @Summary
    Gets the status of the buffer if its full.

  @Description
    This routine gets the status of the buffer if its full.

  @Preconditions
    The MSSP1_SPI_Initialize routine must have been called for the specified
    MSSP1_SPI driver instance.

  @Param
    None.

  @Returns
    true - if the buffer is full
    false - if the buffer is not full.

  @Example 
    Refer to MSSP1_SPI_Initialize() for an example	
 
*/
bool MSSP1_SPI_IsBufferFull( void );

/**
  @Summary
    Gets the status of write collision.

  @Description
    This routine gets the status of write collision.

  @Preconditions
    The MSSP1_SPI_Initialize routine must have been called for the specified
    MSSP1_SPI driver instance.

  @Param
    None.

  @Returns
    true - if the write collision has occurred.
    false - if the write collision has not occurred.

  @Example 
    Refer to MSSP1_SPI_Initialize() for an example	
 
*/
bool MSSP1_SPI_HasWriteCollisionOccured( void );

/**
  @Summary
    Gets the status of receive overflow.

  @Description
    This routine gets the status of receive overflow.

  @Preconditions
    The MSSP1_SPI_Initialize routine must have been called for the specified
    MSSP1_SPI driver instance.

  @Param
    None.

  @Returns
    true - if receive overflow has occurred.
    false - if receive overflow has not occurred.

  @Example 
    Refer to MSSP1_SPI_Initialize() for an example	
 
*/
bool MSSP1_SPI_HasReceiveOverflowOccured( void );

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif //_MSSP1_SPI_H
    
/**
 End of File
*/
