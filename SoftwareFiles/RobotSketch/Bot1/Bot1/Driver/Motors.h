/*
 * Motors.h
 *
 * Created: 13/02/2015 12:02:26 p.m.
 * Author:  Andrés Rengifo at Universidad de los Andes
 * This work is licensed under a: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
 * http://creativecommons.org/licenses/by-nc-sa/4.0/
 */
#include <avr/io.h>

#ifndef MOTORS_H_
#define MOTORS_H_

#define DIR_RIGHT  PB7
#define DIR_LEFT   PB6

#define P0 (1 << CS00) //No Prescaling
#define P8 (1 << CS01) //Clock / 8
#define P64 (1 << CS00)|(1 << CS01) //Clock / 64
#define P256 (1 << CS02) //Clock / 256
#define P1024 (1 << CS02)|(1 << CS00) //Clock / 1024

#ifndef F_CPU
# define F_CPU 8000000UL
#endif



void initMotors(void);
void motorLeft(int speed);
void motorRight(int speed);
int fixSpeed(int speed);


#endif /* MOTORS_H_ */