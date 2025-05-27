/*
 * states.h
 *
 *  Created on: Feb 11, 2025
 *      Author: akila
 */



// STATES ======================================================================
#define NONE ('N')
#define STRAIGHT ('L')
#define CIRCLE ('C')
#define FIGURE8 ('F')
#define TRIANGLE ('T')

#define WAIT ('W')
#define START ('S')
#define RUN ('R')
#define TURN ('P')
#define END ('E')
#define WAITING2START (200)


// STRAIGHT
#define S_WHEEL_COUNT_TIME (10)  //per segment
#define S_RIGHT_COUNT_TIME (6)  //used to be 5
#define S_LEFT_COUNT_TIME (11)
#define S_TRAVEL_DISTANCE (20)  //number of segments

// CIRCLE
#define C_WHEEL_COUNT_TIME (30)
#define C_RIGHT_COUNT_TIME (3)
#define C_LEFT_COUNT_TIME (30)
#define C_TRAVEL_DISTANCE (40)

// FIGURE 8
#define F_WHEEL_COUNT_TIME (30)
#define F1_RIGHT_COUNT_TIME (3)
#define F1_LEFT_COUNT_TIME (30)
#define F2_RIGHT_COUNT_TIME (30)
#define F2_LEFT_COUNT_TIME (3)
#define F_TRAVEL_DISTANCE (40)

// TRIANGLE
#define T_WHEEL_COUNT_TIME (9)
#define T_RIGHT_COUNT_TIME (5)
#define T_LEFT_COUNT_TIME (9)
#define T_TRAVEL_DISTANCE (8)


#define T_TURN_RIGHT_COUNT_TIME (1)
#define T_TURN_LEFT_COUNT_TIME (30)
#define T_TURN_WHEEL_COUNT_TIME (30)                 //needs to be bigger than travel distance
#define T_TURN_TRAVEL_DISTANCE (4)//go back to 6 if neccesary
//Functions
void Run_Straight(void);
void Run_Circle(void);
void Run_Figure8(void);
void Run_Triangle(void);


void straight_run_case(void);
void circle_run_case(void);
void figure8_run_case(void);
void triangle_run_case(void);
void turn_triangle_case(void);


void wait_case(void);
void start_case(void);
void end_case(void);

void Forward_On(void);
void Forward_Off(void);


#ifndef INCLUDE_STATES_H_
#define INCLUDE_STATES_H_



#endif /* INCLUDE_STATES_H_ */

