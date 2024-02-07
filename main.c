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
#include "date_finders.h"

void main(void) {
    //call the variables
    unsigned int light_state = 0;
    unsigned int daylight_savings = 0;
    unsigned int light_start = 1;
    unsigned int light_end = 5;
    unsigned int hour = 0;
    unsigned int day = 0;
    unsigned int year = 2024;
    unsigned int leap;
    unsigned int fwd_daylight_savings_day;
    unsigned int bkwd_daylight_savings_day;
    unsigned int backward_zone = 0; //Variable to ensure hour moves back once a year. (avoids infinite loop in October)

    //initialising necessary components
    Interrupts_init();
    Timer0_init();
    LEDarray_init();
    
    while (1) {
        
        if (LATEbits.LATE2 == 1){
            hour++;
            LATEbits.LATE2 = 0;
        }
        LEDarray_disp_bin(hour);//displaying hour of the day on LED display
        

        
            
                              
        //Calculate the dates for the daylight savings changes
        if (day==0 && hour == 0){
            fwd_daylight_savings_day = calculateDayOfDSTStart(year);
            bkwd_daylight_savings_day = calculateDayOfDSTEnd(year);
        }
        //If its daylight savings, move hour forward at 2 am
        if (day==fwd_daylight_savings_day && hour==2){
            hour++;
            backward_zone = 0;

        }
        //If its daylight savings in October, move hour backwards at 2am
        if (day==bkwd_daylight_savings_day && hour==2 && backward_zone == 0){
            hour--;
            backward_zone = 1;
        }
        
                

        
        if (hour >= 1 && hour <= 5){
            light_state = 1;
        } else {
            light_state = 0;
        }
        
        if (light_state == 1){
            LATHbits.LATH3 = 1;
        } else {
            LATHbits.LATH3 = 0;
        }
     
        

        
        if (hour == 24) {
           hour = 0;
           day++;
              }//resets hours once it reaches 24hours
        if (day == 365){
            leap = isLeapYear(year);
            if (leap == 0){
                day=0;
                year++;
            }
            
        }
        if (day == 366){
            day = 0;
            year++;
        }        
    }
}