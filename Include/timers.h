/*
 * timers.h
 *
 *  Created on: Feb 20, 2025
 *      Author: akila
 */

#ifndef INCLUDE_TIMERS_H_
#define INCLUDE_TIMERS_H_


// Main While loop switch cases
#define Time_Sequence_Rate (50) // 50 millisecods
#define S1250 (1250/Time_Sequence_Rate) // 1.25 seconds
#define S1000 (1000/Time_Sequence_Rate) // 1 second
#define S750 (750/Time_Sequence_Rate) // 0.75 seconds
#define S500 (500/Time_Sequence_Rate) // 0.50 seconds
#define S250 (250/Time_Sequence_Rate) // 0.25 seconds


#define MS200 1 // 200ms
#define MS400 2 // 200ms
#define SEC1_200MS 5  //1 second in 200ms
#define SEC2_200MS 10 //2 second in 200ms
#define SEC3_200MS 15  //1 second in 200ms
#define SEC4_200MS 20  //1 second in 200ms
#define SEC5_200MS 25 //5 second in 200ms
#define SEC7_200MS 35  //1 second in 200ms
#define SEC8_200MS 40  //1 second in 200ms
#define SEC9_200MS 47
#define SEC10_200MS 50
#define SEC20_200MS 100 //5 second in 200ms


#define TIMER_B0_CCR1_2_OV_VECTOR TIMER0_B1_VECTOR


#define ID_1 (0x0040) /* /2 */
#define ID_2 (0x0080) /* /4 */
#define ID_3 (0x00c0) /* /8 */
#define ID__2 (0x0040) /* /2 */
#define ID__4 (0x0080) /* /4 */
#define ID__8 (0x00c0) /* /8 */

#define TBIDEX_0 (0x0000) /* Divide by 1 */
#define TBIDEX_1 (0x0001) /* Divide by 2 */
#define TBIDEX_2 (0x0002) /* Divide by 3 */
#define TBIDEX_3 (0x0003) /* Divide by 4 */
#define TBIDEX_4 (0x0004) /* Divide by 5 */
#define TBIDEX_5 (0x0005) /* Divide by 6 */
#define TBIDEX_6 (0x0006) /* Divide by 7 */
#define TBIDEX_7 (0x0007) /* Divide by 8 */
#define TBIDEX__1 (0x0000) /* Divide by 1 */
#define TBIDEX__2 (0x0001) /* Divide by 2 */
#define TBIDEX__3 (0x0002) /* Divide by 3 */
#define TBIDEX__4 (0x0003) /* Divide by 4 */
#define TBIDEX__5 (0x0004) /* Divide by 5 */
#define TBIDEX__6 (0x0005) /* Divide by 6 */
#define TBIDEX__7 (0x0006) /* Divide by 7 */
#define TBIDEX__8 (0x0007) /* Divide by 8 */


#define SMCLK_FREQUENCY     8000000  // 8 MHz system clock
#define TIMER_DIVIDER       64         // ID__8 (÷8) and TBIDEX__8 (÷8)  Total ÷64
#define TB0CCR0_INTERVAL    25000  // 200ms = 25,000
#define TB0CCR1_INTERVAL    25000  //200ms
#define TB0CCR2_INTERVAL    25000  //200ms
#define DEBOUNCE_INTERVAL    25000  //200ms


#define SAMPLE_INTERVAL 2500    //10ms interrupt for B1 Timer


volatile unsigned int switch_pressed1;
volatile unsigned int debounce_active1;
volatile unsigned int debounce_count1;


volatile unsigned int switch_pressed2;
volatile unsigned int debounce_active2;
volatile unsigned int debounce_count2;





#endif /* INCLUDE_TIMERS_H_ */
