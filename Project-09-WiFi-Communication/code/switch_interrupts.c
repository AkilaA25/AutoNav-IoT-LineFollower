/*
 * switch_interrupts.c
 *
 *  Created on: Feb 20, 2025
 *      Author: akila
 */


#include  "include\macros.h"


#pragma vector=PORT4_VECTOR
__interrupt void switchP4_interrupt(void) {
    if (P4IFG & SW1) {
        P4IFG &= ~SW1;  // Clear interrupt flag for SW1
        P4IE &= ~SW1;
        TB0CCTL1 &= ~CCIFG;   // Clear any pending timer interrupt

        switch_pressed1 = 1;   // Set flag to indicate switch press
        debounce_active1 = 1;  // Set flag to indicate debounce is active
        debounce_count1 = 0;   // Reset debounce counter

        TB0CCR1 = TB0R + DEBOUNCE_INTERVAL; // Set debounce time
        TB0CCTL1 |= CCIE;     // Enable Timer B0 interrupt for debounce
    }
}


#pragma vector=PORT2_VECTOR
__interrupt void switchP2_interrupt(void) {
    if (P2IFG & SW2) {
        P2IFG &= ~SW2;  // Clear interrupt flag for SW1
        P2IE &= ~SW2;
        TB0CCTL2 &= ~CCIFG;   // Clear any pending timer interrupt

        switch_pressed2 = 1;   // Set flag to indicate switch press
        debounce_active2 = 1;  // Set flag to indicate debounce is active
        debounce_count2 = 0;   // Reset debounce counter

        TB0CCR2 = TB0R + DEBOUNCE_INTERVAL; // Set debounce time
        TB0CCTL2 |= CCIE;     // Enable Timer B0 interrupt for debounce
    }
}


