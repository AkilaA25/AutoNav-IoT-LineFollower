/*
 * macros.h
 *
 *  Created on: Jan 30, 2025
 *      Author: akila
 */
//

volatile unsigned char event;



#define DEBOUNCE_TIME (5)


#include <string.h>
// list of all .h files and global variables
#include  "include\clocks.h"
#include  "include\display.h"
#include  "include\functions.h"
#include  "include\init.h"
#include  "include\LCD.h"
#include  "include\led.h"
#include  "include\ports.h"
#include  "include\shapes.h"
#include  "include\system.h"
#include  "include\globals.h"      //all global variables
#include  "include\timers.h"
#include  "msp430.h"


#ifndef MACROS_H_
#define MACROS_H_

#define ALWAYS                  (1)
#define RESET_STATE             (0)
#define RED_LED              (0x01) // RED LED 0
#define GRN_LED              (0x40) // GREEN LED 1
#define TEST_PROBE           (0x01) // 0 TEST PROBE
#define TRUE                 (0x01) //


// HOMEWORK 5
#define USE_GPIO            (0x00)
#define USE_SMCLK           (0x01)


#endif /* MACROS_H_ */
