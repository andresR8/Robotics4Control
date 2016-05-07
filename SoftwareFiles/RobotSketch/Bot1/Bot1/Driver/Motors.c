/*
 * Motors.c
 *
 * Created: 13/02/2015 12:02:12 p.m.
 * Author:  Andrés Rengifo at Universidad de los Andes
 * This work is licensed under a: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
 * http://creativecommons.org/licenses/by-nc-sa/4.0/
 */
#include "Motors.h"
#include <util/delay.h>

void initMotors(void){
	DDRB |= (1 << DIR_RIGHT); //PIN to control right motor direction  is now an output
	DDRB |= (1 << DIR_LEFT);  //PIN to control left motor direction  is now an output
	
	DDRB |= (1 << DDB1);         // PB1 is now an output channel A
	DDRB |= (1 << DDB2);         // PB2 is now an output channel B
	   
	PORTB |= (1 << DIR_LEFT)|(1<<DIR_RIGHT);
	
	//TCCR1A |= (1 << WGM10) ;	//  PWM, phase correct, 8-bit
	//COM1A1/COM1B1 COM1A0/COM1B0
	
	TCCR1A |= (1 << WGM10);	// Fast PWM 8bit
	//TCCR1B |=(1 << WGM12);
	
	//Set OCA1A and OCA1B on compare match set output to high level
	TCCR1A |= (1 << COM1A0)|(1 << COM1A1)|(1 << COM1B0)|(1 << COM1B1);
	
	
	TCCR1B  |= P8;      //Prescalling 8
	
	 
	 

}


void  motorLeft(int speed){
	speed=speed==0?0:fixSpeed(speed);
	if(speed<0){
	speed=-speed;
	PORTB |=(1 << DIR_LEFT);	
	}
	else{
	PORTB &= ~ (1 << DIR_LEFT);
	speed=100-speed;
	}
	
	
	
	
	if(speed==0){
		OCR1AL=0;
		PORTB |=(1 << DIR_LEFT);
	}
	else{	
		double n=(speed*255)/100.0;
		uint8_t num=(uint8_t)n;
		OCR1AL=num;
		
		#if DEBUG_UART==1
		printf("A%i\n",OCR1AL);
		#endif
		
	}
}

void motorRight(int speed){	
    speed=speed==0?0:fixSpeed(speed);
	
	if(speed<0){
		PORTB |= (1 << DIR_RIGHT);
		speed=-speed;
	}
	else{
		PORTB &= ~(1 << DIR_RIGHT);
		speed=100-speed;
	}
	
	if(speed==0){
		OCR1BL=0;
		PORTB |= (1 << DIR_RIGHT);
	}
	else{		
	   double n=(speed*255)/100.0;
	   uint8_t num=(uint8_t)n;
	   OCR1BL=num;
	   
	   #if DEBUG_UART==1	   
	   printf("B%i\n",OCR1BL);
	   #endif
	}
}

int fixSpeed(int speed){
	double voltage=(3.7*speed)/100.0;
	int s=(int)pow((2.1377*voltage) + 2.5182,1.9693);	
	return s;
}