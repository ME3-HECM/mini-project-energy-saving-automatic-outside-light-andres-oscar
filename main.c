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
#include "functions.h"
#include "LCD.h"
#include "global_variables.h"


void main(void) {
    //call the variables
    unsigned int daylight_savings = 0;
    unsigned int day = 9;
    unsigned int year = 2024;
    unsigned int leap;
    unsigned int fwd_daylight_savings_day;
    unsigned int bkwd_daylight_savings_day;
    unsigned int backward_zone = 0; //Variable to ensure hour moves back once a year. (avoids infinite loop in October)
    char buf[32];

    //initialising necessary components
    Interrupts_init();
    Comp1_init_re();
    Comp1_init_fe();
    Timer0_init();
    LEDarray_init();
    LCD_init();

    while (1) {
        


        LEDarray_disp_bin(hour);//displaying hour of the day on LED display
        LCD_setline(1);
        time2String(buf,hour,day,year);
        
            
                              
        //Calculate the dates for the daylight savings changes
        if (day==1 && hour == 0){
            fwd_daylight_savings_day = lastSunday(year, 3);
            bkwd_daylight_savings_day = lastSunday(year, 10);
        }

        
                

        
        if (hour >= 1 && hour <= 5){
            LATHbits.LATH3 = 1;
        }
        
     
        

        
        if (hour == 24) {
           hour = 0;
           day++;
              }//resets hours once it reaches 24hours
        if (day == 365){
            leap = isLeapYear(year);
            if (leap == 0){
                day=1;
                year++;
            }
            
        }
        if (day == 366){
            day = 1;
            year++;
        }        
    }
}