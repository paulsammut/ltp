/**
  MSSP1_SPI Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    mssp1_spi.c

  @Summary
    This is the generated source file for the MSSP1_SPI driver using MPLAB(c) Code Configurator

  @Description
    This source file provides APIs for driver for MSSP1_SPI.
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

/**
  Section: Included Files
*/

#include <xc.h>
#include "mssp1_spi.h"

/**
  Section: Driver Interface
*/


void MSSP1_SPI_Initialize (void)
{
    // SMP Middle; CKE Active to Idle; 
    SSP1STAT = 0x0040;
    // SSPEN enabled; WCOL no_collision; CKP Idle:Low, Active:High; SSPM FOSC/8; SSPOV no_overflow; 
    SSP1CON1 = 0x0021;
    // ACKEN disabled; GCEN disabled; PEN disabled; ACKDT acknowledge; RSEN disabled; RCEN disabled; SEN disabled; 
    SSP1CON2 = 0x0000;
    // SBCDE disabled; BOEN disabled; SCIE disabled; PCIE disabled; DHEN disabled; SDAHT 100ns; AHEN disabled; 
    SSP1CON3 = 0x0000;
    // AMSK 0; 
    SSP1MSK = 0x0000;
    // SSPADD 1; 
    SSP1ADD = 0x0001;
}

uint8_t MSSP1_SPI_Exchange8bit( uint8_t data )
{

    SSP1BUF = data;

    while (SSP1STATbits.BF == false)
    {

    }

    return SSP1BUF;
}

uint8_t MSSP1_SPI_Exchange8bitBuffer(uint8_t *dataTransmitted, uint8_t bufLen, uint8_t *dataReceived)
{
    uint16_t bytesWritten = 0;

    if(dataTransmitted != NULL)
    {
        if(dataReceived != NULL)
        {
            while(bytesWritten < bufLen )
            {
                dataReceived[bytesWritten] = MSSP1_SPI_Exchange8bit(dataTransmitted[bytesWritten]);
                bytesWritten++;
            }
        }else
        {
            while(bytesWritten < bufLen )
            {
                MSSP1_SPI_Exchange8bit(dataTransmitted[bytesWritten]);
                bytesWritten++;
            }
        }
    }
    else
    {
        if(dataReceived != NULL)
        {
            while(bytesWritten < bufLen )
            {
                dataReceived[bytesWritten] = MSSP1_SPI_Exchange8bit(MSSP1_SPI_DUMMY_DATA);
                bytesWritten++;
            }
        }
    }
    return bytesWritten;
}

bool MSSP1_SPI_IsBufferFull( void )
{ 
    return (!SSP1STATbits.BF);
}

bool MSSP1_SPI_HasWriteCollisionOccured( void )
{ 
    return (!SSP1CON1bits.WCOL);
}

bool MSSP1_SPI_HasReceiveOverflowOccured( void )
{ 
    return (!SSP1CON1bits.SSPOV);
}

/**
 End of File
*/
