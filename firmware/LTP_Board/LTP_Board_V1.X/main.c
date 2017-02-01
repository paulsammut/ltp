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
#include "lidar.h"
#include "encoder.h"
#include "mcc_generated_files/mccp1_compare.h"
#include "motor.h"
#include "PID.h"


#define FOSC    (32000000ULL)
#define FCY     (FOSC/2)

#include <libpic30.h>

/*
                         Main application
 */

unsigned int i;
unsigned char c = 0;
int8_t sweepVal = 0;
char buf[20];
bool rampup = 1;
uint16_t curAngle;

void test1(void);
void test2(void);
void test3(void);
void test4(void);
void test5(void);

int main(void) {
    // initialize the device
    SYSTEM_Initialize();



    printf("\r\n");
    printf("LTP_BOARD_BOOTING..\r\n");

    LTP_system_init();

    DEBUG_RED = 1;
    DEBUG_GREEN = 1;

    PID_setAnglePtr(&curAngle);
    

    while (1) {
        //test1();
        //test3();
        //test4();
        test5();
    }

    return -1;
}

void test1(void) {
    uint16_t angle;
    uint16_t distance;


    angle = getAngle();
    distance = LIDAR_getDistance();
    printf("PWM val is %d, and head angle is %d and the distance is %d\r\n", sweepVal, angle, distance);
}


// I2C test
void test2(void) {
    LIDAR_getDistance();
}

void test3(void) {


    //enact the PWM value
    motor_setSpeed(sweepVal/2);

    if (rampup)
        sweepVal++;
    else
        sweepVal--;

    if (sweepVal >= 100 && rampup)
        rampup = 0;
    if (sweepVal <= -100 && !rampup)
        rampup = 1;

    c++;
}

void test4() {
    printf("Timer val: %u\r\n", TMR1);
    if (IFS0bits.T1IF) {
        //TMR1 = 0;
        printf("Timer reset!\r\n");
        IFS0bits.T1IF = false;
    }
}

void test5() {
    curAngle = getAngle();
}


/**
 End of File
 */