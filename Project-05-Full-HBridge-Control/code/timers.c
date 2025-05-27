/*
 * timers.c
 *
 *  Created on: Feb 18, 2025
 *      Author: akila
 */


#include  "include\macros.h"  //has every header file and global variables

#define DEBOUNCE_LIMIT 20;


void Init_Timers(void){
    Init_Timer_B0();
}

void Init_Timer_B0(void) {
    TB0CTL = TBSSEL__SMCLK;       // Use SMCLK (8 MHz)
    TB0CTL |= TBCLR;              // Reset TB0R, clock divider, count direction
    TB0CTL |= MC__CONTINUOUS;     // Set Timer B0 to continuous mode
    TB0CTL |= ID__8;              // Divide SMCLK by 8
    TB0EX0 = TBIDEX__8;           // Further divide by 8

    TB0CCR0 = TB0CCR0_INTERVAL;
    TB0CCTL0 |= CCIE;             // Enable interrupt for CCR0

    TB0CCR1 = 0;
    TB0CCTL1 |= CCIE;             // Enable interrupt for CCR1

    TB0CCR2 = 0;
    TB0CCTL2 |= CCIE;             // Enable interrupt for CCR2


    TB0CTL &= ~TBIE;              // Disable Timer B overflow interrupt
    TB0CTL &= ~TBIFG;             // Clear Timer B overflow flag
}






