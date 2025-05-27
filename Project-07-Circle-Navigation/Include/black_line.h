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
#define PAUSE 3
#define LINE_DETECTED 4
#define TURNING 5
#define PAUSE2 6
#define NAVIGATE 7
#define CENTER_APPROACH 8
#define CENTER_REACHED 9
#define STOPPED 10

#define BLACK_LINE_THRESHOLD 700

// Global variables for project control
extern volatile unsigned int project_state;
volatile unsigned int circle_count;



void Black_Line_Process(void);

#endif /* INCLUDE_BLACK_LINE_H_ */
