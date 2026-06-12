#include "adc.h"

#include <avr/io.h>
#include <stdint.h>

void adc_init(void) // Referenced from Tutorial 9
{
    PORTA.PIN2CTRL = PORT_ISC_INPUT_DISABLE_gc;

    ADC0.CTRLB = ADC_PRESC_DIV2_gc;

    ADC0.CTRLC = (4 << ADC_TIMEBASE_gp) | ADC_REFSEL_VDD_gc;

    ADC0.CTRLE = 64;

    ADC0.CTRLF = ADC_FREERUN_bm | ADC_LEFTADJ_bm;

    ADC0.MUXPOS = ADC_MUXPOS_AIN2_gc;

    ADC0.CTRLA = ADC_ENABLE_bm;

    ADC0.COMMAND = ADC_MODE_SINGLE_8BIT_gc | ADC_START_IMMEDIATE_gc;


    // This waits for the first conversion to finish ensuring that no invalid ADC values are used for the first gameplay delay 
    while (!(ADC0.INTFLAGS & ADC_RESRDY_bm))
    {
        ;
    }

    ADC0.INTFLAGS = ADC_RESRDY_bm;

    // Wait for one more fresh conversion.
    while (!(ADC0.INTFLAGS & ADC_RESRDY_bm))
    {
        ;
    }
}

// This returns the 8-bit ADC result from the potentiometer 
uint8_t adc_results(void)
{
    return ADC0.RESULT0;
}

// This uses the adc_result and converts into a linear format from 250 to 2000ms ensuring it lies between the assigment equirment of 0.25 to 2s 
uint16_t get_adc_value(void)
{
    uint8_t adc_value = adc_results();

    return 250 + (((uint32_t)adc_value * 1750) / 255);
}

