/*
 * switches.c
 *
 *  Created on: Feb 11, 2025
 *      Author: akila
 */

#include  "include\macros.h"  //has every header file and global variables

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

        project_state = WAIT_TO_START;
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

        if (emitter_state == EMITTER_ON){
            emitter_state = EMITTER_OFF;
        }
        else if (emitter_state == EMITTER_OFF) {
            emitter_state = EMITTER_ON;
        }

    }

}
//------------------------------------------------------------------------------
