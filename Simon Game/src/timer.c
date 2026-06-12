#include "timer.h"
#include "display.h"
#include "input.h"

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>


static volatile uint32_t elapsed_time_ms = 0;


// This is the timer initialisation which is put in the intialisation function in intitalisation.c 
void timer_init(void)
{
    TCB0.CTRLA = 0; 

    TCB0.CTRLB = TCB_CNTMODE_INT_gc; 
    TCB0.CCMP = 3333; // 1ms  

    TCB0.INTFLAGS = TCB_CAPT_bm; 
    TCB0.INTCTRL = TCB_CAPT_bm;

    TCB0.CTRLA = TCB_CLKSEL_DIV1_gc | TCB_ENABLE_bm;
}

// The elapsed time is used within play_back.c to ensure the timing of the segment patterns being lit up 
uint32_t get_elapsed_time(void)
{
    uint32_t time;

    uint8_t interrupt_state = SREG;

    cli(); // need to disable interrupts as the time is 32 bt meaning that it could be changed by the timer interrupt 

    time = elapsed_time_ms;

    SREG = interrupt_state;

    return time;
}

// The main timer interrupt used for button debouncing and display multiplexing 
ISR(TCB0_INT_vect) // TCB0 interrupt every 1 ms
{
    static uint8_t display_counter = 0;
    static uint8_t debounce_counter = 0;

    elapsed_time_ms++;

    debounce_counter++;

    if (debounce_counter >= 5) // Needed to change the debounce to 5 ms for the autograder to work 
    {
        input_debounce(); // Needed to change the display flicker to 5 ms in order to match up with the autograder specifications  
        debounce_counter = 0;
    }

    display_counter++;

    if (display_counter >= 5) // Needed to change the display flicker to 5 ms in order to match up with the autograder specifications 
    {
        display_flicker(); // This is the display flicker function within display.c that causes both sides of the 7 segment display to flicker at a rate which the eye can see both at the same time  
        display_counter = 0;
    }

    TCB0.INTFLAGS = TCB_CAPT_bm;
}
