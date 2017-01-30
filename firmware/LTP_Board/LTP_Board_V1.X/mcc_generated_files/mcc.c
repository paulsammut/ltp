/**
  @Generated MPLAB(c) Code Configurator Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    mcc.c

  @Summary:
    This is the mcc.c file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - pic24-dspic-pic32mm : v1.25
        Device            :  PIC24FV16KM204
        Driver Version    :  1.02
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

// Configuration bits: selected in the GUI

// FBS
#pragma config BWRP = OFF    // Boot Segment Write Protect->Disabled
#pragma config BSS = OFF    // Boot segment Protect->No boot program flash segment

// FGS
#pragma config GWRP = OFF    // General Segment Write Protect->General segment may be written
#pragma config GCP = OFF    // General Segment Code Protect->No Protection

// FOSCSEL
#pragma config FNOSC = FRCPLL    // Oscillator Select->Fast RC Oscillator with Postscaler and PLL Module (FRCDIV+PLL)
#pragma config SOSCSRC = ANA    // SOSC Source Type->Analog Mode for use with crystal
#pragma config LPRCSEL = HP    // LPRC Oscillator Power and Accuracy->High Power, High Accuracy Mode
#pragma config IESO = ON    // Internal External Switch Over bit->Internal External Switchover mode enabled (Two-speed Start-up enabled)

// FOSC
#pragma config POSCMOD = NONE    // Primary Oscillator Configuration bits->Primary oscillator disabled
#pragma config OSCIOFNC = IO    // CLKO Enable Configuration bit->Port I/O enabled (CLKO disabled)
#pragma config POSCFREQ = HS    // Primary Oscillator Frequency Range Configuration bits->Primary oscillator/external clock input frequency greater than 8MHz
#pragma config SOSCSEL = SOSCHP    // SOSC Power Selection Configuration bits->Secondary Oscillator configured for high-power operation
#pragma config FCKSM = CSECME    // Clock Switching and Monitor Selection->Both Clock Switching and Fail-safe Clock Monitor are enabled

// FWDT
#pragma config WDTPS = PS32768    // Watchdog Timer Postscale Select bits->1:32768
#pragma config FWPSA = PR128    // WDT Prescaler bit->WDT prescaler ratio of 1:128
#pragma config FWDTEN = OFF    // Watchdog Timer Enable bits->WDT disabled in hardware; SWDTEN bit disabled
#pragma config WINDIS = OFF    // Windowed Watchdog Timer Disable bit->Standard WDT selected(windowed WDT disabled)

// FPOR
#pragma config BOREN = BOR3    // Brown-out Reset Enable bits->Brown-out Reset enabled in hardware, SBOREN bit disabled
#pragma config RETCFG = OFF    // ->Retention regulator is not available
#pragma config PWRTEN = ON    // Power-up Timer Enable bit->PWRT enabled
#pragma config I2C1SEL = PRI    // Alternate I2C1 Pin Mapping bit->Use Default SCL1/SDA1 Pins For I2C1
#pragma config BORV = V30    // Brown-out Reset Voltage bits->Brown-out Reset set to Highest Voltage (3.0V)
#pragma config MCLRE = ON    // MCLR Pin Enable bit->RA5 input pin disabled, MCLR pin enabled

// FICD
#pragma config ICS = PGx1    // ICD Pin Placement Select bits->EMUC/EMUD share PGC1/PGD1

#include "mcc.h"

void SYSTEM_Initialize(void)
{
    PIN_MANAGER_Initialize();
    INTERRUPT_Initialize();
    OSCILLATOR_Initialize();
    MSSP2_I2C_Initialize();
    UART1_Initialize();
    MSSP1_SPI_Initialize();
    MCCP1_COMPARE_Initialize();
}

void OSCILLATOR_Initialize(void)
{
    // CF no clock failure; NOSC FRCPLL; SOSCEN disabled; SOSCDRV disabled; CLKLOCK unlocked; OSWEN Switch is Complete; 
    __builtin_write_OSCCONL((uint8_t) (0x0100 & 0x00FF));
    // RCDIV FRC/1; DOZE 1:1; DOZEN disabled; ROI disabled; 
    CLKDIV = 0x0000;
    // TUN Center frequency; 
    OSCTUN = 0x0000;
    // ROEN disabled; ROSEL disabled; RODIV Base clock value; ROSSLP disabled; 
    REFOCON = 0x0000;
}

/**
 End of File
*/