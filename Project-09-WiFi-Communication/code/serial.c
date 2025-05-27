/*
 * serial.c
 *
 *  Created on: Mar 27, 2025
 *      Author: akila
 */

#include  "include\macros.h"  //has every header file and global variables

// Global variables
volatile unsigned int command_mode = FALSE; // TRUE when in command mode
volatile unsigned int command_received = FALSE;
volatile unsigned int transmitting = FALSE;

////------------------------------------------------------------------------------
#pragma vector=EUSCI_A1_VECTOR
__interrupt void eUSCI_A1_ISR(void){
    char temp;

    switch(__even_in_range(UCA1IV,0x08)){
     case 0: break; // Vector 0 - no interrupt
     case 2: // Vector 2 - RXIFG

         temp = UCA1RXBUF; // Get the received character

         // Check for command prefix
         if (temp == '^') {
             command_mode = TRUE;
         }
         // If in command mode, collect characters until CR
         if (command_mode) {
             // Store in USB receive buffer for  purposes
             PC_Char_Rx[pc_rx_ring_wr] = temp;
             pc_rx_ring_wr++;
             if (pc_rx_ring_wr >= sizeof(PC_Char_Rx)) {
                 pc_rx_ring_wr = BEGINNING;
             }

             // If CR received or buffer full, process command
             if (temp == '\r') {
                 command_mode = FALSE;  // Reset command mode
             }
         }
         else {
             UCA0TXBUF = temp;
         }
         break;

     case 4: // Vector 4 - TXIFG

         UCA1TXBUF = PC_transmit_array[pc_tx_rd];
         if(PC_transmit_array[pc_tx_rd] == '\n'){
             pc_tx_rd = 0x00;
             transmitting = FALSE;
             UCA1IE &= ~UCTXIE;// stop interrupt
         }
         else pc_tx_rd++;

     break;
     default: break;
     }
}
////------------------------------------------------------------------------------
void Init_Serial_UCA1(void){

    pc_rx_ring_wr = BEGINNING;
    pc_rx_ring_rd = BEGINNING;

    // Configure UART 1
    UCA1CTLW0 = 0; // Use word register
    UCA1CTLW0 |= UCSWRST; // Set Software reset enable
    UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
    UCA1CTLW0 &= ~UCMSB; // MSB, LSB select
    UCA1CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit)
    UCA1CTLW0 &= ~UCPEN; // No Parity
    UCA1CTLW0 &= ~UCSYNC; // Asynchronous mode
    UCA1CTLW0 &= ~UC7BIT; // 8-bit data
    UCA0CTLW0 |= UCMODE_0;

    UCA1BRW = 4; // 115,200 Baud
    // UCA1MCTLW = UCSx concatenate UCFx concatenate UCOS16;
    // UCA1MCTLW = 0x49 concatenate 1 concatenate 1;
    UCA1MCTLW = 0x5551 ;
    UCA1CTLW0 &= ~ UCSWRST; // Set Software reset enable
    UCA1TXBUF = 0x00; // Prime the Pump
    UCA1IE |= UCRXIE; // Enable RX interrupt
}
//------------------------------------------------------------------------------

#pragma vector=EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){
    char iot_val;
    switch(__even_in_range(UCA0IV,0x08)){
     case 0: break; // Vector 0 - no interrupt
     case 2: // Vector 2 - RXIFG
         iot_val = UCA0RXBUF;

         IOT_Char_Rx[iot_rx_ring_wr++] = iot_val;
         if(iot_rx_ring_wr >= sizeof(IOT_Char_Rx)){
             iot_rx_ring_wr = BEGINNING;
         }

         UCA1TXBUF = iot_val;
     break;

     case 4: // Vector 4 - TXIFG
         UCA0TXBUF = IOT_transmit_array[iot_tx_rd];
         if(IOT_transmit_array[iot_tx_rd] == '\n'){
             iot_tx_rd = 0;
             unsigned int i;
             for (i = 0; i < sizeof(IOT_transmit_array); i++){
                 IOT_transmit_array[i] = 0x00;
             }
             UCA0IE &= ~UCTXIE;
         }
         else{
             iot_tx_rd++;
         }
     break;
     default: break;
    }
}
void Init_Serial_UCA0(void){
//------------------------------------------------------------------------------
// TX error (%) RX error (%)
// BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
// 8000000 4800 1 104 2 0xD6 -0.08 0.04 -0.10 0.14
// 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
// 8000000 19200 1 26 0 0xB6 -0.08 0.16 -0.28 0.20
// 8000000 57600 1 8 10 0xF7 -0.32 0.32 -1.00 0.36
// 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
// 8000000 .,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,, 0 17 0 0x4A -2.72 2.56 -3.76 7.28
//------------------------------------------------------------------------------
// Configure eUSCI_A0 for UART mode
 UCA0CTLW0 = 0;
 UCA0CTLW0 |= UCSWRST ; // Put eUSCI in reset
 UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
 UCA0CTLW0 &= ~UCMSB; // MSB, LSB select
 UCA0CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
 UCA0CTLW0 &= ~UCPEN; // No Parity
 UCA0CTLW0 &= ~UCSYNC;
 UCA0CTLW0 &= ~UC7BIT;
 UCA0CTLW0 |= UCMODE_0;
// BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
// 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
// UCA?MCTLW = UCSx + UCFx + UCOS16

 UCA0BRW = 4; // 115,200 baud
 UCA0MCTLW = 0x5551;
 UCA0CTLW0 &= ~UCSWRST; // release from reset
 UCA0TXBUF = 0x00; // Prime the Pump
 UCA0IE |= UCRXIE; // Enable RX interrupt
//------------------------------------------------------------------------------
}



// 9,600 Baud Rate
// 1. Calculate N = fBRCLK / Baudrate
// N = SMCLK / 9,600 => 8,000,000 / 9,600 = 833.3333333
// if N > 16 continue with step 3, otherwise with step 2
// 2. OS16 = 0, UCBRx = INT(N)
// continue with step 4
// 3. OS16 = 1,
// UCx = INT(N/16),
// = INT(N/16) = 833.333/16 => 52
// UCFx = INT([(N/16) – INT(N/16)] × 16)
//= ([833.333/16-INT(833.333/16)]*16)
//= (52.08333333-52)*16
//= 0.083*16 = 1
// 4. UCSx is found by looking up the fractional part of N (= N-INT(N)) in table Table 18-4
// Decimal of SMCLK / 8,000,000 / 9,600 = 833.3333333 => 0.333 yields 0x49 [Table]
// 5. If OS16 = 0 was chosen, a detailed error calculation is recommended to be performed
// TX error (%) RX error (%)
// BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
// 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
