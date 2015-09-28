/* 
* File:   leds.h
* Author: 
*
* Created on December 27, 2014, 1:31 PM
*/

#ifndef LEDS_H
#define	LEDS_H

#define LED1 LATDbits.LATD1
#define LED2 LATDbits.LATD2

void initLEDs();
void stopLED();
void runLED();
void toggleLEDs();

#endif	/* LEDS_H */

