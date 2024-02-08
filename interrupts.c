#define mode 1          //defining operating mode (0=normal, 1=testing)

#include <xc.h>
#include "interrupts.h"
#include "global_variables.h"
#include "LCD.h"
/************************************
 * Function to turn on interrupts and set if priority is used
 * Note you also need to enable peripheral interrupts in the INTCON register to use CM1IE.
************************************/
void Interrupts_init(void)
{
	// turn on global interrupts, peripheral interrupts and the interrupt source 
	// It's a good idea to turn on global interrupts last, once all other interrupt configuration is done.
    PIE2bits.C1IE=1; 	//enable interrupt source INT0
    PIE0bits.TMR0IE=1;  //Enable timer interrupt
    IPR2bits.C1IP = 1;
    IPR0bits.TMR0IP = 0;
    INTCONbits.IPEN=1;  //Enable Priority in interrupts
    INTCONbits.PEIE=1;  //Enable Peripherial interrupts
    INTCONbits.GIE=1; 	//turn on interrupts globally (when this is off, all interrupts are deactivated)
    
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

        
        hour++;
        TMR0H=00001011;            //write High reg first, update happens when low reg is written to
        TMR0L=110011011;
        PIR0bits.TMR0IF = 0; // clear interrupt flag

    }
}


