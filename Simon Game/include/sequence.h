#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <stdint.h>

uint8_t sequence_forward(void);
void sequence_initial_state(void);
uint32_t return_current_sequence(void);
void set_current_sequence(uint32_t new_sequence);
void play_sequence(uint8_t length); 



#endif