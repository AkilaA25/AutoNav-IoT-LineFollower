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
#define SMALL_RING_SIZE (16);

// Command definitions
#define CMD_PREFIX        '^'
#define CMD_ACK           '^'
#define CMD_FAST          'F'
#define CMD_SLOW          'S'

extern char ncsu_msg[10];

unsigned long currentBaudRate;  // Default initial baud rate

//flags
extern volatile unsigned int command_received;
extern volatile unsigned int command_mode; // TRUE when in command mode
extern volatile unsigned int transmitting;

void setBaudRate(unsigned long baud);
void Process_PC_Command(void);
void Process_IOT_Command(void);

void Init_Serial_UCA0(void);
void Init_Serial_UCA1(void);

#endif /* INCLUDE_BAUD_H_ */
