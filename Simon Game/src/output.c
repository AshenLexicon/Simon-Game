#include "initialisation.h"
#include "display.h"
#include "display_macros.h"
#include "buzzer.h"

#include <stdint.h>
#include <avr/io.h>


// The array for the scoreboard values which are used in main.c after a fail round to showcase the final score 
static const uint8_t score_board_values[10] = { 
    0b00001000, // 0
    0b01101011, // 1
    0b01000100, // 2
    0b01000001, // 3
    0b00100011, // 4 
    0b00010001, // 5
    0b00010000, // 6
    0b01001011, // 7
    0b00000000, // 8
    0b00000001  // 9 
};

// This displays the score after the GAME_FAIL state to show the sequence length reached
void display_score(uint16_t score)
{
    uint8_t display_score = score % 100;

    uint8_t tens = display_score / 10;
    uint8_t ones = display_score % 10;

    if (score < 10)
    {
        update_display(DISP_OFF, score_board_values[ones]);
    }
    else
    {
        update_display(score_board_values[tens], score_board_values[ones]);
    }
}

// Turns on the patterns that will be displayed throughout the game. The sequence uses the LFSR as the pattern of segment changes 
void patterns_on(uint8_t segment)
{
    if (segment == 0) // each segment round as a corresponding tone and part lit up 
    {
        buzzer_on(TONE_0);
        update_display(DISP_BAR_LEFT, DISP_OFF);
    }
    else if (segment == 1)
    {
        buzzer_on(TONE_1);
        update_display(DISP_BAR_RIGHT, DISP_OFF);
    }
    else if (segment == 2)
    {
        buzzer_on(TONE_2);
        update_display(DISP_OFF, DISP_BAR_LEFT);
    }
    else if (segment == 3)
    {
        buzzer_on(TONE_3);
        update_display(DISP_OFF, DISP_BAR_RIGHT);

    }

}

void patterns_off(void) // turns off the patterns and the buzzer 
{
    update_display(DISP_OFF, DISP_OFF);
    buzzer_off();
}

void success_pattern(void) // this is the success pattern shown after successfuly passing a round/sequence
{
    update_display(DISP_ON, DISP_ON);
    buzzer_off();
}

void fail_pattern(void) // This is the fail pattern shown after failling a round/sequence 
{
    update_display(DISP_DASH, DISP_DASH);
    buzzer_off();
}

