#ifndef _functions_H
#define _functions_H

#include <xc.h>

#define _XTAL_FREQ 64000000

//function prototypes
unsigned int isLeapYear(unsigned int year);
unsigned int lastSunday(unsigned int year, unsigned int month);
void increaseHour(unsigned int day, unsigned int fwd_daylight_savings_day, unsigned int bkwd_daylight_savings_day, unsigned int *hour, unsigned int *backward_zone);
void findDSTdates(unsigned int hour, unsigned int day, unsigned int year, unsigned int *fwd_daylight_savings_day, unsigned int *bkwd_daylight_savings_day);
void changeHourDayYear(unsigned int *hour, unsigned int *day, unsigned int *year);
void initialise(void);


#endif

