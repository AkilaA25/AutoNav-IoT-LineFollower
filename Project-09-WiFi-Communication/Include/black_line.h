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
#define MOVE 2
#define LINE_DETECTED 3
#define TURNING 4
#define NAVIGATE 5
#define CENTER_TURN 6
#define CENTER_APPROACH 7
#define STOPPED 8

#define BLACK_LINE_THRESHOLD 700

#define CIRCLE_TIMER 300

// Global variables for project control
extern volatile unsigned int project_state;


void Black_Line_Process(void);

#endif /* INCLUDE_BLACK_LINE_H_ */
