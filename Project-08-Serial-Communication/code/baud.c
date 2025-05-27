/*
 * baud.c
 *
 *  Created on: Mar 27, 2025
 *      Author: akila
 */


#include  "include\macros.h"  //has every header file and global variables



void setBaudRate(unsigned long baud) {
    if (currentBaudRate == baud) return;

        currentBaudRate = baud;

        // Put both UART ports in reset mode
        UCA0CTLW0 |= UCSWRST;
        UCA1CTLW0 |= UCSWRST;

    if (baud == 115200) {
        UCA0BRW = 4;        // 115200 baud
        UCA1BRW = 4;
        UCA0MCTLW = 0x5551;
        UCA1MCTLW = 0x5551;

    } else if (baud == 460800) {
        UCA0BRW = 17;        // 460800 baud
        UCA1BRW = 17;
        UCA0MCTLW = 0x4A00;
        UCA1MCTLW = 0x4A00;
    }

    UCA0CTLW0 &= ~UCSWRST;   // Release from reset
    UCA0IE |= UCRXIE;        // Enable RX interrupt
}


