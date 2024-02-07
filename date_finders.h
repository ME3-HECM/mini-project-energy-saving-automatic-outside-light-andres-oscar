#ifndef _date_finders_H
#define _date_finders_H

#include <xc.h>

#define _XTAL_FREQ 64000000

//function prototypes
unsigned int isLeapYear(unsigned int year);
unsigned int calculateDayOfDSTStart(unsigned int year);
unsigned int calculateDayOfDSTEnd(unsigned int year);

#endif

