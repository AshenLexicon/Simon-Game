#include "play_back.h"
#include "timer.h"

#include <stdint.h>

void play_back_delay(uint16_t playback_delay_ms) // This is for the timing of the stage and stage transitions - works with the potentiometer to set how long the rounds go for 
{
    uint32_t start_time = get_elapsed_time(); // records the start time before the delay starts 

    while ((get_elapsed_time() - start_time) < playback_delay_ms) // Main.c uses this to control the Simon playback, user feedback, success/fail patterns and score display timimg 
    {
        ;
    }
}
