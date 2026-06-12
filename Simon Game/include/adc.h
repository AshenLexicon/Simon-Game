#ifndef ADC_H
#define ADC_H

#include <stdint.h>

void adc_init(void);
uint8_t adc_results(void);
uint16_t get_adc_value(void);

#endif