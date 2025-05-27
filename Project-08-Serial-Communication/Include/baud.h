/*
 * baud.h
 *
 *  Created on: Mar 27, 2025
 *      Author: akila
 */

#ifndef INCLUDE_BAUD_H_
#define INCLUDE_BAUD_H_

#define BEGINNING (0);
#define COLUMN (32);
#define ROW (4);


extern char ncsu_msg[10];


unsigned long currentBaudRate;  // Default initial baud rate

char ProcessBuffer[4][32];
char TransmitArray[32];
unsigned int pb_row_index;
unsigned int pb_column_index;
char T_Array[32];
unsigned int T_index;
char USB_Char_Rx[16];
char usb_rx_ring_wr;
char usb_rx_ring_rd;


void setBaudRate(unsigned long baud);

void Init_Serial_UCA0(long speed);

#endif /* INCLUDE_BAUD_H_ */
