//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//  Jim Carlson
//  Jan 2023
//  Built with Code Composer Version: CCS12.4.0.00007_win64
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "include\macros.h"  //has every header file anf global variables


// Function Prototypes
void main(void);

//void main(void){
void main(void){
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
//P2OUT &= ~RESET_LCD;
  // Place the contents of what you want on the display, in between the quotes
// Limited to 10 characters per line
  strcpy(display_line[0], "   NCSU   ");
  strcpy(display_line[1], " WOLFPACK ");
  strcpy(display_line[2], "  ECE306  ");
  strcpy(display_line[3], "  GP I/O  ");
  display_changed = TRUE;
  //Display_Update(0,0,0,0);

  wheel_move = 0;
  forward = TRUE;

  wheel_state = IDLE;

//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS) {                      // Can the Operating system run

      Switches_Process();                // Check for switch state change

      if (emitter_state == EMITTER_ON) Update_ADC_Values(); // Update ADC values on LCD display
      else {
          strcpy(display_line[0], " EMITTER  ");
          strcpy(display_line[1], "    OFF   ");
          strcpy(display_line[2], "          ");
          strcpy(display_line[3], "          ");
          display_changed = TRUE;
      }

      Display_Process();                 // Update Display
      P3OUT ^= TEST_PROBE;               // Change State of TEST_PROBE OFF
      check_motor_conflict();            // Checks for explosions
      Black_Line_Process();
      Wheels_Process();

  }
//------------------------------------------------------------------------------

}
