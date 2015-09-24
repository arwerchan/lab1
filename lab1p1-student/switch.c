/*
 * File:   switch.c
 * Author: Garrett
 *
 * Created on September 19, 2015, 10:46 AM
 */

#include <xc.h>

#define INPUT 1
#define OUTPUT 0

#define ENABLED 1
#define DISABLED 0

void initSW1(){
    ANSELD = 0;
    //TODO: Initialize the appropriate pins to work with the external switch using a
    //change notification interrupt.
    TRISDbits.TRISD0 = INPUT;           // Configure switch as input
    CNCONDbits.ON = 1;                  // Enable overall interrupt
    CNENDbits.CNIED0 = ENABLED;         // Enable pin CN
    CNPUDbits.CNPUD0 = ENABLED;         // Enable pull-up resistor
    IFS1bits.CNDIF = 0;                 // Put down the flag
    IPC8bits.CNIP = 1;                  // Configure interrupt priority
    IPC8bits.CNIS = 1;                  // Configure the interrupt sub-priority
    IEC1bits.CNDIE = ENABLED;           // Enable interrupt for D pins
}
