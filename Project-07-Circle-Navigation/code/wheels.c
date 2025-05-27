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
  // Safety checks for motor conflicts
   check_motor_conflict();

  // State machine processing
  switch(wheel_state) {
    case IDLE:
      // Idle state - no changes to wheel speeds
      // Check for request to change state

      break;

    case Configure_Wheel_Speeds:
        // Configure the direction and speed for each wheel
        // This state sets up values but doesn't apply them yet

          // Check which direction we're going
          if(right_forward && left_forward) {
              // Reset current speeds for acceleration
              current_right_wheel_speed = WHEEL_OFF;
              current_left_wheel_speed = WHEEL_OFF;
              wheel_state = Forward_Move_Start;
          } else if(!right_forward && !left_forward) {
              // Reset current speeds for acceleration
              current_right_wheel_speed = WHEEL_OFF;
              current_left_wheel_speed = WHEEL_OFF;
              wheel_state = Reverse_Move_Start;
          } else if (right_forward && !left_forward) {
              // One wheel forward, one reverse (turning)
              // Reset current speeds for acceleration
              current_right_wheel_speed = WHEEL_OFF;
              current_left_wheel_speed = WHEEL_OFF;
              wheel_state = Turn_Start;
          }
          break;

    case Forward_Move_Start:

        // First ensure all motors are off
        RIGHT_REVERSE_SPEED = WHEEL_OFF;
        LEFT_REVERSE_SPEED = WHEEL_OFF;

        // Set PWM values for forward movement
        RIGHT_FORWARD_SPEED = current_right_wheel_speed;
        LEFT_FORWARD_SPEED = current_left_wheel_speed;

        match_speed_forward();

      // If both wheels have reached target speed, move to adjustment state
      if((current_right_wheel_speed >= right_wheel_speed) && (current_left_wheel_speed >= left_wheel_speed)) {
        wheel_state = Navigate_Wait;
      }
      break;


    case Navigate_Wait:

        // Check if both speeds are zero
        if ((RIGHT_FORWARD_SPEED == WHEEL_OFF) && (LEFT_FORWARD_SPEED == WHEEL_OFF)) {
            wheel_state = Initiate_Stop;
        }

        break;

    case Forward_Adjust:

        // First ensure all motors are off
        RIGHT_REVERSE_SPEED = WHEEL_OFF;
        LEFT_REVERSE_SPEED = WHEEL_OFF;

        if ((ADC_Left_Det > BLACK_LINE_THRESHOLD) && (ADC_Right_Det > BLACK_LINE_THRESHOLD)) {
          // Both sensors on the line - maintain current speed
            left_wheel_speed = NAVIGATE_LEFT_SLOW;
            right_wheel_speed = NAVIGATE_RIGHT_SLOW;
        }
        else if ((ADC_Left_Det < BLACK_LINE_THRESHOLD)) {
          // Left sensor on line - slow down right wheel to steer back
            current_right_wheel_speed = WHEEL_OFF;
            right_wheel_speed = WHEEL_OFF;
            left_wheel_speed = NAVIGATE_LEFT_SLOW;    // Slightly increase left wheel speed
        }
        else if ((ADC_Right_Det < BLACK_LINE_THRESHOLD)) {
          // Right sensor on line - slow down left wheel to steer back
            current_left_wheel_speed = WHEEL_OFF;
            right_wheel_speed = NAVIGATE_RIGHT_SLOW;  // Slightly increase right wheel speed
            left_wheel_speed = WHEEL_OFF; // Reduce left wheel speed
        }

        match_speed_forward();

        // Check if both speeds are zero
        if ((RIGHT_FORWARD_SPEED == WHEEL_OFF) && (LEFT_FORWARD_SPEED == WHEEL_OFF)) {
          wheel_state = Initiate_Stop;
        }
        break;

    case Turn_Start:
      // Set initial PWM values for turning clockwise (right wheel forward, left wheel reverse)
        // Ensure all conflicting motors are off
        RIGHT_REVERSE_SPEED = WHEEL_OFF;
        LEFT_FORWARD_SPEED = WHEEL_OFF;

        RIGHT_FORWARD_SPEED = current_right_wheel_speed;
        LEFT_REVERSE_SPEED = current_left_wheel_speed;

      // Gradually increase right wheel speed (forward)
        match_speed_turn();

      // If both wheels have reached target speed, move to turn adjustment state
      if(current_right_wheel_speed >= right_wheel_speed &&
         current_left_wheel_speed >= left_wheel_speed) {
        wheel_state = Turn_Adjust;
      }
      break;

    case Turn_Adjust:
      // Adjust wheel speeds based on line detection or other factors

      // Check if both speeds are zero
      if((RIGHT_FORWARD_SPEED == WHEEL_OFF) && (LEFT_REVERSE_SPEED == WHEEL_OFF)) {
        wheel_state = Initiate_Stop;
      }
      break;


    case Reverse_Move_Start:
        // Ensure all conflicting motors are off
        RIGHT_FORWARD_SPEED = WHEEL_OFF;
        LEFT_FORWARD_SPEED = WHEEL_OFF;

        RIGHT_REVERSE_SPEED = current_right_wheel_speed;
        LEFT_REVERSE_SPEED = current_left_wheel_speed;

        match_speed_reverse();

        // If both wheels have reached target speed, move to adjustment state
        if(current_right_wheel_speed >= right_wheel_speed &&
           current_left_wheel_speed >= left_wheel_speed) {
          wheel_state = Reverse_Adjust;
        }
        break;

    case Reverse_Adjust:
      // Line following adjustment logic for reverse movement
      if (ADC_Left_Det > BLACK_LINE_THRESHOLD && ADC_Right_Det > BLACK_LINE_THRESHOLD) {
        // Both sensors on the line - maintain current speed
        RIGHT_REVERSE_SPEED = right_wheel_speed;
        LEFT_REVERSE_SPEED = left_wheel_speed;
      }
      else if (ADC_Left_Det < BLACK_LINE_THRESHOLD) {
        // Left sensor on line - slow down right wheel to steer back
        RIGHT_REVERSE_SPEED = right_wheel_speed * 0.8;
        LEFT_REVERSE_SPEED = left_wheel_speed * 1.2;
      }
      else if (ADC_Right_Det < BLACK_LINE_THRESHOLD) {
        // Right sensor on line - slow down left wheel to steer back
        RIGHT_REVERSE_SPEED = right_wheel_speed * 1.2;
        LEFT_REVERSE_SPEED = left_wheel_speed * 0.8;
      }

      // Check if both speeds are zero
      if ((RIGHT_REVERSE_SPEED == WHEEL_OFF) && (LEFT_REVERSE_SPEED == WHEEL_OFF)) {
        wheel_state = Initiate_Stop;
      }
      break;



    case Initiate_Stop:
      // Stop all wheels
      RIGHT_FORWARD_SPEED = WHEEL_OFF;
      LEFT_FORWARD_SPEED = WHEEL_OFF;
      RIGHT_REVERSE_SPEED = WHEEL_OFF;
      LEFT_REVERSE_SPEED = WHEEL_OFF;

      // Move to Stop state
      wheel_state = Stop;
      break;

    case Stop:
        //nothing
      break;

    default:
      wheel_state = IDLE;
      break;
  }
}
