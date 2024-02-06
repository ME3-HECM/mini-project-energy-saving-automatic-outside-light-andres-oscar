// CONFIG1L
#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)
// CONFIG3L
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)
#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  


#include <xc.h>

#include "LEDarray.h"
#include "interrupts.h"
#include "comparator.h"
#include "timers.h"


void main(void) {
    //calling variables
    unsigned int light_state;
    TRISEbits.TRISE7 = 1;
    LATEbits.LATE7 = 0;
    TRISHbits.TRISH3= 0;
    LATHbits.LATH3 = 0;
    //initialising necessary components
    Interrupts_init();
    Timer0_init();
    LEDarray_init();
    
    
    while (1) {
        unsigned int hour;
        if (PORTEbits.RE7 != PORTEbits.RE7) {
            hour++;
        }
        
        
        
        if (hour == 24) {hour = 0;}//resets hours once it reaches 24hours
        
        LEDarray_disp_bin(hour);//displaying hour of the day on LED display
     
        
        if (hour < 5 && hour > 1) {
            light_state = 0;
        }
        else {light_state = 1;}
        
        if (light_state == 1){
            LATHbits.LATH3 = 1;
        }
        else {LATHbits.LATH3 = 0;}
    }
}