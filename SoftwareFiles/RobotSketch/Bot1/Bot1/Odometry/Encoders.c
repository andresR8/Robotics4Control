/*
 * Encoders.c
 *
 * Created: 18/02/2015 12:54:34 p.m.
 * Author:  Andrés Rengifo at Universidad de los Andes 
 * This work is licensed under a: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
 * http://creativecommons.org/licenses/by-nc-sa/4.0/
*/

#include "Encoders.h"
#include <avr/io.h>


void initEncoders(){
	DDRD &= ~(1 << PORT_RIGHT);                     //PORT_RIGHT input
	DDRD &= ~(1 << PORT_LEFT);                      //PORT_LEFT input
	PORTD |=(1 << PORT_RIGHT)|(1 << PORT_LEFT);     //Pull-up for read sensors
	
	PCICR |= _BV(PCIE2);                            //set PCIE2 to enable PCMSK2 scan
	PCMSK2 |= _BV(PCINT19);                        // set PCINT19 to trigger an interrupt on state change
	PCMSK2 |= _BV(PCINT20);                        // set PCINT20 to trigger an interrupt on state change
}