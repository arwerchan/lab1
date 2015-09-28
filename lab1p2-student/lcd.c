/*
 * File:   lcd.c
 * Authors:
 *
 * Created on December 31, 2014, 1:39 PM
 */

/* TODO: Make define statements for each pin used in the LCD
 */
#include <xc.h>
#include "lcd.h"
#include "timer.h"

#define LCD_DATA  LATD
#define LCD_RS  LATDbits.LATD7
#define LCD_E   LATDbits.LATD6

#define TRIS_D7 TRISDbits.TRISD15
#define TRIS_D6 TRISDbits.TRISD14
#define TRIS_D5 TRISDbits.TRISD13
#define TRIS_D4 TRISDbits.TRISD12
#define TRIS_RS TRISDbits.TRISD7
#define TRIS_E  TRISDbits.TRISD6

#define LCD_WRITE_DATA    1
#define LCD_WRITE_CONTROL 0

#define LOWER 1
#define UPPER 0

#define OUTPUT 0
#define INPUT 1

/* This function should take in a two-byte word and writes either the lower or upper
 * byte to the last four bits of LATB. Additionally, according to the LCD data sheet
 * It should set LCD_RS and LCD_E with the appropriate values and delays.
 * After these commands are issued, there should be a delay.
 * The command type is a simplification. From the data sheet, the RS is '1'
 * when you are simply writing a character. Otherwise, RS is '0'.
 */
void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower){
    //TODO:
    if(lower){
        LATDbits.LATD15 = word<3>;
        LATDbits.LATD14 = word<2>;
        LATDbits.LATD13 = word<1>;
        LATDbits.LATD12 = word<0>;
    }
    else{
        LATDbits.LATD15 = word<7>;
        LATDbits.LATD14 = word<6>;
        LATDbits.LATD13 = word<5>;
        LATDbits.LATD12 = word<4>;
    }
    LCD_RS = commandType; delayUs(1);
    LCD_E = 1;  
    delayUs(1); //minimum 230 ns
    LCD_E = 0;  
    delayUs(1);
    delayUs(delayAfter);
}

/* Using writeFourBits, this function should write the two bytes of a character
 * to the LCD.
 */
void writeLCD(unsigned char word, unsigned int commandType, unsigned int delayAfter){
    //TODO:
    writeFourBits(word, commandType, delayAfter, UPPER);
    writeFourBits(word, commandType, delayAfter, LOWER);
}

/* Given a character, write it to the LCD. RS should be set to the appropriate value.
 */
void printCharLCD(char c) {
    //TODO:
    writeLCD(c, LCD_WRITE_DATA, 46);
}
/*Initialize the LCD
 */
void initLCD(void) {
    // Setup D, RS, and E to be outputs (0).
    LCD_DATA = OUTPUT;
    LCD_RS = OUTPUT;
    LCD_E = OUTPUT;
    
    // Initilization sequence utilizes specific LCD commands before the general configuration
    // commands can be utilized. The first few initilition commands cannot be done using the
    // WriteLCD function. Additionally, the specific sequence and timing is very important.
    TRIS_D4 = 1;
    TRIS_D5 = 1;
    TRIS_D6 = 0;
    TRIS_D7 = 0;
    LCD_RS = 0;
    //LCD R/W = 0;
    delayUs(4100);
    
    
    // Enable 4-bit interface
    delayUs(100);
    
    // Function Set (specifies data width, lines, and font.
    
    
    // 4-bit mode initialization is complete. We can now configure the various LCD
    // options to control how the LCD will function.

    // TODO: Display On/Off Control
        // Turn Display (D) Off
    // TODO: Clear Display (The delay is not specified in the data sheet at this point. You really need to have the clear display delay here.
    // TODO: Entry Mode Set
        // Set Increment Display, No Shift (i.e. cursor move)
    // TODO: Display On/Off Control
        // Turn Display (D) On, Cursor (C) Off, and Blink(B) Off
    TRIS_D4 = 0;
    TRIS_D5 = 1;
    TRIS_D6 = 0;
    TRIS_D7 = 0;
    LCD_RS = 0;
    //LCD R/W = 0;
    
    TRIS_D4 = 0;
    TRIS_D5 = 1;
    TRIS_D6 = 0;
    TRIS_D7 = 0;
    LCD_RS = 0;
    //LCD R/W = 0;
    
    TRIS_D4 = 1;
    TRIS_D5 = 1;
    TRIS_D6 = 0;
    TRIS_D7 = 0;
    LCD_RS = 0;
    //LCD R/W = 0;
    
    //wait
    TRIS_D4 = 0;
    TRIS_D5 = 0;
    TRIS_D6 = 1;
    TRIS_D7 = 1;
    LCD_RS = 0;
    //LCD R/W = 0;
    
    delayUs(40);
    
    TRIS_D4 = 0;
    TRIS_D5 = 0;
    TRIS_D6 = 0;
    TRIS_D7 = 0;
    LCD_RS = 0;
    //LCD R/W = 0;
    
    TRIS_D4 = 0;
    TRIS_D5 = 0;
    TRIS_D6 = 0;
    TRIS_D7 = 1;
    LCD_RS = 0;
    //LCD R/W = 0;
    
    delayUs(1000);
    
    TRIS_D4 = 0;
    TRIS_D5 = 0;
    TRIS_D6 = 0;
    TRIS_D7 = 0;
    LCD_RS = 0;
    //LCD R/W = 0;
    
    TRIS_D4 = 1;
    TRIS_D5 = 0;
    TRIS_D6 = 0;
    TRIS_D7 = 0;
    LCD_RS = 0;
    //LCD R/W = 0;
    
    delayUs(1614);
    
    TRIS_D4 = 0;
    TRIS_D5 = 0;
    TRIS_D6 = 0;
    TRIS_D7 = 0;
    LCD_RS = 0;
    //LCD R/W = 0;
    
    TRIS_D4 = 0;
    TRIS_D5 = 1;
    TRIS_D6 = 1;
    TRIS_D7 = 0;
    LCD_RS = 0;
    //LCD R/W = 0;
    
    delayUs(40);
}

/*
 * You can use printCharLCD here. Note that every time you write a character
 * the cursor increments its position automatically.
 * Since a string is just a character array, try to be clever with your use of pointers.
 */
void printStringLCD(const char* s) {
    //TODO:
}

/*
 * Clear the display.
 */
void clearLCD(){
    TRIS_D4 = 0;
    TRIS_D5 = 0;
    TRIS_D6 = 0;
    TRIS_D7 = 0;
    LCD_RS = 0;
    //LCD R/W = 0;
    
    TRIS_D4 = 1;
    TRIS_D5 = 0;
    TRIS_D6 = 0;
    TRIS_D7 = 0;
    LCD_RS = 0;
    //LCD R/W = 0;
    
    delayUs(1614);
}

/*
 Use the command for changing the DD RAM address to put the cursor somewhere.
 */
void moveCursorLCD(unsigned char x, unsigned char y){
}

/*
 * This function is called in lab1p2.c for testing purposes.
 * If everything is working properly, you should get this to look like the video on D2L
 * However, it is suggested that you test more than just this one function.
 */
void testLCD(){
    initLCD();
    int i = 0;
    printCharLCD('c');
    for(i = 0; i < 1000; i++) delayUs(1000);
    clearLCD();
    printStringLCD("Hello!");
    moveCursorLCD(1, 2);
    for(i = 0; i < 1000; i++) delayUs(1000);
    printStringLCD("Hello!");
    for(i = 0; i < 1000; i++) delayUs(1000);
}