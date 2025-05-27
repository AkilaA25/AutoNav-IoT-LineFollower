/*
 * command.c
 *
 *  Created on: Apr 7, 2025
 *      Author: akila
 */


#include  "include\macros.h"  //has every header file and global variables


void Process_IOT_Command(void){
    if (process_command){
        char period_str[5]; // 4 digits + null terminator
        memcpy(period_str, &IOT_process_buffer[command_row][16], 4);
        period_str[4] = '\0';
        time_period = atoi(period_str); // This will now contain the number of 200ms intervals

        char command_str[6];  // 5 characters for "F0001" + 1 for the null terminator
        memcpy(command_str, &IOT_process_buffer[command_row][15], 5);
        command_str[5] = ' ';

        if ((IOT_process_buffer[command_row][15] == 'F')){
            if (display_action){
                strcpy(display_line[0], "          ");
                strcpy(display_line[1], first_ip_buffer);
                strcpy(display_line[2], second_ip_buffer);
                strcpy(display_line[3], command_str);
                display_changed = TRUE;
                if (!timer_active) {
                    time_start_point = current_time;
                    timer_active = TRUE;
                }
                display_action = 0;
            }

            if (wheel_state == IDLE) {
                wheel_state = Initiate_Forward;
                right_wheel_speed = VERY_SLOW;
                left_wheel_speed = VERY_SLOW;
                time_counter = current_time; // reset timer when movement starts
            }

            if (current_time > time_counter + time_period) { // each unit is 200ms
                wheel_state = Initiate_Stop;
                movement_in_progress = 0;
                process_command = 0;
            }
        }
        else if ((IOT_process_buffer[command_row][15] == 'B')){
            if (display_action){
                strcpy(display_line[0], "          ");
                strcpy(display_line[1], first_ip_buffer);
                strcpy(display_line[2], second_ip_buffer);
                strcpy(display_line[3], command_str);
                display_changed = TRUE;
                if (!timer_active) {
                    time_start_point = current_time;
                    timer_active = TRUE;
                }
                display_action = 0;
            }

            if (wheel_state == IDLE) {
                wheel_state = Initiate_Reverse;
                right_wheel_speed = VERY_SLOW;
                left_wheel_speed = VERY_SLOW;
                time_counter = current_time; // reset timer when movement starts
            }

            if (current_time > time_counter + time_period) { // each unit is 200ms
                wheel_state = Initiate_Stop;
                movement_in_progress = 0;
                process_command = 0;
            }
        }
        else if ((IOT_process_buffer[command_row][15] == 'R')){
            if (display_action){
                strcpy(display_line[0], "          ");
                strcpy(display_line[1], first_ip_buffer);
                strcpy(display_line[2], second_ip_buffer);
                strcpy(display_line[3], command_str);
                display_changed = TRUE;
                if (!timer_active) {
                    time_start_point = current_time;
                    timer_active = TRUE;
                }
                display_action = 0;
            }

            if (wheel_state == IDLE) {
                wheel_state = Initiate_Right_Turn;
                right_wheel_speed = VERY_SLOW;
                left_wheel_speed = VERY_SLOW;
                time_counter = current_time; // reset timer when movement starts
            }

            if (current_time > time_counter + time_period) { // each unit is 200ms
                wheel_state = Initiate_Stop;
                movement_in_progress = 0;
                process_command = 0;
            }
        }
        else if ((IOT_process_buffer[command_row][15] == 'L')){
            if (display_action){
                strcpy(display_line[0], "          ");
                strcpy(display_line[1], first_ip_buffer);
                strcpy(display_line[2], second_ip_buffer);
                strcpy(display_line[3], command_str);
                display_changed = TRUE;
                if (!timer_active) {
                    time_start_point = current_time;
                    timer_active = TRUE;
                }
                display_action = 0;
            }

            if (wheel_state == IDLE) {
                wheel_state = Initiate_Left_Turn;
                right_wheel_speed = VERY_SLOW;
                left_wheel_speed = VERY_SLOW;
                time_counter = current_time; // reset timer when movement starts
            }

            if (current_time > time_counter + time_period) { // each unit is 200ms
                wheel_state = Initiate_Stop;
                movement_in_progress = 0;
                process_command = 0;
            }
        }
        else if (IOT_process_buffer[command_row][15] == 'A'){
            if (display_action){
                strcpy(display_line[0], "Arrived 0X");
                display_line[0][9] = '0' + time_period;
                strcpy(display_line[1], first_ip_buffer);
                strcpy(display_line[2], second_ip_buffer);
                strcpy(display_line[3], command_str);
                display_changed = TRUE;
                display_action = 0;
            }
            movement_in_progress = 0;
            process_command = 0;
        }
        else if (IOT_process_buffer[command_row][15] == 'X'){
            if (display_action){
                strcpy(display_line[0], "          ");
                strcpy(display_line[1], first_ip_buffer);
                strcpy(display_line[2], second_ip_buffer);
                strcpy(display_line[3], command_str);
                display_changed = TRUE;
                if (!timer_active) {
                    time_start_point = current_time;
                    timer_active = TRUE;
                }
                Control_Emitter(EMITTER_ON);
                line_counter = current_time;
                project_state = WAIT_TO_START;
                display_action = 0;
            }
            movement_in_progress = 0;
            process_command = 0;
        }
        else if (IOT_process_buffer[command_row][15] == 'E'){
            if (display_action){
                strcpy(display_line[0], "          ");
                strcpy(display_line[1], first_ip_buffer);
                strcpy(display_line[2], second_ip_buffer);
                strcpy(display_line[3], command_str);
                display_changed = TRUE;
                Control_Emitter(EMITTER_OFF);
                line_counter = current_time;
                project_state = EXIT_INITIALIZE;
                display_action = 0;
            }
            movement_in_progress = 0;
            process_command = 0;
        }
    }
}

unsigned int pc_tx_rd = 0;

// Function to set baud rate and send response
void Process_PC_Command(void) {

    // Check for valid command format (should start with ^ and have another character)
    if (command_received) {
        // Process based on second character
        switch(PC_process_buffer[display_row][1]) {
            case '^': // ^^ Command - "I'm here"
                strcpy(PC_transmit_array, "I'm here\n");
                break;

            case 'F': // ^F Command - Set baud rate to 115200
                strcpy(PC_transmit_array, "115200\n");
                break;

            case 'S': // ^S Command - Set baud rate to 9600
                strcpy(PC_transmit_array, "9600\n");
                break;

            default:
                // Unknown command
                strcpy(PC_transmit_array, "Unknown\n");
                break;
        }

        transmitting = TRUE;
        UCA1IE |= UCTXIE; // Trigger transmit interrupt
        // Clear the command flag after processing to prevent reprocessing
        command_received = FALSE;
    }
}


