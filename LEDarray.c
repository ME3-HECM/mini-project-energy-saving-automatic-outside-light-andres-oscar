#include <xc.h>
#include "LEDarray.h"

/************************************
/ LEDarray_init
/ Function used to initialise pins to drive the LEDarray
************************************/
void LEDarray_init(void)
{
    LATA = 0; //set initial output LAT values (they may have random values when powered on)
    LATB = 0; //initialise LAT before TRIS
    LATFbits.LATF0 = 0;
    LATFbits.LATF6 = 0;
    LATG = 0;
	LATHbits.LATH3 = 1;
    
    //set up TRIS registers for pins connected to LED array
    TRISA = 0; 
	TRISB = 0;
    TRISFbits.TRISF0 = 0;
    TRISFbits.TRISF6 = 0;
    TRISG = 0;
    TRISHbits.TRISH3 = 0;

    TRISFbits.TRISF2=1; //set TRIS value for pin (input)
    ANSELFbits.ANSELF2=0; //turn off analogue input on pin    
}


/************************************
/ LEDarray_disp_bin
/ Function used to display a number on the LED array in binary
************************************/
void LEDarray_disp_bin(unsigned int number)
{
    //some code to turn on/off the pins connected to the LED array
	if (number & 1)        {LATGbits.LATG0 = 1;} else {LATGbits.LATG0 = 0;} //test bit 0 against bit mask and set LED
    if (number & (1 << 1)) {LATGbits.LATG1 = 1;} else {LATGbits.LATG1 = 0;} //test bit 1
    if (number & (1 << 2)) {LATAbits.LATA2 = 1;} else {LATAbits.LATA2 = 0;} //test bit 2
    if (number & (1 << 3)) {LATFbits.LATF6 = 1;} else {LATFbits.LATF6 = 0;} //...
    if (number & (1 << 4)) {LATAbits.LATA4 = 1;} else {LATAbits.LATA4 = 0;}
    if (number & (1 << 5)) {LATAbits.LATA5 = 1;} else {LATAbits.LATA5 = 0;}
    if (number & (1 << 6)) {LATFbits.LATF0 = 1;} else {LATFbits.LATF0 = 0;}
    if (number & (1 << 7)) {LATBbits.LATB0 = 1;} else {LATBbits.LATB0 = 0;}
    if (number & (1 << 8)) {LATBbits.LATB1 = 1;} else {LATBbits.LATB1 = 0;} //test bit 8
}
