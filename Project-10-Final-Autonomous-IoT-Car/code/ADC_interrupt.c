/*
 * ADC_interrupt.c
 *
 *  Created on: Mar 1, 2025
 *      Author: akila
 */


#include "include\macros.h"  // Has every header file and global variables


#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void){
    switch(__even_in_range(ADCIV,ADCIV_ADCIFG)){
        case ADCIV_NONE:
            break;
        case ADCIV_ADCOVIFG: // When a conversion result is written to the ADCMEM0
            // before its previous conversion result was read.
            break;
        case ADCIV_ADCTOVIFG: // ADC conversion-time overflow
            break;
        case ADCIV_ADCHIIFG: // Window comparator interrupt flags
            break;
        case ADCIV_ADCLOIFG: // Window comparator interrupt flag
            break;
        case ADCIV_ADCINIFG: // Window comparator interrupt flag
            break;
        case ADCIV_ADCIFG: // ADCMEM0 memory register with the conversion result
            ADCCTL0 &= ~ADCENC; // Disable ENC bit.
            switch (ADC_Channel++){
                case 0x00: // Channel A2 Interrupt (Left Detector)
                    ADC_Left_Det = ADCMEM0; // Move result into Global Values
                    ADC_Left_Det = ADC_Left_Det >> 2;
                    ADCMCTL0 &= ~ADCINCH_2; // Disable Last channel A2
                    ADCMCTL0 |= ADCINCH_3; // Enable Next channel A3
                    break;
                case 0x01: // Channel A3 Interrupt (Right Detector)
                    ADC_Right_Det = ADCMEM0; // Move result into Global Values
                    ADC_Right_Det = ADC_Right_Det >> 2;
                    ADCMCTL0 &= ~ADCINCH_3; // Disable Last channel A3
                    ADCMCTL0 |= ADCINCH_5; // Enable Next channel A5 (Thumbwheel)
                    break;
                case 0x02: // Channel A5 Interrupt (Thumbwheel)
                    ADC_Thumb = ADCMEM0; // Move result into Global Values
                    ADC_Thumb = ADC_Thumb >> 2;
                    ADCMCTL0 &= ~ADCINCH_5; // Disable Last channel A5
                    ADCMCTL0 |= ADCINCH_2; // Enable Next [First] channel A2
                    ADC_Channel = 0; // Reset channel counter
                    break;
                default:
                    break;
            }
            ADCCTL0 |= ADCENC; // Enable Conversions
            break;
        default:
            break;
    }
}
