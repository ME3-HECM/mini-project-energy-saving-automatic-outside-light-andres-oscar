#include <xc.h>
#include "date_finders.h"
#include <stdio.h>

// Function to check if a year is a leap year
unsigned int isLeapYear(unsigned int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Function to calculate the day of the year for the last Sunday in March
unsigned int calculateDayOfDSTStart(unsigned int year) {
    unsigned int leapYear = isLeapYear(year);
    // Days in January and February
    unsigned int daysBeforeMarch = 31 + (leapYear ? 29 : 28);
    
    // Calculate day of the week for March 1st using Zeller's Congruence
    unsigned int K = year % 100;
    unsigned int J = year / 100;
    // Adjusting formula for March 1st and our day convention (0=Sunday, ..., 6=Saturday)
    unsigned int h = (1 + ((13 * (3 + 1)) / 5) + K + (K / 4) + (J / 4) - 2 * J) % 7;
    unsigned int dayOfWeekMarch1st = (h + 6) % 7; // Adjusting result to match 0=Sunday, ..., 6=Saturday
    
    // Calculate day of the week for March 31st
    unsigned int dayOfWeekMarch31st = (dayOfWeekMarch1st + 30) % 7;
    
    // Calculate the last Sunday's date in March
    unsigned int lastSundayDateMarch = 31 - dayOfWeekMarch31st;
    
    // Calculate the day of the year for the last Sunday in March
    unsigned int dayOfYearForDSTStart = daysBeforeMarch + lastSundayDateMarch;
    
    return dayOfYearForDSTStart;
}

unsigned int calculateDayOfDSTEnd(unsigned int year) {
    unsigned int leapYear = isLeapYear(year);
    // Days in January through September
    unsigned int daysBeforeOctober = 31 + (leapYear ? 29 : 28) + 31 + 30 + 31 + 30 + 31 + 31 + 30;
    
    // Calculate day of the week for October 1st using Zeller's Congruence
    unsigned int K = year % 100;
    unsigned int J = year / 100;
    // Adjusting formula for October 1st and our day convention (0=Sunday, ..., 6=Saturday)
    unsigned int h = (1 + ((13 * (10 + 1)) / 5) + K + (K / 4) + (J / 4) - 2 * J) % 7;
    unsigned int dayOfWeekOctober1st = (h + 6) % 7; // Adjusting result to match 0=Sunday, ..., 6=Saturday
    
    // Calculate day of the week for October 31st
    unsigned int dayOfWeekOctober31st = (dayOfWeekOctober1st + 30) % 7;
    
    // Calculate the last Sunday's date in October
    unsigned int lastSundayDateOctober = 31 - dayOfWeekOctober31st;
    
    // Calculate the day of the year for the last Sunday in October
    unsigned int dayOfYearForDSTEnd = daysBeforeOctober + lastSundayDateOctober;
    
    return dayOfYearForDSTEnd;
}

