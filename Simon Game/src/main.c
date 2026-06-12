#include "initialisation.h"
#include "display.h"
#include "display_macros.h"
#include "timer.h"
#include "output.h"
#include "buzzer.h"
#include "input.h"
#include "sequence.h"
#include "play_back.h"
#include "adc.h"

#include <avr/interrupt.h>
#include <avr/io.h>

#include <stdint.h>

// Prototype functions 
void state_machine(void);
uint8_t wait_for_user_step(uint16_t playback_delay_ms);
uint8_t check_user_sequence(uint8_t length, uint16_t playback_delay_ms);

typedef enum // state positiosn 
{
    GAME_PLAY_SIMON,
    GAME_CHECK_USER,
    GAME_SUCCESS,
    GAME_FAIL

} game_state_t;


int main(void)
{
    cli(); // Turns off the interrupts for the intialisation of the peripherals  

    initialise_all(); // the initalisation function from intialisation.c 

    sei(); // turns back on the interrupts for the code to flow  

    state_machine(); // starts the state_machine 

    while (1)
    {
        ;
    }
}

void state_machine(void)
{
    game_state_t game_state = GAME_PLAY_SIMON; 

    uint8_t sequence_length = 1;

    uint32_t start_state = return_current_sequence();
    uint32_t next_game_state = start_state;

    uint16_t playback_delay_ms = 250;

    uint8_t correct = 0;

    while (1)
    {
        switch (game_state)
        {
            case GAME_PLAY_SIMON:
                // Reset LFSR to the start of the current sequence.
                set_current_sequence(start_state);

                // Simon plays the current sequence.
                play_sequence(sequence_length);

                // Save where the LFSR finished after Simon's full sequence.  If the user fails, the next game starts from this point.
                next_game_state = return_current_sequence();

                // Reset LFSR again so the user's input can be checked against the same sequence Simon just played.
                set_current_sequence(start_state);

                // Read playback delay for user input and success/fail displays.
                playback_delay_ms = get_adc_value();

                game_state = GAME_CHECK_USER;
                break;

            case GAME_CHECK_USER:
                correct = check_user_sequence(sequence_length, playback_delay_ms); // checks the sequence 

                if (correct) 
                {
                    game_state = GAME_SUCCESS;
                }
                else
                {
                    game_state = GAME_FAIL;
                }
                break;

            case GAME_SUCCESS:
                success_pattern(); 

                play_back_delay(playback_delay_ms);

                patterns_off();

                sequence_length++;

                game_state = GAME_PLAY_SIMON;
                break;

            case GAME_FAIL:
                fail_pattern();

                play_back_delay(playback_delay_ms);

                display_score(sequence_length);

                play_back_delay(playback_delay_ms);

                patterns_off();

                play_back_delay(playback_delay_ms);

                sequence_length = 1;

                start_state = next_game_state;

                game_state = GAME_PLAY_SIMON;
                break;

            default:
                sequence_length = 1;
                start_state = return_current_sequence();
                game_state = GAME_PLAY_SIMON;
                break;
        }
    }
}


uint8_t wait_for_user_step(uint16_t playback_delay_ms) // This function waits for the user to press one of the buttons and ensures that there is matching feedback but that button 
{
    while (1)
    {
        uint8_t events = input_button_event();

        if (events & PIN4_bm) // Button S! 
        {
            patterns_on(0);

            play_back_delay(playback_delay_ms / 2);

            wait_until_button_released(PIN4_bm);

            patterns_off();

            return 0;
        }
        else if (events & PIN5_bm) // Button S2
        {
            patterns_on(1);

            play_back_delay(playback_delay_ms / 2);

            wait_until_button_released(PIN5_bm);

            patterns_off();

            return 1;
        }
        else if (events & PIN6_bm) // Button S3
        {
            patterns_on(2);

            play_back_delay(playback_delay_ms / 2);

            wait_until_button_released(PIN6_bm);

            patterns_off();

            return 2;
        }
        else if (events & PIN7_bm) // Button S4 
        {
            patterns_on(3);

            play_back_delay(playback_delay_ms / 2);

            wait_until_button_released(PIN7_bm);

            patterns_off();

            return 3;
        }
    }
}

uint8_t check_user_sequence(uint8_t length, uint16_t playback_delay_ms) // this function checks To check whether the user correctly repeats the full Simon sequence for the current round
{
    for (uint8_t i = 0; i < length; i++)
    {
        uint8_t expected_step = sequence_forward();

        uint8_t user_step = wait_for_user_step(playback_delay_ms);

        if (user_step != expected_step)
        {
            return 0;
        }
    }

    return 1;
}
