/*
 * motors.c
 *
 *  Created on: Feb 18, 2025
 *      Author: akila
 */



#include  "include\macros.h"  //has every header file and global variables

volatile unsigned char conflict_detected = FALSE;
volatile unsigned int acceleration_step = 1000; // Speed increment per cycle


void check_motor_conflict(void) {
  // Check for conflicts in motor direction signals
    if((RIGHT_FORWARD_SPEED != WHEEL_OFF) && (RIGHT_REVERSE_SPEED != WHEEL_OFF)) {
    // Conflict detected - turn on RED LED
        P1OUT |= RED_LED;
        // Disable both directions
        RIGHT_FORWARD_SPEED = WHEEL_OFF;
        RIGHT_REVERSE_SPEED = WHEEL_OFF;

        conflict_detected = TRUE;
    }

    if((LEFT_FORWARD_SPEED != WHEEL_OFF) && (LEFT_REVERSE_SPEED != WHEEL_OFF)) {
        // Conflict detected - turn on RED LED
        P1OUT |= RED_LED;
        // Disable both directions
        LEFT_FORWARD_SPEED = WHEEL_OFF;
        LEFT_REVERSE_SPEED = WHEEL_OFF;

        conflict_detected = TRUE;
    }

    // Log conflict if detected
    if(conflict_detected) {
        project_state = STOPPED;
        wheel_state = Initiate_Stop;

        strcpy(display_line[0], " CONFLICT ");
        display_changed = TRUE;
    }

}


void match_speed_forward(void){
    // Gradually increase right wheel speed
    if (current_right_wheel_speed == 0) RIGHT_FORWARD_SPEED = WHEEL_OFF;
    if (current_left_wheel_speed == 0) LEFT_FORWARD_SPEED = WHEEL_OFF;

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
}

void match_speed_reverse(void){

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
}

void match_speed_turn(void){
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
}

