/*
 * display_time.c
 *
 *  Created on: Mar 4, 2025
 *      Author: akila
 */


#include  "include\macros.h"  //has every header file and global variables






// Update timer function to be called in the main timer interrupt (Timer0_B0_ISR)
void Update_Timer(void) {
    if (!timer_active) return;  // Stop timer when car stops

    if (current_time >= time_start_point) { //current time increment in sets of 0.2

        timer = current_time - time_start_point;

        // Convert 0.2-second intervals to seconds
        total_seconds = timer / 5;

        // Calculate individual digits
        hundreds = total_seconds / 100;  // Number of hundreds of seconds
        tens = (total_seconds % 100) / 10;  // Number of tens of seconds
        ones = total_seconds % 10;  // Number of ones of seconds
        tenths = (timer % 5) * 2;  // Tenths of a second (0-4 becomes 0-8)
    }
}

// Function to display timer on screen
void Display_Timer(void) {

    Update_Timer();
    // Clear timer display line
    strcpy(display_line[3], "T:        ");

    // Format: "T:XXX.X" where XXX is seconds, X is tenths
    display_line[3][2] = '0' + hundreds;
    display_line[3][3] = '0' + tens;
    display_line[3][4] = '0' + ones;
    display_line[3][5] = '.';
    display_line[3][6] = '0' + tenths;

    display_changed = TRUE;
}
