/*
 * straight.c
 *
 *  Created on: Feb 11, 2025
 *      Author: akila
 */
#include  "include\macros.h"

//this file contains all global variables


//FOR SHAPES
volatile unsigned char state = WAIT;
volatile unsigned int delay_start = 0;
volatile unsigned int right_motor_count = 0;
volatile unsigned int left_motor_count = 0;
volatile unsigned int segment_count = 0;

volatile unsigned int triangle_sides = 0;
volatile unsigned int figure8s = 0;




void Run_Straight(void){
    switch(state){
    case WAIT: // Begin
        wait_case();
        break; //
    case START: // Begin
        start_case();
        break; //
    case RUN: // Run
        straight_run_case();
        break; //
    case END: // End
        end_case();
        break; //
    default: break;
    }
}

void Run_Circle(void){
    switch(state){
    case WAIT: // Begin
        wait_case();
        break; //
    case START: // Begin
        start_case();
        break; //
    case RUN: // Run
        circle_run_case();
        break; //
    case END: // End
        end_case();
        break; //
    default: break;
    }
}

void Run_Figure8(void){
    switch(state){
    case WAIT: // Begin
        wait_case();
        break; //
    case START: // Begin
        start_case();
        break; //
    case RUN: // Run
        figure8_run_case();
        break; //
    case END: // End
        end_case();
        break; //
    default: break;
    }
}

void Run_Triangle(void){
    switch(state){
    case WAIT: // Begin
        wait_case();
        break; //
    case START: // Begin
        start_case();
        break; //
    case RUN: // Run
        triangle_run_case();
    case TURN:
        turn_triangle_case();
        break; //
    case END: // End
        end_case();
        break; //
    default: break;
    }
}


void Forward_On(void){
    P6OUT |= R_FORWARD;
    P6OUT |= L_FORWARD;
}

void Forward_Off(void){
    P6OUT &= ~R_FORWARD;
    P6OUT &= ~L_FORWARD;
}


void wait_case(void){
    if(time_change){
        time_change = 0;
        if(delay_start++ >= WAITING2START){
            delay_start = 0;
            state = START;
        }
    }
}

void start_case(void){
    cycle_time = 0;
    right_motor_count = 0;
    left_motor_count = 0;
    Forward_On();
    segment_count = 0;
    state = RUN;
}



void end_case(void){
    Forward_Off();
    state = WAIT;
    event = NONE;
}



void straight_run_case(void){
    if(time_change){
        time_change = 0;
        if(segment_count <= S_TRAVEL_DISTANCE){
            if(right_motor_count++ >= S_RIGHT_COUNT_TIME){  //does the turning
                P6OUT &= ~R_FORWARD;
            }
            if(left_motor_count++ >= S_LEFT_COUNT_TIME){  //does the turning
                P6OUT &= ~L_FORWARD;
            }
            if(cycle_time >= S_WHEEL_COUNT_TIME){
                cycle_time = 0;
                right_motor_count = 0;
                left_motor_count = 0;
                segment_count++;
                Forward_On();
            }
        }else{
            state = END;
        }
    }
}


void circle_run_case(void){
    if(time_change){
        time_change = 0;
        if(segment_count <= C_TRAVEL_DISTANCE){
            if(right_motor_count++ >= C_RIGHT_COUNT_TIME){  //does the turning
                P6OUT &= ~R_FORWARD;
            }
            if(left_motor_count++ >= C_LEFT_COUNT_TIME){  //does the turning
                P6OUT &= ~L_FORWARD;
            }
            if(cycle_time >= C_WHEEL_COUNT_TIME){
                cycle_time = 0;
                right_motor_count = 0;
                left_motor_count = 0;
                segment_count++;
                Forward_On();
            }
        }else{
            state = END;
        }
    }
}



void figure8_run_case(void){
    if(time_change){
        time_change = 0;
        if(segment_count <= F_TRAVEL_DISTANCE){
            if(segment_count < F_TRAVEL_DISTANCE / 2) {
                if(right_motor_count++ >= F1_RIGHT_COUNT_TIME){
                    P6OUT &= ~R_FORWARD;
                }
                if(left_motor_count++ >= F1_LEFT_COUNT_TIME){
                    P6OUT &= ~L_FORWARD;
                }
            } else {
                if(right_motor_count++ >= F2_RIGHT_COUNT_TIME){
                    P6OUT &= ~R_FORWARD;
                }
                if(left_motor_count++ >= F2_LEFT_COUNT_TIME){
                    P6OUT &= ~L_FORWARD;
                }
            }

            if(cycle_time >= F_WHEEL_COUNT_TIME){
                cycle_time = 0;
                right_motor_count = 0;
                left_motor_count = 0;
                segment_count++;
                Forward_On();
            }

        }else if(figure8s == 0){
            figure8s++;
            segment_count = 0;
            state = RUN;
        }else{
            state = END;
        }
    }
}


void triangle_run_case(void) {

    if (time_change) {
        time_change = 0;
        // A triangle has 3 sides, and we repeat it twice (6 sides total)
        if (segment_count <= T_TRAVEL_DISTANCE) {
            if(right_motor_count++ >= T_RIGHT_COUNT_TIME){  //does the turning
                P6OUT &= ~R_FORWARD;
            }
            if(left_motor_count++ >= T_LEFT_COUNT_TIME){  //does the turning
                P6OUT &= ~L_FORWARD;
            }
            if(cycle_time >= T_WHEEL_COUNT_TIME){
                cycle_time = 0;
                right_motor_count = 0;
                left_motor_count = 0;
                segment_count++;
                Forward_On();
            }

        }else if(triangle_sides <= 6){
            segment_count = 0;
            triangle_sides++;
            state = TURN;
        }else{
            state = END;
        }
    }
}

// Separate function for handling the turn
void turn_triangle_case(void) {
    if(time_change){
        time_change = 0;
        if(segment_count <= T_TURN_TRAVEL_DISTANCE){
            if(right_motor_count++ >= T_TURN_RIGHT_COUNT_TIME){  //does the turning
                P6OUT &= ~R_FORWARD;
            }
            if(left_motor_count++ >= T_TURN_LEFT_COUNT_TIME){  //does the turning
                P6OUT &= ~L_FORWARD;
            }
            if(cycle_time >= T_TURN_WHEEL_COUNT_TIME){
                cycle_time = 0;
                right_motor_count = 0;
                left_motor_count = 0;
                segment_count++;
                Forward_On();
            }
        }else{
            segment_count = 0;
            state = RUN;
        }
    }
}
