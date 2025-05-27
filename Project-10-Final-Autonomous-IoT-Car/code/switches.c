/*
 * switches.c
 *
 *  Created on: Feb 11, 2025
 *      Author: akila
 */

#include  "include\macros.h"  //has every header file and global variables

volatile unsigned int number_of_presses = 0;

//------------------------------------------------------------------------------
void Switches_Process(void){
//------------------------------------------------------------------------------
// This function calls the individual Switch Functions
//------------------------------------------------------------------------------
 Switch1_Process();
 Switch2_Process();
}
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
void Switch1_Process(void){
//------------------------------------------------------------------------------
// Switch 1 Configurations
// Port P4 Pin 1
//------------------------------------------------------------------------------

    if (switch_pressed1){
        switch_pressed1 = 0;
        switch_pressed2 = 0;

        number_of_presses++;
        unsigned int avg = (ADC_Left_Det + ADC_Right_Det) / 2;

        if (number_of_presses == 1){
            Control_Emitter(EMITTER_ON);
            show_adc = 1;
            strcpy(display_line[0], "  White:  ");
            strcpy(display_line[1], "          ");
            display_changed = TRUE;
        }
        else if (number_of_presses == 2){
            WHITE_LINE_THRESHOLD = avg;
            strcpy(display_line[0], "  Black:  ");
            strcpy(display_line[1], "          ");
            display_changed = TRUE;
        }
        else if (number_of_presses == 3){
            BLACK_LINE_THRESHOLD = avg - 100;
            Control_Emitter(EMITTER_OFF);
            show_adc = 0;
            ip_show = 1;
        }

    }

}
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
void Switch2_Process(void){
//------------------------------------------------------------------------------
// Switch 2 Configurations
// Port P2 Pin 3
//------------------------------------------------------------------------------

    if (switch_pressed2){
        switch_pressed1 = 0;
        switch_pressed2 = 0;

        P6DIR ^= LCD_BACKLITE;          // Set LCD_BACKLITE direction to output

    }

}
//------------------------------------------------------------------------------
