/*
 * wheels.h
 *
 *  Created on: Feb 28, 2025
 *      Author: akila
 */

#ifndef INCLUDE_WHEELS_H_
#define INCLUDE_WHEELS_H_


// Wheel State Machine States
#define IDLE (0)
#define Initiate_Forward (1)
#define Move_Forward (2)
#define Initiate_Reverse (3)
#define Move_Reverse (4)
#define Initiate_Right_Turn (5)
#define Turn_Right (6)
#define Initiate_Left_Turn (7)
#define Turn_Left (8)
#define Follow_Line (9)
#define Initiate_Stop (10)



extern volatile unsigned char wheel_state;
extern volatile unsigned int right_wheel_speed;
extern volatile unsigned int left_wheel_speed;
extern volatile unsigned char right_forward;
extern volatile unsigned char left_forward;


// Current wheel speed variables for acceleration
volatile unsigned int current_right_wheel_speed;
volatile unsigned int current_left_wheel_speed;


// ADC variables
extern volatile unsigned int ADC_Left_Det;
extern volatile unsigned int ADC_Right_Det;
extern volatile unsigned int ADC_Thumb;



// Function prototypes
void Wheels_Process(void);
void check_motor_conflict(void);
void match_speed_forward(void);
void match_speed_reverse(void);
void match_speed_turn_right(void);
void match_speed_turn_left(void);
void int2hex(unsigned int value, char* string);




#endif /* INCLUDE_WHEELS_H_ */
