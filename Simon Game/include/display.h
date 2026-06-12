#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

extern volatile uint8_t display_left;
extern volatile uint8_t display_right;

void display_flicker(void);
void spi_display(uint8_t data);
void update_display(uint8_t left, uint8_t right);
void display_init(void);


#endif
