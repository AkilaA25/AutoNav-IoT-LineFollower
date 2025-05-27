/*
 * wheels.c
 *
 *  Created on: Feb 27, 2025
 *      Author: akila
 */


#include "include\macros.h"  // Has every header file and global variables


// Global Variables
extern volatile unsigned char wheel_state = IDLE;
extern volatile unsigned int right_wheel_speed = 0;
extern volatile unsigned int left_wheel_speed = 0;

extern volatile unsigned char right_forward = TRUE;
extern volatile unsigned char left_forward = TRUE;



//------------------------------------------------------------------------------
// Wheels_Process - State Machine for controlling wheel movement
//------------------------------------------------------------------------------
void Wheels_Process(void) {
    switch(wheel_state) {
        case IDLE:
            // Wheels idle, waiting for command
            LEFT_FORWARD_SPEED = WHEEL_OFF;
            LEFT_REVERSE_SPEED = WHEEL_OFF;
            RIGHT_FORWARD_SPEED = WHEEL_OFF;
            RIGHT_REVERSE_SPEED = WHEEL_OFF;

            break;

        case Initiate_Forward:
            // Stop all movement first
            LEFT_FORWARD_SPEED = WHEEL_OFF;
            LEFT_REVERSE_SPEED = WHEEL_OFF;
            RIGHT_FORWARD_SPEED = WHEEL_OFF;
            RIGHT_REVERSE_SPEED = WHEEL_OFF;

            // Reset current speeds for smooth acceleration
            current_left_wheel_speed = 0;
            current_right_wheel_speed = 0;

            // Change state to forward movement
            wheel_state = Move_Forward;
            break;

        case Move_Forward:
            // Apply forward movement with acceleration
            match_speed_forward();
            break;

        case Initiate_Reverse:
            // Stop all movement first
            LEFT_FORWARD_SPEED = WHEEL_OFF;
            LEFT_REVERSE_SPEED = WHEEL_OFF;
            RIGHT_FORWARD_SPEED = WHEEL_OFF;
            RIGHT_REVERSE_SPEED = WHEEL_OFF;

            // Reset current speeds for smooth acceleration
            current_left_wheel_speed = 0;
            current_right_wheel_speed = 0;

            // Change state to reverse movement
            wheel_state = Move_Reverse;
            break;

        case Move_Reverse:
            // Apply reverse movement with acceleration
            match_speed_reverse();
            break;

        case Initiate_Right_Turn:
            // Stop all movement first
            LEFT_FORWARD_SPEED = WHEEL_OFF;
            LEFT_REVERSE_SPEED = WHEEL_OFF;
            RIGHT_FORWARD_SPEED = WHEEL_OFF;
            RIGHT_REVERSE_SPEED = WHEEL_OFF;

            // Reset current speeds for smooth transition
            current_left_wheel_speed = 0;
            current_right_wheel_speed = 0;

            // Change state to right turn
            wheel_state = Turn_Right;
            break;

        case Turn_Right:
            // Left wheel forward, right wheel slower or reverse for sharper turns
            match_speed_turn_right();
            break;

        case Initiate_Left_Turn:
            // Stop all movement first
            LEFT_FORWARD_SPEED = WHEEL_OFF;
            LEFT_REVERSE_SPEED = WHEEL_OFF;
            RIGHT_FORWARD_SPEED = WHEEL_OFF;
            RIGHT_REVERSE_SPEED = WHEEL_OFF;

            // Reset current speeds for smooth transition
            current_left_wheel_speed = 0;
            current_right_wheel_speed = 0;

            // Change state to left turn
            wheel_state = Turn_Left;
            break;

        case Turn_Left:
            // Right wheel forward, left wheel slower or reverse for sharper turns
            match_speed_turn_left();
            break;

        case Follow_Line:
            if (ADC_Left_Det > BLACK_LINE_THRESHOLD && ADC_Right_Det > BLACK_LINE_THRESHOLD) {
                // Move straight when both sensors detect the black line
                LEFT_REVERSE_SPEED = WHEEL_OFF;
                RIGHT_REVERSE_SPEED = WHEEL_OFF;
                LEFT_FORWARD_SPEED = SLOW10;
                RIGHT_FORWARD_SPEED = SLOW10;

            }
            else if (ADC_Left_Det > BLACK_LINE_THRESHOLD && ADC_Right_Det < BLACK_LINE_THRESHOLD) {
                // If only left sensor sees black, turn left (toward the line)
                LEFT_REVERSE_SPEED = WHEEL_OFF;
                RIGHT_REVERSE_SPEED = WHEEL_OFF;
                LEFT_FORWARD_SPEED = WHEEL_OFF;
                RIGHT_FORWARD_SPEED = SLOW10;

            }
            else if (ADC_Right_Det > BLACK_LINE_THRESHOLD && ADC_Left_Det < BLACK_LINE_THRESHOLD) {
                // If only right sensor sees black, turn right (toward the line)
                RIGHT_FORWARD_SPEED = WHEEL_OFF;
                LEFT_REVERSE_SPEED = WHEEL_OFF;
                RIGHT_REVERSE_SPEED = WHEEL_OFF;
                LEFT_FORWARD_SPEED = SLOW10;

            }
            else {
                // If both sensors are off the line (both seeing white),
                // move backward until any sensor detects the black line again
                LEFT_FORWARD_SPEED = WHEEL_OFF;
                RIGHT_FORWARD_SPEED = WHEEL_OFF;
                LEFT_REVERSE_SPEED = SLOW10;
                RIGHT_REVERSE_SPEED = SLOW10;
            }
            break;


        case Initiate_Stop:
            LEFT_FORWARD_SPEED = WHEEL_OFF;
            LEFT_REVERSE_SPEED = WHEEL_OFF;
            RIGHT_FORWARD_SPEED = WHEEL_OFF;
            RIGHT_REVERSE_SPEED = WHEEL_OFF;
            wheel_state = IDLE;
            break;

        default:
            wheel_state = IDLE;
            break;
    }
}
