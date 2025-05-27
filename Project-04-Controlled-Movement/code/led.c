/*
 * led.c
 *
 *  Created on: Jan 30, 2025
 *      Author: akila
 */

#include  "include\macros.h"  //has every header file



void Init_LEDs(void){
//------------------------------------------------------------------------------
// LED Configurations
//------------------------------------------------------------------------------
// Turns on both LEDs
  P1OUT &= ~RED_LED;
  P6OUT &= ~GRN_LED;
//------------------------------------------------------------------------------
}

