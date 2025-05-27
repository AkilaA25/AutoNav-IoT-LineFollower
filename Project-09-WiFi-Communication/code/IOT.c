/*
 * IOT.c
 *
 *  Created on: Apr 8, 2025
 *      Author: akila
 */

#include  "include\macros.h"  //has every header file and global variables

char ssid_command[] = "AT+CWJAP?\r\n";
char ip_command[] = "AT+CIFSR\r\n";
char mux_command[] = "AT+CIPMUX=1\r\n";
char network_command[] = "AT+CIPSERVER=1,9147\r\n";


void IOT_Process(void){ // Process IOT messages
     unsigned int iot_rx_wr_temp;
     iot_rx_wr_temp = iot_rx_ring_wr;
     if(iot_rx_wr_temp != iot_rx_ring_rd){ // Determine if IOT is available
         IOT_process_buffer[iot_pb_row_index][iot_pb_col_index] = IOT_Char_Rx[iot_rx_ring_rd++];
         if(iot_rx_ring_rd >= sizeof(IOT_Char_Rx)){
             iot_rx_ring_rd = BEGINNING;
         }

         if(IOT_process_buffer[iot_pb_row_index][iot_pb_col_index] == '\n'){

             if (ssid_found){
                 unsigned int j;
                 unsigned int i=0;
                 for (j = 0; j < sizeof(IOT_process_buffer[ssid_row]); j++){
                     if (IOT_process_buffer[ssid_row][j] == '\"'){
                        if (start_ssid_cpy) {
                            start_ssid_cpy = 0;
                            break;
                        }
                        else {
                            start_ssid_cpy = 1;
                            continue;
                        }
                     }
                     else if (start_ssid_cpy){
                         ssid_val[i] = IOT_process_buffer[ssid_row][j];
                         i++;
                     }
                 }
                 ssid_found = 0;
                 ssid_show = 1;
                 mux_start = 1;
                 ssid_val[i] = '\0';
             }

             if (ip_found){
                 unsigned int j;
                 unsigned int i=0;
                 for (j = 0; j < sizeof(IOT_process_buffer[ip_row]); j++){
                     if (IOT_process_buffer[ip_row][j] == '\"'){
                        if (start_ip_cpy) {
                            start_ip_cpy = 0;
                            break;
                        }
                        else {
                            start_ip_cpy = 1;
                            continue;
                        }
                     }
                     else if (start_ip_cpy){
                         ip_val[i] = IOT_process_buffer[ip_row][j];
                         i++;
                     }
                 }
                 ip_found = 0;
                 ip_show = 1;
                 ssid_start = 1;
                 ip_val[i] = '\0';
             }

             if (mux_found){
                 network_start = 1;
                 mux_found = 0;
             }


             if (command_start){
                 if ((IOT_process_buffer[command_row][11] == '1')&&(IOT_process_buffer[command_row][12] == '1')&&(IOT_process_buffer[command_row][13] == '1')&&(IOT_process_buffer[command_row][14] == '1')){
                     password_approved = 1;
                 }
                 command_start = 0;
                 process_command = 1;
                 display_direction = 1;
             }

             iot_pb_col_index = 0;
             IOT_line = iot_pb_row_index;
             iot_pb_row_index++;
             if(iot_pb_row_index >= 4){
                 iot_pb_row_index = 0;
             }
         }else{

             switch(iot_pb_col_index){
                 case 0:
                     if(IOT_process_buffer[iot_pb_row_index][iot_pb_col_index] == '+'){ // Got "+"
                         command_confirm = 1;
                     } else{
                         command_confirm = 0;
                     }
                     break;
                 case 1:
                     break;
                 case 4:
                     break;
                 case 5:
                     //+CWJAP:"your_ssid","ec:a9:40:dd:35:d0",1,-71,0,5,3,0,0
                     if(IOT_process_buffer[iot_pb_row_index][iot_pb_col_index] == 'P' && command_confirm){ // get SSID
                         ssid_found = 1;
                         ssid_row = iot_pb_row_index;
                     }
                     break;
                 case 7:
                     if(IOT_process_buffer[iot_pb_row_index][iot_pb_col_index] == 'T'){ // get SSID
                         ip_start = 1;
                     }
                     break;
                 case 8:
                     if(IOT_process_buffer[iot_pb_row_index][iot_pb_col_index] == 'X'){ // get SSID
                         mux_found = 1;
                     }
                     break;
                 case 10:
                     if(IOT_process_buffer[iot_pb_row_index][iot_pb_col_index] == '^' && command_confirm && (!movement_in_progress)){
                         command_start = 1;
                         movement_in_progress = 1;
                         command_row = iot_pb_row_index;
                     }
                     break;
                 case 11:
                     //+CIFSR:STAIP,"192.168.4.1"
                     if(IOT_process_buffer[iot_pb_row_index][iot_pb_col_index] == 'P' && command_confirm){
                         ip_row = iot_pb_row_index;
                         ip_found = 1;
                     }
                     break;

                 default: break;
             }
             iot_pb_col_index++;
         }
     }
}

void Init_IOT(void){

    if (ip_start){
        unsigned int i;
        for(i=0; i<sizeof(ip_command); i++){
            IOT_transmit_array[i] = ip_command[i];
        }
        time_counter = current_time;
        UCA0IE |= UCTXIE;
        ip_start = 0;
    }

    if (ssid_start){
        unsigned int i;
        for(i=0; i<sizeof(ssid_command); i++){
            IOT_transmit_array[i] = ssid_command[i];
        }
        time_counter = current_time;
        UCA0IE |= UCTXIE;
        ssid_start = 0;
    }

    if (mux_start){
        unsigned int i;
        for(i=0; i<sizeof(mux_command); i++){
            IOT_transmit_array[i] = mux_command[i];
        }
        time_counter = current_time;
        UCA0IE |= UCTXIE;
        mux_start = 0;
    }

    if (network_start){
        unsigned int i;
        for(i=0; i<sizeof(network_command); i++){
            IOT_transmit_array[i] = network_command[i];
        }
        time_counter = current_time;
        UCA0IE |= UCTXIE;
        network_start = 0;
    }

    if (ip_show) {
        // Set label on line 1.
        strcpy(display_line[1], "IP ADDRESS");

        // Find the index of the second dot in ip_val.
        unsigned int dot_count = 0;
        unsigned int pos_second_dot = 0;
        unsigned int i = 0;
        while (ip_val[i] != '\0') {
            if (ip_val[i] == '.') {
                dot_count++;
                if (dot_count == 2) {
                    pos_second_dot = i;
                    break;
                }
            }
            i++;
        }

        strncpy(display_line[2], ip_val, pos_second_dot);
        strcpy(display_line[3], ip_val + pos_second_dot + 1);
        display_changed = TRUE;
        ip_show = 0;
    }

    if(ssid_show){

        strncpy(display_line[0], ssid_val, 10);
        display_changed = TRUE;

        ssid_show = 0;
    }

}
