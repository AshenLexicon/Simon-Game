#include "initialisation.h"
#include "output.h"
#include "input.h"
#include "sequence.h"
#include "adc.h"
#include "display.h"
#include "timer.h"
#include "buzzer.h"

#include <stdint.h>
#include <avr/io.h>


// This is the intialisation function which intialising all the requred pins and perhiherals.
// Helps keep main.c clean  
void initialise_all(void)
{

    display_init();
    timer_init(); 
    pwm_init();
    input_init();
    sequence_initial_state();
    adc_init();

    
}






