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

// Main While loop switch cases
#define Time_Sequence_Rate (50) // 50 millisecods
#define S1250 (1250/Time_Sequence_Rate) // 1.25 seconds
#define S1000 (1000/Time_Sequence_Rate) // 1 second
#define S750 (750/Time_Sequence_Rate) // 0.75 seconds
#define S500 (500/Time_Sequence_Rate) // 0.50 seconds
#define S250 (250/Time_Sequence_Rate) // 0.25 seconds


// Function Prototypes
//void Carlson_StateMachine(void);
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

//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS) {                      // Can the Operating system run

//    Carlson_StateMachine();            // Run a Time Based State Machine
    Switches_Process();                // Check for switch state change
    Display_Process();                 // Update Display
    P3OUT ^= TEST_PROBE;                // Change State of TEST_PROBE OFF
    check_motor_conflict();             //checks for explosions


    switch (action) {
        case 1:
            if (current_time > (time_counter + SEC1_200MS)) {
                strcpy(display_line[0], "  FORWARD ");
                strcpy(display_line[1], "          ");
                strcpy(display_line[2], "          ");
                strcpy(display_line[3], "          ");
                P6OUT |= R_FORWARD;
                P6OUT |= L_FORWARD;
                display_changed = 1;
            }
            if (current_time > (time_counter + (2*SEC1_200MS))) {
                strcpy(display_line[0], "   PAUSE  ");
                P6OUT &= ~R_FORWARD;
                P6OUT &= ~L_FORWARD;
                P6OUT &= ~R_REVERSE;
                P6OUT &= ~L_REVERSE;
                display_changed = 1;
                action++;
                time_counter = current_time;
            }

            break;
        case 2:
            if (current_time > (time_counter + SEC1_200MS)) {
                strcpy(display_line[0], "  REVERSE ");
                P6OUT |= R_REVERSE;
                P6OUT |= L_REVERSE;
                display_changed = 1;
            }
            if (current_time > (time_counter + (3*SEC1_200MS))) {
                strcpy(display_line[0], "   PAUSE  ");
                P6OUT &= ~R_FORWARD;
                P6OUT &= ~L_FORWARD;
                P6OUT &= ~R_REVERSE;
                P6OUT &= ~L_REVERSE;
                display_changed = 1;
                action++;
                time_counter = current_time;
            }

            break;
        case 3:
            if (current_time > (time_counter + SEC1_200MS)) {
                strcpy(display_line[0], "  FORWARD ");
                P6OUT |= R_FORWARD;
                P6OUT |= L_FORWARD;
                display_changed = 1;
            }
            if (current_time > (time_counter + (2*SEC1_200MS))) {
                strcpy(display_line[0], "   PAUSE  ");
                P6OUT &= ~R_FORWARD;
                P6OUT &= ~L_FORWARD;
                P6OUT &= ~R_REVERSE;
                P6OUT &= ~L_REVERSE;
                display_changed = 1;
                action++;
                time_counter = current_time;
            }

            break;
        case 4:
            if (current_time > (time_counter + SEC1_200MS)) {
                strcpy(display_line[0], " Spin CW  ");
                P6OUT |= L_FORWARD;
                P6OUT |= R_REVERSE;
                display_changed = 1;
            }
            if (current_time > (time_counter + (4*SEC1_200MS))) {
                strcpy(display_line[0], "   PAUSE  ");
                P6OUT &= ~R_FORWARD;
                P6OUT &= ~L_FORWARD;
                P6OUT &= ~R_REVERSE;
                P6OUT &= ~L_REVERSE;
                display_changed = 1;
                action++;
                time_counter = current_time;
            }
            break;
        case 5:
            if (current_time > (time_counter + (2*SEC1_200MS))) {
                strcpy(display_line[0], " Spin CCW ");
                P6OUT |= R_FORWARD;
                P6OUT |= L_REVERSE;
                display_changed = 1;
            }
            if (current_time > (time_counter + (6*SEC1_200MS))) {
                strcpy(display_line[0], "   PAUSE  ");
                P6OUT &= ~R_FORWARD;
                P6OUT &= ~L_FORWARD;
                P6OUT &= ~R_REVERSE;
                P6OUT &= ~L_REVERSE;
                display_changed = 1;
                action++;
                time_counter = current_time;
            }

            break;
        default:
            P6OUT &= ~R_FORWARD;
            P6OUT &= ~L_FORWARD;
            P6OUT &= ~R_REVERSE;
            P6OUT &= ~L_REVERSE;
            break;
    }








/*

    switch(event){
     case STRAIGHT: // Straight
         Run_Straight();
         break; //
     case CIRCLE: // Straight
         Run_Circle();
         break; //
     case FIGURE8: // Straight
         Run_Figure8();
         break; //
     case TRIANGLE: // Straight
         Run_Triangle();
         break; //
     default: break;
     }

     */


  }
//------------------------------------------------------------------------------

}



void Carlson_StateMachine(void){

    one_time = 1;

    if(Time_Sequence++ > 250){
     Time_Sequence = 0;
     }

    switch(Time_Sequence){
      case 250:                        //
        if(one_time){
          Init_LEDs();
          lcd_BIG_mid();
          display_changed = 1;
          one_time = 0;
        }
        Time_Sequence = 0;             //
        break;
      case 200:                        //
        if(one_time){
          P1OUT &= ~RED_LED;            // Change State of LED 4
          P6OUT |= GRN_LED;            // Change State of LED 5
          one_time = 0;
        }
        break;
      case 150:                         //
        if(one_time){
          P1OUT |= RED_LED;            // Change State of LED 4
          P6OUT &= ~GRN_LED;            // Change State of LED 5
          one_time = 0;
        }
        break;
      case 100:                         //
        if(one_time){
          lcd_4line();
          lcd_BIG_bot();
          P6OUT |= GRN_LED;            // Change State of LED 5
          display_changed = 1;
          one_time = 0;
        }
        break;
      case  50:                        //
        if(one_time){
          one_time = 0;
        }
        break;                         //
      default: break;
    }
}
