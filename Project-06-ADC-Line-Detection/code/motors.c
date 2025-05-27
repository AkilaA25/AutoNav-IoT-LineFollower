/*
 * motors.c
 *
 *  Created on: Feb 18, 2025
 *      Author: akila
 */



#include  "include\macros.h"  //has every header file and global variables

volatile unsigned char conflict_detected = FALSE;


void check_motor_conflict(void) {
  // Check for conflicts in motor direction signals
    if((RIGHT_FORWARD_SPEED != WHEEL_OFF) && (RIGHT_REVERSE_SPEED != WHEEL_OFF)) {
    // Conflict detected - turn on RED LED
        P1OUT |= RED_LED;
        // Disable both directions
        RIGHT_FORWARD_SPEED = WHEEL_OFF;
        RIGHT_REVERSE_SPEED = WHEEL_OFF;

        conflict_detected = TRUE;
    }

    if((LEFT_FORWARD_SPEED != WHEEL_OFF) && (LEFT_REVERSE_SPEED != WHEEL_OFF)) {
        // Conflict detected - turn on RED LED
        P1OUT |= RED_LED;
        // Disable both directions
        LEFT_FORWARD_SPEED = WHEEL_OFF;
        LEFT_REVERSE_SPEED = WHEEL_OFF;

        conflict_detected = TRUE;
    }

    // Log conflict if detected
    if(conflict_detected) {
        project_state = STOPPED;
        wheel_state = Initiate_Stop;

        strcpy(display_line[0], " CONFLICT ");
        display_changed = TRUE;
    }

}

