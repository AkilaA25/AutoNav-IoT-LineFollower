/*
 * serial.c
 *
 *  Created on: Mar 27, 2025
 *      Author: akila
 */

#include  "include\macros.h"  //has every header file and global variables


char ncsu_msg[10] = "NCSU  #1\n";
////------------------------------------------------------------------------------
//#pragma vector=EUSCI_A0_VECTOR
//__interrupt void eUSCI_A0_ISR(void){
//    unsigned int temp;
//    switch(__even_in_range(UCA0IV,0x08)){
//        case 0: // Vector 0 - no interrupt
//            break;
//        case 2: // Vector 2 - RXIFG
//            temp = usb_rx_ring_wr++;
//            USB_Char_Rx[temp] = UCA0RXBUF; // RX -> USB_Char_Rx character
//
//            if (usb_rx_ring_wr >= (sizeof(USB_Char_Rx))){
//                usb_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
//            }
//            break;
//        case 4: // Vector 4 – TXIFG
//            break;
//        default: break;
//    }
//}
////------------------------------------------------------------------------------
//void Init_Serial_UCA0(void){
//    int i;
//
//    for(i=0; i<SMALL_RING_SIZE; i++){
//        USB_Char_Rx[i] = 0x00; // USB Rx Buffer
//
//    }
//    usb_rx_ring_wr = BEGINNING;
//    usb_rx_ring_rd = BEGINNING;
//    for(i=0; i<LARGE_RING_SIZE; i++){ // May not use this
//        USB_Char_Tx[i] = 0x00; // USB Tx Buffer
//
//    }
//    usb_tx_ring_wr = BEGINNING;
//    usb_tx_ring_rd = BEGINNING;
//// Configure UART 0
//    UCA0CTLW0 = 0; // Use word register
//    UCA0CTLW0 |= UCSWRST; // Set Software reset enable
//    UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
//    // 9,600 Baud Rate
//    // 1. Calculate N = fBRCLK / Baudrate
//    // N = SMCLK / 9,600 => 8,000,000 / 9,600 = 833.3333333
//    // if N > 16 continue with step 3, otherwise with step 2
//    // 2. OS16 = 0, UCBRx = INT(N)
//    // continue with step 4
//    // 3. OS16 = 1,
//    // UCx = INT(N/16),
//    // = INT(N/16) = 833.333/16 => 52
//    // UCFx = INT([(N/16) – INT(N/16)] × 16)
//    //= ([833.333/16-INT(833.333/16)]*16)
//    //= (52.08333333-52)*16
//    //= 0.083*16 = 1
//    // 4. UCSx is found by looking up the fractional part of N (= N-INT(N)) in table Table 18-4
//    // Decimal of SMCLK / 8,000,000 / 9,600 = 833.3333333 => 0.333 yields 0x49 [Table]
//    // 5. If OS16 = 0 was chosen, a detailed error calculation is recommended to be performed
//    // TX error (%) RX error (%)
//    // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
//    // 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
//    UCA0BRW = 52; // 9,600 Baud
//    // UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
//    // UCA0MCTLW = 0x49 concatenate 1 concatenate 1;
//    UCA0MCTLW = 0x4911 ;
//    UCA0CTLW0 &= ~ UCSWRST; // Set Software reset enable
//    UCA0IE |= UCRXIE; // Enable RX interrupt
//}
//------------------------------------------------------------------------------

#pragma vector=EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){
    unsigned int temp;
    switch(__even_in_range(UCA0IV,0x08)){
        case 0: // Vector 0 - no interrupt
            break;
        case 2: // Vector 2 - RXIFG
            temp = UCA0RXBUF;

            USB_Char_Rx[usb_rx_ring_wr] = temp; // RX -> USB_Char_Rx character
                usb_rx_ring_wr++;
                if (usb_rx_ring_wr >= (sizeof(USB_Char_Rx))){
                    usb_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
                }

            break;
        case 4: // Vector 4 – TXIFG

            UCA0TXBUF = TransmitArray[T_index];
            if (TransmitArray[T_index] == '\n') {
                T_index = BEGINNING;
                UCA0IE &= ~UCTXIE;
            }
            else{
                T_index++;
            }

            break;
        default: break;
    }
}
void Init_Serial_UCA0(long speed){
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


 UCA0BRW = 4 ; // 115,200 baud
 UCA0MCTLW = 0x5551 ;
 UCA0CTLW0 &= ~UCSWRST ; // release from reset
 //UCA0TXBUF = 0x00; // Prime the Pump
 UCA0IE |= UCRXIE; // Enable RX interrupt
//------------------------------------------------------------------------------
}
