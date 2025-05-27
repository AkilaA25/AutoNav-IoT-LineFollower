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
          wheel_state = Configure_Wheel_Speeds;
          right_forward = TRUE;
          left_forward = TRUE;
          right_wheel_speed = VERY_SLOW;
          left_wheel_speed = VERY_SLOW;
      }
      break;

    case MOVE:
      // Check if black line detected
      if ((ADC_Left_Det > BLACK_LINE_THRESHOLD) || (ADC_Right_Det > BLACK_LINE_THRESHOLD)) {
        project_state = PAUSE;

        // Display Black Line Detected
        strcpy(display_line[0], "LINE FOUND");
        display_changed = TRUE;

      }
      break;

    case PAUSE:
        // Wait 200ms to stop
        wheel_state = Initiate_Stop;
        project_state = LINE_DETECTED;
        time_counter  = current_time;

    case LINE_DETECTED:
      // Wait for stop completion and transition to next state
      if (current_time  > (time_counter + SEC2_200MS)) {
        // Configure wheels to turn
        project_state = TURNING;

        strcpy(display_line[0], " TURNING  ");
        display_changed = TRUE;

        wheel_state = Configure_Wheel_Speeds;
        right_wheel_speed = VERY_SLOW_TURN;
        left_wheel_speed = VERY_SLOW_TURN;
        right_forward = TRUE;
        left_forward = FALSE;  // One wheel forward, one reverse for turning
      }
      break;

    case TURNING:
      // Turn until both detectors see the black line
      if((ADC_Left_Det > BLACK_LINE_THRESHOLD) && (ADC_Right_Det > BLACK_LINE_THRESHOLD)) {
        project_state = PAUSE2;

        time_start_point = current_time;
        timer_active = TRUE;

        strcpy(display_line[0], " NAVIGATE ");
        display_changed = TRUE;

      }
      break;

    case PAUSE2:
        wheel_state = Initiate_Stop;
        project_state = NAVIGATE;

    case NAVIGATE:
        // Track number of circle completions
        wheel_state = Forward_Adjust;

        // Check if vehicle has completed two full circles
        if(circle_count >= 2) {
          project_state = CENTER_APPROACH;

          strcpy(display_line[0], "CENTER    ");
          display_changed = TRUE;

          // Configure wheels to turn towards circle center
          wheel_state = Configure_Wheel_Speeds;
          right_forward = TRUE;  // Turning inward
          left_forward = FALSE;
          right_wheel_speed = VERY_SLOW;
          left_wheel_speed = VERY_SLOW;

          time_counter  = current_time;
        }
          else {
              project_state = NAVIGATE;
        }

        break;

    case CENTER_APPROACH:
        // turn out of the circle and come back to the center
        if (current_time  > (time_counter + SEC1_200MS)) {
            project_state = CENTER_REACHED;
            time_counter  = current_time;

            wheel_state = Configure_Wheel_Speeds;
            right_forward = TRUE;  // Turning inward
            left_forward = TRUE;
            right_wheel_speed = VERY_SLOW;
            left_wheel_speed = VERY_SLOW;
        }
        break;

    case CENTER_REACHED:
        // turn out of the circle and come back to the center
        if (current_time  > (time_counter + SEC2_200MS)) {
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
