#ifndef BUZZER_H
#define BUZZER_H

#include <stdint.h>

// Tones matching my student number n12087904 

#define TONE_0 303  // E high, based on student number ending 04
#define TONE_1 255  // C sharp, based on student number ending 04
#define TONE_2 404  // A, based on student number ending 04
#define TONE_3 151  // E low, based on student number ending 04


void pwm_init(void);
void buzzer_on(uint16_t frequency);
void buzzer_off(void);


#endif
