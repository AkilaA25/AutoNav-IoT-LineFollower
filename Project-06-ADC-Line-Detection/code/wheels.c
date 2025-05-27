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

// Current wheel speed variables for acceleration
volatile unsigned int current_right_wheel_speed = 0;
volatile unsigned int current_left_wheel_speed = 0;
volatile unsigned int acceleration_step = 1000; // Speed increment per cycle

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
        } else {
          // One wheel forward, one reverse (turning)
          if(right_forward && !left_forward) {
            // Reset current speeds for acceleration
            current_right_wheel_speed = WHEEL_OFF;
            current_left_wheel_speed = WHEEL_OFF;
            wheel_state = Turn_Start;
          }

        }
        break;

    case Forward_Move_Start:

        // First ensure all motors are off
        RIGHT_REVERSE_SPEED = WHEEL_OFF;
        LEFT_REVERSE_SPEED = WHEEL_OFF;

        // Set PWM values for forward movement
        RIGHT_FORWARD_SPEED = current_right_wheel_speed;
        LEFT_FORWARD_SPEED = current_left_wheel_speed;

      // Gradually increase right wheel speed
      if(current_right_wheel_speed < right_wheel_speed) {
        current_right_wheel_speed += acceleration_step;
        if(current_right_wheel_speed > right_wheel_speed) {
          current_right_wheel_speed = right_wheel_speed;
        }
        RIGHT_FORWARD_SPEED = current_right_wheel_speed;
      }

      // Gradually increase left wheel speed
      if(current_left_wheel_speed < left_wheel_speed) {
        current_left_wheel_speed += acceleration_step;
        if(current_left_wheel_speed > left_wheel_speed) {
          current_left_wheel_speed = left_wheel_speed;
        }
        LEFT_FORWARD_SPEED = current_left_wheel_speed;
      }

      // If both wheels have reached target speed, move to adjustment state
      if((current_right_wheel_speed >= right_wheel_speed) && (current_left_wheel_speed >= left_wheel_speed)) {
        wheel_state = Forward_Adjust;
      }
      break;

    case Forward_Adjust:
      // Adjust wheel speeds based on line detection
      // This is where black line following adjustments would be made

      // Check if both speeds are zero
      if((RIGHT_FORWARD_SPEED == WHEEL_OFF) && (LEFT_FORWARD_SPEED == WHEEL_OFF)) {
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
      if(current_right_wheel_speed < right_wheel_speed) {
        current_right_wheel_speed += acceleration_step;
        if(current_right_wheel_speed > right_wheel_speed) {
          current_right_wheel_speed = right_wheel_speed;
        }
        RIGHT_FORWARD_SPEED = current_right_wheel_speed;
      }

      // Gradually increase left wheel speed (reverse)
      if(current_left_wheel_speed < left_wheel_speed) {
        current_left_wheel_speed += acceleration_step;
        if(current_left_wheel_speed > left_wheel_speed) {
          current_left_wheel_speed = left_wheel_speed;
        }
        LEFT_REVERSE_SPEED = current_left_wheel_speed;
      }

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

        // Gradually increase right wheel speed
        if(current_right_wheel_speed < right_wheel_speed) {
          current_right_wheel_speed += acceleration_step;
          if(current_right_wheel_speed > right_wheel_speed) {
            current_right_wheel_speed = right_wheel_speed;
          }
          RIGHT_REVERSE_SPEED = current_right_wheel_speed;
        }

        // Gradually increase left wheel speed
        if(current_left_wheel_speed < left_wheel_speed) {
          current_left_wheel_speed += acceleration_step;
          if(current_left_wheel_speed > left_wheel_speed) {
            current_left_wheel_speed = left_wheel_speed;
          }
          LEFT_REVERSE_SPEED = current_left_wheel_speed;
        }

        // If both wheels have reached target speed, move to adjustment state
        if(current_right_wheel_speed >= right_wheel_speed &&
           current_left_wheel_speed >= left_wheel_speed) {
          wheel_state = Reverse_Adjust;
        }
        break;

    case Reverse_Adjust:

      // Adjust wheel speeds based on line detection or other factors

      // Check if both speeds are zero
      if((RIGHT_REVERSE_SPEED == WHEEL_OFF) && (LEFT_REVERSE_SPEED == WHEEL_OFF)) {
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
