/*
 * display_timer.h
 *
 *  Created on: Mar 5, 2025
 *      Author: akila
 */

#ifndef INCLUDE_DISPLAY_TIMER_H_
#define INCLUDE_DISPLAY_TIMER_H_

volatile unsigned char timer_active;
volatile unsigned int hundreds;
volatile unsigned int tens;
volatile unsigned int ones;
volatile unsigned int tenths;
volatile unsigned int timer;
volatile unsigned int total_seconds;

volatile unsigned int time_start_point;

void Update_Timer(void);
void Display_Timer(void);

#endif /* INCLUDE_DISPLAY_TIMER_H_ */
