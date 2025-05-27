/*
 * black_line.h
 *
 *  Created on: Feb 28, 2025
 *      Author: akila
 */

#ifndef INCLUDE_BLACK_LINE_H_
#define INCLUDE_BLACK_LINE_H_

// State definitions for project
#define IDLE_STATE 0
#define WAIT_TO_START 1
#define MOVE_UP 2
#define MOVE_TO_BOARD 3
#define MOVE_TO_LINE 4
#define LINE_DETECTED 5
#define TURNING 6
#define TURN_DONE 7
#define NAVIGATE_LINE 8
#define CIRCLE_DETECTED 9
#define NAVIGATE_CIRCLE 10
#define EXIT_INITIALIZE 11
#define EXIT_TURN 12
#define EXIT 13
#define STOPPED 14


// Global variables for project control
extern volatile unsigned int project_state;


void Black_Line_Process(void);

#endif /* INCLUDE_BLACK_LINE_H_ */
