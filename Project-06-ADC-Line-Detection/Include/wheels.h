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
#define Configure_Wheel_Speeds (1)
#define Forward_Move_Start (2)
#define Forward_Adjust (3)
#define Turn_Start (4)
#define Turn_Adjust (5)
#define Reverse_Move_Start (6)
#define Reverse_Adjust (7)
#define Initiate_Stop (8)
#define Stop (9)


extern volatile unsigned char wheel_state;
extern volatile unsigned int right_wheel_speed;
extern volatile unsigned int left_wheel_speed;
extern volatile unsigned char right_forward;
extern volatile unsigned char left_forward;

// ADC variables
extern volatile unsigned int ADC_Left_Det;
extern volatile unsigned int ADC_Right_Det;
extern volatile unsigned int ADC_Thumb;



// Function prototypes
void Wheels_Process(void);
void check_motor_conflict(void);
void Init_ADC(void);
void Control_Emitter(unsigned char emitter_state);
void Update_ADC_Values(void);
void int2hex(unsigned int value, char* string);




#endif /* INCLUDE_WHEELS_H_ */
