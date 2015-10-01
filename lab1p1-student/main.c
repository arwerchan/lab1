// ******************************************************************************************* //
//
// File:         lab1p1.c
// Date:         
// Authors:      
//
// Description: Part 1 for lab 1
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "leds.h"
#include "interrupt.h"
#include "switch.h"
#include "timer.h"


// Define states
typedef enum stateTypeEnum{
    waitPush, waitRelease, count
} stateType;

volatile stateType state = waitPush;

/* Please note that the configuration file has changed from lab 0.
 * the oscillator is now of a different frequency.
 */
int main(void)
{
    
    initLEDs();
    initSW1();
    initTimer1();
    
    enableInterrupts();
    
    while(1)
    {
        //TODO: Using a finite-state machine, define the behavior of the LEDs
        //Debounce the switch
        switch(state){
            case waitPush:
                break;
            case count:
                delayMs(5);
                // check button
                
                break;
            case waitRelease:
                break;
        }
    }
    
    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL3SRS) _CNInterrupt(void){
    //TODO: Implement the interrupt to capture the press of the button
    PORTDbits.RD0 = 1;
    IFS1bits.CNDIF = 0;
    if(state == waitPush) state = count;
    else if(state == waitRelease){
        state = waitPush;
        toggleLEDs();
    }
}
