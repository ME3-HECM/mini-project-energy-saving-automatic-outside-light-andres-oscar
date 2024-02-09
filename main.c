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
    unsigned int synced = 0;
    unsigned int daylight_savings = 0;
    unsigned int day = 11;
    unsigned int year = 2024;
    unsigned int leap;
    unsigned int fwd_daylight_savings_day;
    unsigned int bkwd_daylight_savings_day;
    unsigned int backward_zone = 0; //Variable to ensure hour moves back once a year. (avoids infinite loop in October)
    char buf[32];

    initialise();
          
    while (1) {
        leap = isLeapYear(year);
                
        LEDarray_disp_bin(hour);//displaying hour of the day on LED display
       
        LCD_setline(1);
        
        time2String(buf,hour,day,year,leap);
       
        findDSTdates(hour, day, year,&fwd_daylight_savings_day, &bkwd_daylight_savings_day);

        increaseHour(day, fwd_daylight_savings_day, bkwd_daylight_savings_day, &hour, &backward_zone);                   
        
        changeHourDayYear(&hour, &day, &year, leap, &synced);       
        
        
        sunSync(&hour, day, &synced);

 // if the time is between 1 and 5 am, keep LED as off
   }
}