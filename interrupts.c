#define mode 1          //defining operating mode (0=normal, 1=testing)

#include <xc.h>
#include "interrupts.h"


/************************************
 * Function to turn on interrupts and set if priority is used
 * Note you also need to enable peripheral interrupts in the INTCON register to use CM1IE.
************************************/
void Interrupts_init(void)
{
	// turn on global interrupts, peripheral interrupts and the interrupt source 
	// It's a good idea to turn on global interrupts last, once all other interrupt configuration is done.
    PIE2bits.C1IE = 1; // comparator 1
    IPR2bits.C1IP = 1; // high priority
    INTCONbits.PEIE = 1; // peripheral interrupts
    INTCONbits.GIE = 1; // global interrupts
    //Interrupts
    LATEbits.LATE2 = 0;
    TRISEbits.TRISE2= 1;
}

/************************************
 * High priority interrupt service routine
 * Make sure all enabled interrupts are checked and flags cleared
************************************/
void __interrupt(high_priority) HighISR()
{
	//add your ISR code here i.e. check the flag, do something (i.e. toggle an LED), clear the flag...
    if (PIR2bits.C1IF == 1) {
        LATHbits.LATH3 = !LATHbits.LATH3;//change value for the H3 LED 
        PIR2bits.C1IF = 0;
    }
}
    




//low priority interrupt setup for timer overflow
void __interrupt(low_priority) LowISR()
{   
    
    if (PIR0bits.TMR0IF == 1) { // check interrupt flag

        
        LATEbits.LATE2 = 1;
        TMR0H=00001011;            //write High reg first, update happens when low reg is written to
        TMR0L=110011011;
        PIR0bits.TMR0IF = 0; // clear interrupt flag
    }
}


