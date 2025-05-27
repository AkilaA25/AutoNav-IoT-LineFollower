/*
 * timers.c
 *
 *  Created on: Feb 18, 2025
 *      Author: akila
 */


#include  "include\macros.h"  //has every header file and global variables

#define DEBOUNCE_LIMIT 20;

void Init_Timers(void){
    Init_Timer_B0();
    Init_Timer_B1();
    Init_Timer_B3();
}

void Init_Timer_B0(void) {
    TB0CTL = TBSSEL__SMCLK;       // Use SMCLK (8 MHz)
    TB0CTL |= TBCLR;              // Reset TB0R, clock divider, count direction
    TB0CTL |= MC__CONTINUOUS;     // Set Timer B0 to continuous mode
    TB0CTL |= ID__8;              // Divide SMCLK by 8
    TB0EX0 = TBIDEX__8;           // Further divide by 8

    TB0CCR0 = TB0CCR0_INTERVAL;
    TB0CCTL0 |= CCIE;             // Enable interrupt for CCR0

    TB0CCR1 = 0;
    TB0CCTL1 &= ~CCIE;             // Enable interrupt for CCR1

    TB0CCR2 = 0;
    TB0CCTL2 &= ~CCIE;             // Enable interrupt for CCR2

    TB0CTL &= ~TBIE;              // Disable Timer B overflow interrupt
    TB0CTL &= ~TBIFG;             // Clear Timer B overflow flag
}



// Timer B1 dedicated to black line detection
void Init_Timer_B1(void) {
    TB1CTL = TBSSEL__SMCLK;       // Use SMCLK (8 MHz)
    TB1CTL |= TBCLR;              // Reset TB1R, clock divider, count direction
    TB1CTL |= MC__CONTINUOUS;     // Set Timer B0 to continuous mode
    TB1CTL |= ID__8;              // Divide SMCLK by 8
    TB1EX0 = TBIDEX__4;           // Further divide by 4

    TB1CCR0 = SAMPLE_INTERVAL;
    TB1CCTL0 |= CCIE;             // Enable interrupt for CCR0

    TB1CCR1 = 0;
    TB1CCTL1 &= ~CCIE;             // Enable interrupt for CCR1

    TB1CCR2 = 0;
    TB1CCTL2 &= ~CCIE;             // Enable interrupt for CCR2


    TB1CTL &= ~TBIE;              // Disable Timer B overflow interrupt
    TB1CTL &= ~TBIFG;             // Clear Timer B overflow flag
}


void Init_Timer_B3(void) {
//------------------------------------------------------------------------------
// SMCLK source, up count mode, PWM Right Side
// TB3.1 P6.0 LCD_BACKLITE
// TB3.2 P6.1 R_FORWARD
// TB3.3 P6.2 R_REVERSE
// TB3.4 P6.3 L_FORWARD
// TB3.5 P6.4 L_REVERSE
//------------------------------------------------------------------------------
     TB3CTL = TBSSEL__SMCLK; // SMCLK
     TB3CTL |= MC__UP; // Up Mode
     TB3CTL |= TBCLR; // Clear TAR
     PWM_PERIOD = WHEEL_PERIOD; // PWM Period [Set this to 50005]

     TB3CCTL1 = OUTMOD_7; // CCR1 reset/set
     LCD_BACKLITE_DIMING = PERCENT_80; // P6.0 Right Forward PWM duty cycle

     TB3CCTL2 = OUTMOD_7; // CCR2 reset/set
     RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.1 Right Forward PWM duty cycle

     TB3CCTL3 = OUTMOD_7; // CCR3 reset/set
     LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.2 Left Forward PWM duty cycle

     TB3CCTL4 = OUTMOD_7; // CCR4 reset/set
     RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.3 Right Reverse PWM duty cycle

     TB3CCTL5 = OUTMOD_7; // CCR5 reset/set
     LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.4 Left Reverse PWM duty cycle
//------------------------------------------------------------------------------
}



