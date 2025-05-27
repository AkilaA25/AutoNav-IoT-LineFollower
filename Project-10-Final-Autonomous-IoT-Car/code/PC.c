/*
 * PC.c
 *
 *  Created on: Apr 8, 2025
 *      Author: akila
 */

#include  "include\macros.h"  //has every header file and global variables

void PC_Process(void){
    if (pc_rx_ring_rd != pc_rx_ring_wr) {

        PC_process_buffer[pc_pb_row_index][pc_pb_col_index] = PC_Char_Rx[pc_rx_ring_rd];

        if (PC_Char_Rx[pc_rx_ring_rd] == '\r') {
            display_row = pc_pb_row_index;
            pc_pb_row_index++;
            if (pc_pb_row_index >= 4){
                pc_pb_row_index = 0;
            }
            pc_pb_col_index = 0;

            // Clear the following row
            unsigned int i;
            for (i = 0; i < 32; i++) {
                PC_process_buffer[pc_pb_row_index][i] = 0x00;
            }

            command_received = 1;

        }
        else {
            pc_pb_col_index++;
        }

        pc_rx_ring_rd++;
        if (pc_rx_ring_rd >= (sizeof(PC_Char_Rx))) pc_rx_ring_rd = BEGINNING;
    }
}
