/*
 * PWM.h
 *
 *  Created on: Feb 27, 2025
 *      Author: akila
 */

#ifndef INCLUDE_PWM_H_
#define INCLUDE_PWM_H_

#define PWM_PERIOD (TB3CCR0)
#define LCD_BACKLITE_DIMING (TB3CCR1)
#define RIGHT_FORWARD_SPEED (TB3CCR2)
#define RIGHT_REVERSE_SPEED (TB3CCR3)
#define LEFT_FORWARD_SPEED (TB3CCR4)
#define LEFT_REVERSE_SPEED (TB3CCR5)

#define WHEEL_OFF (0)
#define SLOW (35000)
#define SLOW15 (15000)
#define SLOW14 (14000)
#define SLOW13 (13000)
#define SLOW11 (10500)
#define SLOW10 (10000)
#define SLOW12 (12000)
#define SLOW20 (20000)
#define VERY_SLOW (15000)
#define SLOW10 (10000)
#define SLOW08 (8000)
#define FAST (50000)
#define PERCENT_100 (50000)
#define PERCENT_80 (40000)

#define NAVIGATE_RIGHT_SLOW (20000)
#define NAVIGATE_LEFT_SLOW (20000)


#endif /* INCLUDE_PWM_H_ */
