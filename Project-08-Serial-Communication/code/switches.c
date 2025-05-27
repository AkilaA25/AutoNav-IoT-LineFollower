/*
 * switches.c
 *
 *  Created on: Feb 11, 2025
 *      Author: akila
 */

#include  "include\macros.h"  //has every header file and global variables

volatile unsigned int number_of_presses = 0;
volatile unsigned int blackVal = 0;
volatile unsigned int whiteVal = 0;


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

        if (number_of_presses == 1){
            strcpy(display_line[0], "          ");
            strcpy(display_line[1], "          ");
            strcpy(display_line[2], "  115,200 ");
            strcpy(display_line[3], "          ");
            display_changed = TRUE;
            Display_Update(0,0,0,0);

            setBaudRate(115200);
        }


        if (number_of_presses == 2){
            strcpy(display_line[0], "          ");
            strcpy(display_line[1], "          ");
            strcpy(display_line[2], "  460,800 ");
            strcpy(display_line[3], "          ");
            display_changed = TRUE;
            Display_Update(0,0,0,0);

            setBaudRate(460800);
        }

        if (number_of_presses > 2){
            number_of_presses = 0;
        }

        UCA0IE |= UCRXIE;

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

        strcpy(display_line[0], " TRANSMIT ");
        strncpy(TransmitArray, ProcessBuffer[display_row], 11);
        strcpy(display_line[3], "          ");
        display_changed = TRUE;
        Display_Update(0,0,0,0);

        UCA0IE |= UCTXIE;

    }

}
//------------------------------------------------------------------------------
