/*
 * motors.c
 *
 *  Created on: Feb 18, 2025
 *      Author: akila
 */



#include  "include\macros.h"  //has every header file and global variables

void check_motor_conflict(void) {
    if ((P6IN & L_FORWARD) && (P6IN & L_REVERSE)) {
        P6OUT &= ~L_FORWARD;  // Shut off both
        P6OUT &= ~L_REVERSE;
        P6OUT |= RED_LED;                   // Turn on RED LED
    }

    if ((P6IN & R_FORWARD) && (P6IN & R_REVERSE)) {
        P6OUT &= ~R_FORWARD;  // Shut off both
        P6OUT &= ~R_REVERSE;
        P6OUT |= RED_LED;                   // Turn on RED LED
    }
}

