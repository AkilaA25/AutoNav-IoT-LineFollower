//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//  Built with Code Composer Version: CCS12.4.0.00007_win64
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "include\macros.h"  //has every header file and global variables


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
    time_counter = current_time;
    while (current_time < time_counter + 5){
        continue;
    }
    Init_LCD();                          // Initialize LCD
    Init_ADC();
    Init_DAC();

    // Initialize serial port at 115,200 baud as per homework requirements
    Init_Serial_UCA0();
    Init_Serial_UCA1();

    //P2OUT &= ~RESET_LCD;
    // Place the contents of what you want on the display, in between the quotes
    // Limited to 10 characters per line
    strcpy(display_line[0], "          ");
    strcpy(display_line[1], "  (o) (o) ");
    strcpy(display_line[2], "          ");
    strcpy(display_line[3], "          ");
    display_changed = TRUE;
    //Display_Update(0,0,0,0);

    wheel_state = IDLE;
    project_state = IDLE_STATE;
    time_counter = current_time;
    timer_active = FALSE;
    enable = TRUE;
    timecheck = 1;
    //------------------------------------------------------------------------------
    // Beginning of the "While" Operating System
    //------------------------------------------------------------------------------
    while(ALWAYS) {                      // Can the Operating system run
        Switches_Process();                // Check for switch state change
        Display_Process();                 // Update Display
        Wheels_Process();
        check_motor_conflict();            // Checks for explosions
        Process_PC_Command();
        Process_IOT_Command();
        if (timer_active) Display_Timer();
        if (show_adc) Update_ADC_Values();
        PC_Process();
        IOT_Process();
        Init_IOT();
        Black_Line_Process();
    }
}
//------------------------------------------------------------------------------
