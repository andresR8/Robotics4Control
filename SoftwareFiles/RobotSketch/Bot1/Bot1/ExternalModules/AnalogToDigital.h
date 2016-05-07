/*
 * AnalogToDigital.h
 *
 * Author:  Andrés Rengifo at Universidad de los Andes
 * This work is licensed under a: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
 * http://creativecommons.org/licenses/by-nc-sa/4.0/
 */
#include <avr/io.h>
#ifndef F_CPU
#define F_CPU		8000000
#endif
#include <util/delay.h>

#ifndef ANALOGTODIGITAL_H_
#define ANALOGTODIGITAL_H_


          		
#define ADC4_RIGHT (1<<MUX2) 
#define ADC5_LEFT (1<<MUX2)|(1<<MUX0) 		


void initAnalogToDigital();
uint16_t AnalogToDigital_read(uint8_t adcChannel);
uint16_t AnalogToDigital_getAverage(uint8_t channel);



#endif /* ANALOGTODIGITAL_H_ */