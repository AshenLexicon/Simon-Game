#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdint.h>



void patterns_on(uint8_t segment);
void patterns_off(void); 
void success_pattern(void);
void fail_pattern(void);
void display_score(uint16_t score);


#endif
