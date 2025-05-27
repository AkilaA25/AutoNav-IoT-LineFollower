/*
 * IOT.h
 *
 *  Created on: Apr 8, 2025
 *      Author: akila
 */

#ifndef INCLUDE_IOT_H_
#define INCLUDE_IOT_H_




// Global variables for serial communication control
char PC_process_buffer[4][32];
char PC_transmit_array[32];
unsigned int pc_pb_row_index;
unsigned int pc_pb_col_index;
extern unsigned int pc_tx_rd;

char IOT_process_buffer[4][55];
char IOT_transmit_array[32];
unsigned int iot_pb_row_index;
unsigned int iot_pb_col_index;
unsigned int iot_tx_rd;

unsigned int IOT_line;
//ring
char PC_Char_Rx[32];
unsigned int pc_rx_ring_wr;
unsigned int pc_rx_ring_rd;

char IOT_Char_Rx[32];
unsigned int iot_rx_ring_wr;
unsigned int iot_rx_ring_rd;


char ssid_val[32];
char ip_val[32];

unsigned int debug_val;

unsigned int command_confirm;
unsigned int start_ssid_cpy;
unsigned int start_ip_cpy;
unsigned int ssid_row;
unsigned int ip_row;
unsigned int ssid_found;
unsigned int ip_found;
unsigned int mux_found;
unsigned int ip_show;
unsigned int ssid_show;

unsigned int process_command;
unsigned int display_direction;
unsigned int movement_in_progress;

unsigned int command_row;

unsigned int password_approved;
unsigned int command_start;

unsigned int ready;

unsigned int enable;
unsigned int ssid_start;
unsigned int ip_start;
unsigned int network_start;
unsigned int mux_start;

unsigned int time_period;


void PC_Process(void);
void IOT_Process(void);
void Init_IOT(void);



#endif /* INCLUDE_IOT_H_ */
