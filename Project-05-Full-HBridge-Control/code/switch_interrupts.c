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

        switch_pressed1 = 1;   // Set flag to indicate switch press
        debounce_active1 = 1;  // Set flag to indicate debounce is active
        debounce_count1 = 0;   // Reset debounce counter

        P4IE &= ~SW1;         // Disable switch interrupt during debounce
        TB0CCTL1 &= ~CCIFG;   // Clear any pending timer interrupt
        TB0CCR1 = TB0R + TB0CCR0_INTERVAL; // Set debounce time
        TB0CCTL1 |= CCIE;     // Enable Timer B0 interrupt for debounce
        TB0CCTL0 &= ~CCIE;

    }
}



#pragma vector=PORT2_VECTOR
__interrupt void switchP2_interrupt(void) {
    if (P2IFG & SW2) {
        P2IFG &= ~SW2;  // Clear interrupt flag for SW1
        P2IE &= ~SW2;

        switch_pressed2 = 1;   // Set flag to indicate switch press
        debounce_active2 = 1;  // Set flag to indicate debounce is active
        debounce_count2 = 0;   // Reset debounce counter

        P2IE &= ~SW2;         // Disable switch interrupt during debounce
        TB0CCTL1 &= ~CCIFG;   // Clear any pending timer interrupt
        TB0CCR1 = TB0R + TB0CCR0_INTERVAL; // Set debounce time
        TB0CCTL1 |= CCIE;     // Enable Timer B0 interrupt for debounce
        TB0CCTL0 &= ~CCIE;
    }
}
