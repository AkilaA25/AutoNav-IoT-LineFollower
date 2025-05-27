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
    while (current_time < time_counter + 10){
        continue;
    }
    Init_LCD();                          // Initialize LCD
    Init_ADC();

    // Initialize serial port at 115,200 baud as per homework requirements
    Init_Serial_UCA0();
    Init_Serial_UCA1();

    //P2OUT &= ~RESET_LCD;
    // Place the contents of what you want on the display, in between the quotes
    // Limited to 10 characters per line
    strcpy(display_line[0], "          ");
    strcpy(display_line[1], " Loading  ");
    strcpy(display_line[2], "          ");
    strcpy(display_line[3], "          ");
    display_changed = TRUE;
    //Display_Update(0,0,0,0);

    wheel_state = IDLE;
    emitter_state = EMITTER_OFF;
    time_counter = current_time;
    enable = TRUE;
    //------------------------------------------------------------------------------
    // Beginning of the "While" Operating System
    //------------------------------------------------------------------------------
    while(ALWAYS) {                      // Can the Operating system run
        Switches_Process();                // Check for switch state change
        Display_Process();                 // Update Display
        Wheels_Process();
        P3OUT ^= TEST_PROBE;               // Change State of TEST_PROBE OFF
        check_motor_conflict();            // Checks for explosions
        Process_Command();
        PC_Process();
        IOT_Process();
        Init_IOT();

        if (enable && current_time > time_counter + 20){
            P3OUT |= IOT_EN_CPU;            //set iot en high after 200ms
            enable = 0;
            time_counter = current_time;
        }

        if (process_command){
            char period_str[5]; // 4 digits + null terminator
            memcpy(period_str, &IOT_process_buffer[command_row][16], 4);
            period_str[4] = '\0';
            time_period = atoi(period_str); // This will now contain the number of 200ms intervals
            if ((IOT_process_buffer[command_row][15] == 'F')){
                if (display_direction){
                    lcd_BIG_mid();
                    strcpy(display_line[0], "          ");
                    strcpy(display_line[1], " FORWARD  ");
                    strcpy(display_line[2], "          ");
                    display_changed = TRUE;
                    display_direction = 0;
                }

                if (wheel_state == IDLE) {
                    wheel_state = Initiate_Forward;
                    right_wheel_speed = VERY_SLOW;
                    left_wheel_speed = VERY_SLOW;
                    time_counter = current_time; // reset timer when movement starts
                    strcpy(display_line[0], "   START  ");
                    display_changed = TRUE;
                }

                if (current_time > time_counter + time_period) { // each unit is 200ms
                    wheel_state = Initiate_Stop;
                    strcpy(display_line[0], "   STOP   ");
                    movement_in_progress = 0;
                    display_changed = TRUE;
                    process_command = 0;
                }
            }
            else if ((IOT_process_buffer[command_row][15] == 'B')){
                if (display_direction){
                    lcd_BIG_mid();
                    strcpy(display_line[0], "          ");
                    strcpy(display_line[1], " BACKWARD ");
                    strcpy(display_line[2], "          ");
                    display_changed = TRUE;
                    display_direction = 0;
                }

                if (wheel_state == IDLE) {
                    wheel_state = Initiate_Reverse;
                    right_wheel_speed = VERY_SLOW;
                    left_wheel_speed = VERY_SLOW;
                    time_counter = current_time; // reset timer when movement starts
                    strcpy(display_line[0], "   START  ");
                    display_changed = TRUE;
                }

                if (current_time > time_counter + time_period) { // each unit is 200ms
                    wheel_state = Initiate_Stop;
                    strcpy(display_line[0], "   STOP   ");
                    movement_in_progress = 0;
                    display_changed = TRUE;
                    process_command = 0;
                }
            }
            else if ((IOT_process_buffer[command_row][15] == 'R')){
                if (display_direction){
                    lcd_BIG_mid();
                    strcpy(display_line[0], "          ");
                    strcpy(display_line[1], "  RIGHT   ");
                    strcpy(display_line[2], "          ");
                    display_changed = TRUE;
                    display_direction = 0;
                }

                if (wheel_state == IDLE) {
                    wheel_state = Initiate_Right_Turn;
                    right_wheel_speed = VERY_SLOW;
                    left_wheel_speed = VERY_SLOW;
                    time_counter = current_time; // reset timer when movement starts
                    strcpy(display_line[0], "   START  ");
                    display_changed = TRUE;
                }

                if (current_time > time_counter + time_period) { // each unit is 200ms
                    wheel_state = Initiate_Stop;
                    strcpy(display_line[0], "   STOP   ");
                    movement_in_progress = 0;
                    display_changed = TRUE;
                    process_command = 0;
                }
            }
            else if ((IOT_process_buffer[command_row][15] == 'L')){
                if (display_direction){
                    lcd_BIG_mid();
                    strcpy(display_line[0], "          ");
                    strcpy(display_line[1], "   LEFT   ");
                    strcpy(display_line[2], "          ");
                    display_changed = TRUE;
                    display_direction = 0;
                }

                if (wheel_state == IDLE) {
                    wheel_state = Initiate_Left_Turn;
                    right_wheel_speed = VERY_SLOW;
                    left_wheel_speed = VERY_SLOW;
                    time_counter = current_time; // reset timer when movement starts
                    strcpy(display_line[0], "   START  ");
                    display_changed = TRUE;
                }

                if (current_time > time_counter + time_period) { // each unit is 200ms
                    wheel_state = Initiate_Stop;
                    strcpy(display_line[0], "   STOP   ");
                    movement_in_progress = 0;
                    display_changed = TRUE;
                    process_command = 0;
                }
            }
        }

    }
}
//------------------------------------------------------------------------------
