 /* adc.c
 *
 * Created: 11/02/2015
 * Author:  Andrés Rengifo at Universidad de los Andes
 * This work is licensed under a: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
 * http://creativecommons.org/licenses/by-nc-sa/4.0/
 */
 
#include "adc.h"

void initAdc(void)
{
	/** Setup and enable ADC **/
	ADMUX = (1<<REFS1)|	// Reference Selection Bits
	(1<<REFS0)|		//1.1V Internal
	(0<<ADLAR);		// ADC Left Adjust Result
	
	ADCSRA = (1<<ADEN)|	// ADC ENable
	//(0<<ADSC)|		// ADC Start Conversion
	//(0<<ADATE)|		// ADC Auto Trigger Enable
	//(0<<ADIF)|		// ADC Interrupt Flag
	//(0<<ADIE)|		// ADC Interrupt Enable
	(1<<ADPS2)|		    // ADC Prescaler Select Bits 8MHz/32=250KHz
	(0<<ADPS1)|
	(1<<ADPS0);
}

uint16_t readAdc(uint8_t mux) {
	ADMUX &= ~(0x7); //Clear previous Channel	
	ADMUX|=mux;      //Set the new Channel
	
	ADCSRA |= (1<<ADEN); //Enable ADC
	_delay_ms(1);        
	
	// set ADSC bit to get the *next* conversion started
	ADCSRA |= (1<<ADSC);
	
	// read from ADC, waiting for conversion to finish
	// (assumes someone else asked for a conversion.)
	// wait for it to be cleared
	while(ADCSRA & (1<<ADSC)) {
		// do nothing... just hold your breath.
	}
	// bit is cleared, so we have a result.
	
	// read from the ADCL/ADCH registers, and combine the result
	// Note: ADCL must be read first (datasheet pp. 259)
	uint8_t low = ADCL;
	uint8_t high = ADCH;
	uint16_t result = low + (high<<8);
	
	ADCSRA &= ~(1<<ADEN );			// Disable ADC to save power
	
	return result;
}