#include "input.h"

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define BUTTON_BITS (PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm)

static volatile uint8_t pb_state;
static volatile uint8_t pb_falling_events;


void input_init(void) // initialising the pins required for button input 
{

    PORTA.DIRCLR = PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm; 

    // Enable Pull up resistors letting unpressed be high and pressed be low (Active Low)
    PORTA.PIN4CTRL |= PORT_PULLUPEN_bm; // S1
    PORTA.PIN5CTRL |= PORT_PULLUPEN_bm; // S2
    PORTA.PIN6CTRL |= PORT_PULLUPEN_bm; // S3 
    PORTA.PIN7CTRL |= PORT_PULLUPEN_bm; // S4 

}


void input_debounce(void) // Debounces S1-S4 using the vertical counter method from Studio/Tutorial 8. This is called in the interrupt in timer.c 
{
    // Vertical Counter Debouncing method 
    static uint8_t count0 = 0;
    static uint8_t count1 = 0;

    uint8_t pb_sample = VPORTA.IN & BUTTON_BITS;

    uint8_t pb_changed = pb_sample ^ pb_state;

    count1 = (count1 ^ count0) & pb_changed;
    count0 = ~count0 & pb_changed;

    uint8_t pb_update = count1 & count0;

    uint8_t old_state = pb_state;

    pb_state ^= pb_update;

    uint8_t falling_edges = old_state & ~pb_state;

    pb_falling_events |= falling_edges & BUTTON_BITS;
}




uint8_t input_button_event(void)
{
    uint8_t events;

    uint8_t interrupt_state = SREG; //SREG is the macro for status register | copy the current CPU status register into a normal variable

    cli(); // Disabling interrupts whilst copying and clearing the button event flags, this ensures that timer.c does not change pb_falling events halfway through

    events = pb_falling_events;
    pb_falling_events = 0;

    SREG = interrupt_state; // restore the CPU status register back to what it was

    return events & BUTTON_BITS;
}

void wait_until_button_released(uint8_t button_press) // This function waits until the physical button has been released, ensuring that you are able to hold down the button 
{
    while (!(VPORTA.IN & button_press))
    {
        ;
    }
}

