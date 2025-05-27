/*
 * switches.c
 *
 *  Created on: Feb 11, 2025
 *      Author: akila
 */


/*
 * switches.c
 *
 *  Created on: Feb 11, 2025
 *      Author: akila
 */

#include  "include\macros.h"  //has every header file and global variables

//shapes

#define DEBOUNCE_RESTART (0)
#define RELEASED (1)
#define PRESSED (0)
#define NOT_OKAY (0)
#define OKAY (1)
#define DEBOUNCE_TIME (200)

volatile unsigned char okay_to_look_at_switch1 = OKAY;
volatile unsigned char sw1_position = RELEASED;
volatile unsigned int count_debounce_SW1;

volatile unsigned char okay_to_look_at_switch2 = OKAY;
volatile unsigned char sw2_position = RELEASED;
volatile unsigned int count_debounce_SW2;

volatile unsigned int number_of_presses = 0;


//------------------------------------------------------------------------------
void Switches_Process(void){
//------------------------------------------------------------------------------
// This function calls the individual Switch Functions
//------------------------------------------------------------------------------
 Switch1_Process();
 Switch2_Process();                                                                               //reenable this
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void Switch1_Process(void){
//------------------------------------------------------------------------------
// Switch 1 Configurations
// Port P4 Pin 1
//------------------------------------------------------------------------------

    if (okay_to_look_at_switch1 && sw1_position){
        if (!(P4IN & SW1)){
            sw1_position = PRESSED;
            okay_to_look_at_switch1 = NOT_OKAY;
            count_debounce_SW1 = DEBOUNCE_RESTART;

            if (number_of_presses == 0){
                 Init_LCD();
                 strcpy(display_line[0], "  SELECT  ");
                 strcpy(display_line[1], " TRIANGLE ");
                 strcpy(display_line[2], "          ");
                 strcpy(display_line[3], "          ");
                 display_changed = TRUE;

                 event = TRIANGLE; //event stright is run
                 number_of_presses++;
            }

            else if (number_of_presses == 1){
                 Init_LCD();
                 strcpy(display_line[0], "  SELECT  ");
                 strcpy(display_line[1], "  CIRCLE  ");
                 strcpy(display_line[2], "          ");
                 strcpy(display_line[3], "          ");
                 display_changed = TRUE;

                 event = CIRCLE; //event straight is run
                 number_of_presses++;
            }

            else if (number_of_presses == 2){
                 Init_LCD();
                 strcpy(display_line[0], "  SELECT  ");
                 strcpy(display_line[1], "  FIGURE8 ");
                 strcpy(display_line[2], "          ");
                 strcpy(display_line[3], "          ");
                 display_changed = TRUE;

                 event = FIGURE8; //event figure eight is run
                 number_of_presses++;
            }

            else if (number_of_presses == 3){
                 Init_LCD();
                 strcpy(display_line[0], "  SELECT  ");
                 strcpy(display_line[1], " TRAINGLE ");
                 strcpy(display_line[2], "          ");
                 strcpy(display_line[3], "          ");
                 display_changed = TRUE;

                 number_of_presses == 0;
                 event = TRIANGLE; //event figure eight is run

            }

        }
    }

    if (count_debounce_SW1 <= DEBOUNCE_TIME){
        count_debounce_SW1++;
    }else{
        okay_to_look_at_switch1 = OKAY;
        if (P4IN & SW1){
            sw1_position = RELEASED;
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
    if (okay_to_look_at_switch2 && sw2_position){
           if (!(P2IN & SW2)){
               sw2_position = PRESSED;
               okay_to_look_at_switch2 = NOT_OKAY;
               count_debounce_SW2 = DEBOUNCE_RESTART;
// do what you want with button press
           }
    }
    if (count_debounce_SW2 <= DEBOUNCE_TIME){
        count_debounce_SW2++;
    }else{
        okay_to_look_at_switch2 = OKAY;
        if (P2IN & SW2){
            sw2_position = RELEASED;
        }
    }
}
//------------------------------------------------------------------------------
