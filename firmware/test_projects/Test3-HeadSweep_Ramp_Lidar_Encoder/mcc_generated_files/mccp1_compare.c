
/**
  MCCP1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    mccp1.c

  @Summary
    This is the generated header file for the MCCP1 driver using MPLAB(c) Code Configurator

  @Description
    This header file provides APIs for driver for MCCP1.
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
#include "mccp1_compare.h"

/** OC Mode.

  @Summary
    Defines the OC Mode.

  @Description
    This data type defines the OC Mode of operation.

*/

static uint16_t         gMCCP1Mode;

/**
  Section: Driver Interface
*/


void MCCP1_COMPARE_Initialize (void)
{
    // CCPON enabled; MOD Dual Edge Compare, Buffered; CCSEL disabled; CCPSIDL disabled; TMR32 16 Bit; CCPSLP disabled; TMRPS 1:1; CLKSEL FOSC/2; TMRSYNC disabled; 
    CCP1CON1L = 0x8005;
    // RTRGEN disabled; ALTSYNC disabled; ONESHOT disabled; TRIGEN disabled; IOPS Each Time Base Period Match; SYNC None; OPSRC Timer Interrupt Event; 
    CCP1CON1H = 0x0000;
    // ASDGM disabled; SSDG disabled; ASDG None; PWMRSEN disabled; 
    CCP1CON2L = 0x0000;
    // OCCEN disabled; OCDEN disabled; OCEEN disabled; ICGSM Level-Sensitive mode; OCFEN disabled; ICSEL IC1; AUXOUT Disabled; OCAEN enabled; OCBEN enabled; OENSYNC disabled; 
    CCP1CON2H = 0x0300;
    // DT 0; 
    CCP1CON3L = 0x0000;
    // OETRIG disabled; OSCNT None; POLACE disabled; POLBDF disabled; PSSBDF Tri-state; OUTM Steerable single output; PSSACE Tri-state; 
    CCP1CON3H = 0x0000;
    // ICDIS disabled; SCEVT disabled; TRSET disabled; ICOV disabled; ASEVT disabled; TRIG disabled; TRCLR disabled; 
    CCP1STATL = 0x0000;
    // TMR 0; 
    CCP1TMRL = 0x0000;
    // TMR 0; 
    CCP1TMRH = 0x0000;
    // PR 1000; 
    CCP1PRL = 0x03E8;
    // PR 0; 
    CCP1PRH = 0x0000;
    // CMP 0; 
    CCP1RAL = 0x0000;
    // CMP 500; 
    CCP1RBL = 0x01F4;
    // BUF 0; 
    CCP1BUFL = 0x0000;
    // BUF 0; 
    CCP1BUFH = 0x0000;
	
    gMCCP1Mode = CCP1CON1Lbits.MOD;

}

void MCCP1_COMPARE_Tasks( void )
{
    if(IFS0bits.CCP1IF)
    {
        IFS0bits.CCP1IF = 0;
    }
}


void MCCP1_COMPARE_TimerTasks( void )
{
    if(IFS0bits.CCT1IF)
    {
        IFS0bits.CCT1IF = 0;
    }
}

void MCCP1_COMPARE_Start( void )
{
    /* Start the Timer */
    CCP1CON1Lbits.CCPON = true;
}
void MCCP1_COMPARE_Stop( void )
{
    /* Start the Timer */
    CCP1CON1Lbits.CCPON = false;
}

void MCCP1_COMPARE_SingleCompare16ValueSet( uint16_t value )
{   
    CCP1RAL = value;
}


void MCCP1_COMPARE_DualCompareValueSet( uint16_t priVal, uint16_t secVal )
{
    
    CCP1RAL = priVal;
	
    CCP1RBL = secVal;
}
void MCCP1_COMPARE_DualEdgeBufferedConfig( uint16_t priVal, uint16_t secVal )
{
    
    CCP1RAL = priVal;
	
    CCP1RBL = secVal;
}
void MCCP1_COMPARE_CenterAlignedPWMConfig( uint16_t priVal, uint16_t secVal )
{
    
    CCP1RAL = priVal;
	
    CCP1RBL = secVal;
}
void MCCP1_COMPARE_VariableFrequencyPulseConfig( uint16_t priVal )
{
    CCP1RAL = priVal;
	
}
bool MCCP1_COMPARE_IsCompareCycleComplete( void )
{
    return(IFS0bits.CCP1IF);
}
bool MCCP1_COMPARE_TriggerStatusGet( void )
{
    return( CCP1STATLbits.TRIG );
    
}
void MCCP1_COMPARE_TriggerStatusSet( void )
{
    CCP1STATLbits.TRSET = 1;
}
void MCCP1_COMPARE_TriggerStatusClear( void )
{
    /* Clears the trigger status */
    CCP1STATLbits.TRCLR = 0;
}
bool MCCP1_COMPARE_SingleCompareStatusGet( void )
{
    return( CCP1STATLbits.SCEVT );
}
void MCCP1_COMPARE_SingleCompareStatusClear( void )
{
    /* Clears the trigger status */
    CCP1STATLbits.SCEVT = 0;
    
}
/**
 End of File
*/
