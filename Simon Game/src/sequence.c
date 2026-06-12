#include "sequence.h"
#include "output.h"
#include "play_back.h"
#include "adc.h"

#include <stdint.h>

#define MASK 0xE2026E6BUL // provided mask 
#define INIT_STATE 0x12087904UL // initial state corresponding with my student id 


static uint32_t STATE_LFSR = INIT_STATE;  // stores the current state 

// This moves the sequence forward to the next random combindatoin 
uint8_t sequence_forward(void) // this is the LFSR for the PRNG 
{
    uint8_t bit = STATE_LFSR & 1; 

    STATE_LFSR = STATE_LFSR >> 1;

    if (bit == 1)
    {
        STATE_LFSR = STATE_LFSR ^ MASK;
    }

    return STATE_LFSR & 0b11;
}

void sequence_initial_state(void) // This can be used for both intialising the sequence and returning the sequence to its initial state 
{
    STATE_LFSR = INIT_STATE;
}

uint32_t return_current_sequence(void) // Returns the current sequence to save where a sequence starts or finishs 
{
    return STATE_LFSR;
}

void set_current_sequence(uint32_t new_sequence) // Sets the current LFSR state and is used to replay the same sequence for checking the user input 
{
    STATE_LFSR = new_sequence;
}



void play_sequence(uint8_t length) // Plays the somon sequence for the current level with each step generated from the LFSR. This is held for half the playback delay and turned off for the other half 
{
    for (uint8_t i = 0; i < length; i++)
    {
        uint16_t playback_delay_ms = get_adc_value(); // read the potentiometer at the start of each step to set the playback_delay

        uint8_t step = sequence_forward(); // generates the next step 

        // Shows the pattern for the step and plays the corresponding tone for half the playback delay 
        patterns_on(step);
        play_back_delay(playback_delay_ms / 2);

        // Turns the step off for half the playback delay 
        patterns_off();
        play_back_delay(playback_delay_ms / 2);
    }
}