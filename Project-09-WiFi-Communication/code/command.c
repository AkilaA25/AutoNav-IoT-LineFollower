/*
 * command.c
 *
 *  Created on: Apr 7, 2025
 *      Author: akila
 */


#include  "include\macros.h"  //has every header file and global variables

unsigned int pc_tx_rd = 0;

// Function to set baud rate and send response
void Process_Command(void) {

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

// Function to set baud rate and send response
void starting_commands(void) {
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


