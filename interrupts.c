#define mode 1          //defining operating mode (0=normal, 1=testing)

#include <xc.h>
#include "interrupts.h"
#include "global_variables.h"
#include "LCD.h"
/************************************
 * Function to turn on interrupts and set if priority is used
 * Note you also need to enable peripheral interrupts in the INTCON register to use CM1IE.
************************************/
void Interrupts_init(void) {
    // Enable comparator 1 interrupt source
    PIE2bits.C1IE = 1;    // Enable interrupt for Comparator 1
    IPR2bits.C1IP = 0;    // Set Comparator 1 interrupt priority 
    
    // Enable comparator 2 interrupt source
    PIE2bits.C2IE = 1;    // Enable interrupt for Comparator 2
    IPR2bits.C2IP = 0;    // Set Comparator 2 interrupt priority 

    // Enable comparator 3 interrupt source
    PIE2bits.C3IE = 1;    // Enable interrupt for Comparator 3
    IPR2bits.C3IP = 1;    // Set Comparator 3 interrupt priority

            
    // Enable timer interrupt (if used in your application)
    PIE0bits.TMR0IE = 1;  // Enable timer interrupt
    IPR0bits.TMR0IP = 0;  // Set timer interrupt priority (0 = low priority)

    // Enable Priority in interrupts
    INTCONbits.IPEN = 1;  // Enable interrupt priority

    // Enable Peripheral interrupts
    INTCONbits.PEIE = 1;  // Enable peripheral interrupts

    // Turn on interrupts globally
    INTCONbits.GIE = 1;   // Enable global interrupts
}


/************************************
 * High priority interrupt service routine
 * Make sure all enabled interrupts are checked and flags cleared
************************************/




//low priority interrupt setup for timer overflow
void __interrupt(low_priority) LowISR()
{   
 
    if (PIR0bits.TMR0IF == 1) { // check interrupt flag

        
        hour++;
        TMR0H=00001011;            //write High reg first, update happens when low reg is written to
        TMR0L=110011011;
        if (hour >= 1 && hour <= 5){
            LATHbits.LATH3 = 0;
        }
        PIR0bits.TMR0IF = 0; // clear interrupt flag

    }
    
    
    if (PIR2bits.C1IF == 1) {

        LATHbits.LATH3 = 1;//change value for the H3 LED 
        
        PIR2bits.C1IF = 0;
    }
    
    if (PIR2bits.C2IF == 1) {
            LATHbits.LATH3 = 0;//change value for the H3 LED 
            PIR2bits.C2IF = 0;
        }

}


