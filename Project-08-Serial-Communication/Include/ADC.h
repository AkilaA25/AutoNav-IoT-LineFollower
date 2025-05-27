/*
 * ADC.h
 *
 *  Created on: Feb 28, 2025
 *      Author: akila
 */

#ifndef INCLUDE_ADC_H_
#define INCLUDE_ADC_H_

#define EMITTER_ON      1
#define EMITTER_OFF     0

// Global variables for ADC channels
volatile unsigned int ADC_Channel;   // Tracks current ADC channel
volatile unsigned int ADC_Left_Det;  // Left detector value
volatile unsigned int ADC_Right_Det; // Right detector value
volatile unsigned int ADC_Thumb;     // Thumbwheel value
volatile char adc_char[4];               // Array for HEX to BCD conversion

void HEXtoBCD(int hex_value);
void adc_line(char line, char location);
void Init_ADC(void);
void Control_Emitter(unsigned char emitter_state);
void Update_ADC_Values(void);


#endif /* INCLUDE_ADC_H_ */
