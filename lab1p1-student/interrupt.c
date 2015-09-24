/* 
 * File:   interrupt.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:32 PM
 */

#include <xc.h>

void enableInterrupts(){
    unsigned int val;

    // set the CP0 cause IV bit high
    asm volatile("mfc0   %0,$13" : "=r"(val));
    val |= 0x00800000;
    asm volatile("mtc0   %0,$13" : "+r"(val));

    INTCONSET = _INTCON_MVEC_MASK;
    INTCON = 0;
    
    INTCONbits.INT0EP = 1;    // set the bit for rising edge trigger (use pull down)
    IFS0bits.INT0IF = 0;         // clear the interrupt 0 flag
    IPC0bits.INT0IP = 7;         // set priority level
    IEC0bits.INT0IE = 1;         // enable INT0

    unsigned int status = 0;
    asm volatile("ei    %0" : "=r"(status));
}

void disableInterrupts(){
    unsigned int status = 0;
    asm volatile("di    %0" : "=r"(status));
}