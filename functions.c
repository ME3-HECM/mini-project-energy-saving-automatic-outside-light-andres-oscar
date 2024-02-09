#include <xc.h>
#include "functions.h"
#include "LCD.h"
#include "LEDarray.h"
#include "comparator.h"
#include "functions.h"
#include "global_variables.h"
#include "interrupts.h"
#include "timers.h"
#include <stdio.h>


// Function to check if a year is a leap year
unsigned int isLeapYear(unsigned int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

unsigned int lastSunday(unsigned int year, unsigned int month){
    unsigned int leapYear = isLeapYear(year);
    
    // Calculate day of the week for March 1st using Zeller's Congruence
    // Adjusting formula for March 1st and our day convention (0=Sunday, ..., 6=Saturday)
    unsigned int h = (1 + ((13 * (month + 1)) / 5) + (year % 100) + ((year % 100) / 4) + ((year / 100) / 4) - 2 * (year / 100)) % 7;
    unsigned int dayOfWeekMonth1st = (h + 6) % 7; // Adjusting result to match 0=Sunday, ..., 6=Saturday
    
    // Calculate day of the week for March 31st
    unsigned int dayOfWeekMonth31st = (dayOfWeekMonth1st + 30) % 7;
    
    // Calculate the last Sunday's date in March
    unsigned int lastSundayDateMonth = 31 - dayOfWeekMonth31st;
    
    // Calculate the last Sunday's date in March
    if (month == 3){
    unsigned int daysBeforeMarch = 31 + (leapYear ? 29 : 28);
    unsigned int dayOfYearForDSTStart = daysBeforeMarch + lastSundayDateMonth;
    return dayOfYearForDSTStart;

    // Calculate the last Sunday's date in October

    }
    if (month == 10){
    unsigned int daysBeforeOctober = 31 + (leapYear ? 29 : 28) + 31 + 30 + 31 + 30 + 31 + 31 + 30;
        // Calculate the day of the year for the last Sunday in October
    unsigned int dayOfYearForDSTEnd = daysBeforeOctober + lastSundayDateMonth;
    
    return dayOfYearForDSTEnd;
    }
    
}

void increaseHour(unsigned int day, unsigned int fwd_daylight_savings_day, unsigned int bkwd_daylight_savings_day, unsigned int *hour, unsigned int *backward_zone) {
    // If it's daylight savings, move hour forward at 2 am
    if (day == fwd_daylight_savings_day && *hour == 2) {
        (*hour)++;
        *backward_zone = 0;
    }
    // If it's daylight savings in October, move hour backwards at 2 am
    if (day == bkwd_daylight_savings_day && *hour == 2 && *backward_zone == 0) {
        (*hour)--;
        *backward_zone = 1;
    }
}

void findDSTdates(unsigned int hour, unsigned int day, unsigned int year, unsigned int *fwd_daylight_savings_day, unsigned int *bkwd_daylight_savings_day){
        //Calculate the dates for the daylight savings changes
    if (day==1 && hour == 0){
        *fwd_daylight_savings_day = lastSunday(year, 3);
        *bkwd_daylight_savings_day = lastSunday(year, 10);
    }

}

void changeHourDayYear(unsigned int *hour, unsigned int *day, unsigned int *year, unsigned int leap, unsigned int *synced){
    // Resets hours once it reaches 24 hours
    if (*hour == 24) {
       *hour = 0;
       (*day)++;
    }

    // For a non-leap year
    if (leap == 0 && *day > 365) {
        *day = 1;
        (*year)++;
        *synced = 0;
    }
    
    // For a leap year
    if (leap == 1 && *day > 366) {
        *day = 1;
        (*year)++;
    }
}

void sunSync(unsigned int *hour, unsigned int day, unsigned int *synced){
    if (LATHbits.LATH3 == 0 && day==11 && *hour>=6 && *synced == 0){
        *hour = 8;
        *synced = 1;
    }
}


void initialise(void){
    //initialising necessary components
    Interrupts_init();
    Comp1_init_re();
    Comp1_init_fe();
    Timer0_init();
    LEDarray_init();
    LCD_init();
    
}


