/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - pic24-dspic-pic32mm : v1.25
        Device            :  PIC24FV16KM202
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC16 1.26
        MPLAB             :  MPLAB X 3.45
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

#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include "LTP_system.h"

/*
                         Main application
 */

unsigned int i;
unsigned char c = 0;
const unsigned int period = 0x03E8/2;
unsigned int PWMval = 0;
char buf[20];
bool rampup = 1;

void test1(void);

    
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    LTP_system_init();
    while(1)
    {
        
        DEBUG_RED = 0;
        DEBUG_RED = 0;
        test1();

    }

    return -1;
}

void test1(void)
{
    // To make the LED blink visibly, we have to wait a while between toggling

    // the LED pin.
    for(i = 0; i < 1000; i++)
    {
        Nop();
    }
    
    //enact the PWM value
    MCCP1_COMPARE_DualEdgeBufferedConfig(0,PWMval);
    
    if(rampup)
        PWMval++;
    else
        PWMval--;
    
    if(PWMval >= period && rampup)
        rampup = 0;
    if(PWMval == 0 && !rampup)
        rampup = 1;
   

    // Toggle the LED output pin to alternate between the LED being on and off
    DEBUG_GREEN ^= 1;
    
    printf("PWM val is %d, and head angle is %d",PWMval,getAngle());
    testEncoder();
    printf("\r\n");

    c++;
    
    //lidar_getDistance();
    
    //getAngle();
    
}
/**
 End of File
*/