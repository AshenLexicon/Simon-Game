#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>

void input_init(void);
void input_debounce(void);
uint8_t input_button_event(void);
void wait_until_button_released(uint8_t button_press); 

#endif