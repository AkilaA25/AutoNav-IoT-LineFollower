/*
 * interrupt_timer.c
 *
 *  Created on: Feb 20, 2025
 *      Author: akila
 */

#include  "include\macros.h"


#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void) {

    TB0CCR0 += TB0CCR0_INTERVAL;
    update_display = 1;
    current_time++;

}


#pragma vector = TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void){  // think timer bo ccr1 all vectors abd cc captures
 //---------------------------------------------------------------------------
// TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
 //---------------------------------------------------------------------------
    switch(__even_in_range(TB0IV,14)){
     case  0: break;
     // No interrupt
     case  2:
     // SW1
     if (debounce_active1){
         debounce_count1++;
         if (debounce_count1 > DEBOUNCE_TIME){ //set debounce time
             debounce_active1 = FALSE;
             P4IE |= SW1;
             TB0CCTL1 &= ~CCIE;
             TB0CCTL0 |= CCIE;
         }

     }
     break;

     case 4:// switch 2 vector
         if (debounce_active2){
             debounce_count2++;
             if (debounce_count2 > DEBOUNCE_TIME){
                 debounce_active2 = FALSE;
                 P2IE |= SW2;                        //re enable the ability to call interrupt again by reset
                 TB0CCTL2 &= ~CCIE;                  // set timer back to 0
                 TB0CCTL0 |= CCIE;
             }
         }
         break;

     case 14:
     // overflow
     break;
     default: break;
    }
}



#pragma vector = TIMER1_B0_VECTOR
__interrupt void Timer1_B0_ISR(void) {

    TB1CCR0 += BLACK_LINE_SAMPLE_INTERVAL;
    ADCCTL0 |= ADCSC; // Start next sample

}

#pragma vector = TIMER1_B1_VECTOR
__interrupt void TIMER1_B1_ISR(void){  // think timer bo ccr1 all vectors abd cc captures
 //---------------------------------------------------------------------------
// TimerB1 1-2, Overflow Interrupt Vector (TBIV) handler
 //---------------------------------------------------------------------------
    switch(__even_in_range(TB1IV,14)){
     case  0: break;
     // No interrupt
     case  2:
         break;

     case 4:// switch 2 vector
         break;

     case 14:
     // overflow
     break;
     default: break;
    }
}



