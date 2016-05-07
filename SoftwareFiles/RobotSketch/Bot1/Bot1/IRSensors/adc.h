 /* adc.h
 *
 * Created: 11/02/2015
 * Author:  Andrés Rengifo at Universidad de los Andes
 * This work is licensed under a: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
 * http://creativecommons.org/licenses/by-nc-sa/4.0/
 */
 
#include <avr/io.h>

#ifndef F_CPU
#define F_CPU		8000000
#endif
#include <util/delay.h>

#ifndef ADC_H
#define ADC_H
void initAdc(void);
uint16_t readAdc(uint8_t mux);
#endif
