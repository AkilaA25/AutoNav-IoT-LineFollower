/*
 * black_line.c
 *
 *  Created on: Feb 28, 2025
 *      Author: akila
 */

#include  "include\macros.h"  //has every header file and global variables

volatile unsigned int project_state = IDLE_STATE;


//------------------------------------------------------------------------------
// Black Line Process - Handles project state machine
//------------------------------------------------------------------------------
void Black_Line_Process(void) {
  switch(project_state) {
    case IDLE_STATE:
        time_counter = current_time;
        strcpy(display_line[0], "   IDLE   ");
        display_changed = TRUE;
      // Wait for switch 1 to be pressed
      // Transition handled in Switches_Process()
      break;

    case WAIT_TO_START:
      // Wait 1 second before starting
      if(current_time > (time_counter + SEC1_200MS)) {
          project_state = MOVE;

          strcpy(display_line[0], "   MOVE   ");
          display_changed = TRUE;

          // Configure wheel to move forward
          wheel_state = Initiate_Forward;
          right_wheel_speed = VERY_SLOW;
          left_wheel_speed = VERY_SLOW;
      }
      break;

    case MOVE:
      // Check if black line detected
      if ((ADC_Left_Det > BLACK_LINE_THRESHOLD) || (ADC_Right_Det > BLACK_LINE_THRESHOLD)) {
        project_state = LINE_DETECTED;
        wheel_state = Initiate_Stop;

        // Display Black Line Detected
        strcpy(display_line[0], "LINE FOUND");
        display_changed = TRUE;
        time_counter = current_time;
      }
      break;

    case LINE_DETECTED:
      // Wait for stop completion and transition to next state
      if (current_time  > (time_counter + SEC2_200MS)) {
        // Configure wheels to turn
        project_state = TURNING;

        strcpy(display_line[0], " TURNING  ");
        display_changed = TRUE;

        wheel_state = Initiate_Right_Turn;
        right_wheel_speed = VERY_SLOW;
        left_wheel_speed = VERY_SLOW;
      }
      break;

    case TURNING:
      // Turn until both detectors see the black line
      if((ADC_Left_Det > BLACK_LINE_THRESHOLD) && (ADC_Right_Det > BLACK_LINE_THRESHOLD)) {
        project_state = NAVIGATE;
        wheel_state = Follow_Line;

        time_counter = current_time;
        timer_active = TRUE;

        strcpy(display_line[0], " NAVIGATE ");
        display_changed = TRUE;

      }
      break;

    case NAVIGATE:
        if(current_time >= time_counter + CIRCLE_TIMER) {
            wheel_state = Initiate_Right_Turn;
            project_state = CENTER_TURN;
            // Stop timer
            timer_active = FALSE;
            // Turn off emitter to save battery
            emitter_state = EMITTER_OFF;
            Control_Emitter(emitter_state);

            time_counter = current_time;
        }
        break;

    case CENTER_TURN:
        // Start turning
        if (current_time > (time_counter + SEC2_200MS)) {
            project_state = CENTER_APPROACH;
            wheel_state = Initiate_Forward;

            time_counter = current_time;
        }
        break;


    case CENTER_APPROACH:
        if (current_time > (time_counter + SEC2_200MS)) {
            project_state = STOPPED;
            wheel_state = Initiate_Stop;
        }
        break;


    case STOPPED:
      // Final state - display values

      break;

    default:
      project_state = IDLE_STATE;
      break;
  }
}
