/* LedRGB.c
*
* Created: 26/03/2015
* Author: Universidad de los Andes Designed by: Andrés Rengifo
* This work is licensed under a: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* http://creativecommons.org/licenses/by-nc-sa/4.0/
*/


#include "LedRGB.h"



void initLedRGB(){
	DDRD|=(1 << PD5)|(1 <<PD6)|(1 << PD7);  //Init pins to drive led as outputs
	PORTD|=~COLOR_OFF; //Init ports high lo start with the led off
}

void set_color(char color){
	PORTD|=~COLOR_OFF;
	switch (color)
	{
		case COLOR_OFF:
		 PORTD|=~COLOR_OFF;
		break;
		
		case COLOR_RED:
		PORTD&= ~COLOR_RED;
		break;
		
		case COLOR_GREEN:
	     PORTD&= ~COLOR_GREEN;
		break;		
			
		case COLOR_BLUE:
		PORTD&= ~COLOR_BLUE;
		break;		
		
		case COLOR_CYAN:
		PORTD&= ~COLOR_CYAN;
		break;
		
		case COLOR_MAGENTA:
		PORTD&= ~COLOR_MAGENTA;
		break;
		
		case COLOR_YELLOW:
		PORTD&= ~COLOR_YELLOW;
		break;
		
		case COLOR_WHITE:
		PORTD&= ~COLOR_WHITE;
		break;
	}
	
	
}