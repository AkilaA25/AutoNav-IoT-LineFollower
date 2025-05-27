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
      //transition handled in command.c
      break;

    case WAIT_TO_START:
      // Wait 1 second before starting
      if(current_time > (line_counter + SEC1_200MS)) {
          project_state = MOVE_UP;

          strcpy(display_line[0], " BL Start ");
          display_changed = TRUE;

          line_counter = current_time;

          // Configure wheel to move forward
          wheel_state = Initiate_Forward;
          right_wheel_speed = SLOW15;
          left_wheel_speed = SLOW15;
      }
      break;

    case MOVE_UP:
      // Wait 1 second before starting
      if(current_time > (line_counter + 3)) {
          project_state = MOVE_TO_BOARD;

          line_counter = current_time;

          // Configure wheel to move forward
          wheel_state = Initiate_Forward;
          right_wheel_speed = SLOW20;
          left_wheel_speed = SLOW11;
      }
      break;

    case MOVE_TO_BOARD:
      // Wait 1 second before starting
        if (current_time > (line_counter + SEC7_200MS) && ((ADC_Left_Det < WHITE_LINE_THRESHOLD) || (ADC_Right_Det < WHITE_LINE_THRESHOLD))) {
            project_state = MOVE_TO_LINE;

            wheel_state = Initiate_Forward;
            right_wheel_speed = SLOW12;
            left_wheel_speed = SLOW12;
        }
      break;

    case MOVE_TO_LINE:
      // Check if black line detected
      if ((ADC_Left_Det > BLACK_LINE_THRESHOLD) || (ADC_Right_Det > BLACK_LINE_THRESHOLD)) {
        project_state = LINE_DETECTED;
        wheel_state = Initiate_Stop;

        // Display Black Line Detected
        strcpy(display_line[0], "Intercept ");
        display_changed = TRUE;
        line_counter = current_time;
      }
      break;

    case LINE_DETECTED:
      // Wait for stop completion and transition to next state
      if (current_time  > (line_counter + SEC5_200MS)) {
        // Configure wheels to turn
        project_state = TURNING;

        strcpy(display_line[0], " BL Turn  ");
        display_changed = TRUE;

        wheel_state = Initiate_Left_Turn;
        right_wheel_speed = SLOW10;
        left_wheel_speed = SLOW10;
      }
      break;

    case TURNING:
      // Turn until both detectors see the black line
      if((ADC_Left_Det > BLACK_LINE_THRESHOLD) && (ADC_Right_Det > BLACK_LINE_THRESHOLD)) {
        project_state = TURN_DONE;
        wheel_state = Initiate_Stop;

        line_counter = current_time;
      }

      break;

    case TURN_DONE:
        if(current_time  > (line_counter + SEC5_200MS)) {
          project_state = NAVIGATE_LINE;
          wheel_state = Follow_Line;

          line_counter = current_time;

          strcpy(display_line[0], "BL Travel ");
          display_changed = TRUE;

        }
      break;

    case NAVIGATE_LINE:
      // Turn until both detectors see the black line
      if(current_time  > (line_counter + SEC10_200MS)) {
        project_state = CIRCLE_DETECTED;
        wheel_state = Initiate_Stop;

        line_counter = current_time;

        strcpy(display_line[0], "BL Circle ");
        display_changed = TRUE;

      }
      break;

      case CIRCLE_DETECTED:
        // Turn until both detectors see the black line
        if(current_time  > (line_counter + SEC5_200MS)) {
          project_state = NAVIGATE_CIRCLE;
          wheel_state = Follow_Line;

          line_counter = current_time;

        }
        break;

      case NAVIGATE_CIRCLE:
        // Navigate till EXIT command
        break;

      case EXIT_INITIALIZE:
          // Start turning
          project_state = EXIT_TURN;
          wheel_state = Initiate_Left_Turn;
          right_wheel_speed = SLOW10;
          left_wheel_speed = SLOW10;
          line_counter = current_time;
          strcpy(display_line[0], " BL Exit  ");
          display_changed = TRUE;

      case EXIT_TURN:
        // Start turning
        if (current_time > (line_counter + 2)) {
            project_state = EXIT;
            wheel_state = Initiate_Forward;
            line_counter = current_time;
        }
        break;

    case EXIT:
        if (current_time > (line_counter + SEC2_200MS)) {
            strcpy(display_line[0], " I'M FREE ");
            display_changed = TRUE;

            project_state = STOPPED;
            wheel_state = Initiate_Stop;
            timer_active = FALSE;
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
