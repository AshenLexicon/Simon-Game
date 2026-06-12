#include "buzzer.h"
#include "initialisation.h"
#include "output.h"

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>


//  Initialise the pwm for the buzzer 
void pwm_init(void)
{

    // TCA0 WO0 output pin for buzzer
    PORTB.DIRSET = PIN0_bm;
    PORTB.OUTCLR = PIN0_bm;

    // Configure TCA0 for single-slope PWM on WO0
    TCA0.SINGLE.CTRLA = 0;
    TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_SINGLESLOPE_gc | TCA_SINGLE_CMP0EN_bm;

    // Start silent
    TCA0.SINGLE.PER = 0;
    TCA0.SINGLE.CMP0 = 0;// Start first note

    // Enable TCA0
    TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;

}

// This turns on the buzzer using the tone macros in buzzer.h to make sound throughout the gameplay in Simon 
void buzzer_on(uint16_t frequency)
{
    uint16_t period = (3333333UL / frequency) - 1; // 3333333UL is the clock speed 

    TCA0.SINGLE.PER = period;
    TCA0.SINGLE.CMP0 = (period + 1) / 2;
}

// This turns off the buzzer and is used throughout the gameplay in Simon 
void buzzer_off(void)
{
    TCA0.SINGLE.CMP0 = 0;
}
