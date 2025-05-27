/*
 * globals.h
 *
 *  Created on: Feb 11, 2025
 *      Author: akila
 */

#ifndef INCLUDE_GLOBALS_H_
#define INCLUDE_GLOBALS_H_

volatile unsigned int Last_Time_Sequence;     // a variable to identify Time_Sequence has changed
volatile unsigned int cycle_time;             // is a new time base used to control making shapes
volatile unsigned int time_change;            // is an identifier that a change has occurred


volatile unsigned int current_time;
volatile unsigned int action;
volatile unsigned int time_counter;
volatile unsigned int line_detection_time;  // Time when line was detected


volatile unsigned char emitter_state;



// Global Variables
volatile char slow_input_down;
extern char display_line[4][11];
extern char *display[4];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned int update_display_count;
extern volatile unsigned char update_display;
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
unsigned int test_value;
char chosen_direction;
char change;

unsigned int wheel_move;
char forward;

#endif /* INCLUDE_GLOBALS_H_ */
