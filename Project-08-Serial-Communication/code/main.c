//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//  Jim Carlson
//  Jan 2023
//  Built with Code Composer Version: CCS12.4.0.00007_win64
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "include\macros.h"  //has every header file and global variables

unsigned int delay = 1;
unsigned int display_row = 0;

// Function Prototypes
void main(void);

void main(void) {
    //    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    //------------------------------------------------------------------------------
    // Main Program
    // This is the main routine for the program. Execution of code starts here.
    // The operating system is Back Ground Fore Ground.
    //
    //------------------------------------------------------------------------------
    PM5CTL0 &= ~LOCKLPM5;
    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings

    Init_Ports();                        // Initialize Ports
    Init_Clocks();                       // Initialize Clock System
    Init_Conditions();                   // Initialize Variables and Initial Conditions
    Init_Timers();
    Init_LCD();                          // Initialize LCD
    Init_ADC();

    // Initialize serial port at 460,800 baud as per homework requirements
    Init_Serial_UCA0(460800);

    //P2OUT &= ~RESET_LCD;
    // Place the contents of what you want on the display, in between the quotes
    // Limited to 10 characters per line
    strcpy(display_line[0], " Loading  ");
    strcpy(display_line[1], "          ");
    strcpy(display_line[2], "          ");
    strcpy(display_line[3], "          ");
    display_changed = TRUE;
    //Display_Update(0,0,0,0);

    wheel_state = IDLE;
    timer_active = FALSE;
    emitter_state = EMITTER_OFF;

    time_counter = current_time;

    //------------------------------------------------------------------------------
    // Beginning of the "While" Operating System
    //------------------------------------------------------------------------------
    while(ALWAYS) {                      // Can the Operating system run
        Switches_Process();                // Check for switch state change
        Display_Process();                 // Update Display
        P3OUT ^= TEST_PROBE;               // Change State of TEST_PROBE OFF
        check_motor_conflict();            // Checks for explosions

        if (delay && (current_time > SEC5_200MS)) {
            strcpy(display_line[0], "          ");
            strcpy(display_line[1], "          ");
            strcpy(display_line[2], " BAUD RATE");
            strcpy(display_line[3], "          ");
            display_changed = TRUE;
            delay = 0;
        }

        if (usb_rx_ring_rd != usb_rx_ring_wr) {

            ProcessBuffer[pb_row_index][pb_column_index] = USB_Char_Rx[usb_rx_ring_rd];

            if (USB_Char_Rx[usb_rx_ring_rd] == '\n') {
                display_row = pb_row_index;
                pb_row_index++;
                if (pb_row_index >= 4){
                    pb_row_index = 0;
                }
                pb_column_index = 0;

                // Clear the following row
                unsigned int i;
                for (i = 0; i < 32; i++) {
                   ProcessBuffer[pb_row_index][i] = 0x00;
                }

                strncpy(display_line[3], ProcessBuffer[display_row], 10);
                strcpy(display_line[1], " RECIEVED ");
                strcpy(display_line[0], "          ");
                display_changed = TRUE;
            }
            else {
                pb_column_index++;
            }

            usb_rx_ring_rd++;
            if (usb_rx_ring_rd >= (sizeof(USB_Char_Rx))) usb_rx_ring_rd = BEGINNING;
        }
    }
}
//------------------------------------------------------------------------------
