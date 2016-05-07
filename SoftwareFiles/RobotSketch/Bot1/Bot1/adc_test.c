/*	ADC Test
http://tom-itx.dyndns.org:81/~webpage/how_to/atmega168/mega168_adc_index.php
	For an Atmega 48 88 or 168
	Sends ADC results to the serial port
	Set your terminal to 2400 N 8 1
	
	Atmega168 DIP TX   PD1 (pin3)
	Atmega168 DIP RX   PD0 (pin2)
	Atmega168 DIP ADC2 PC2 (PIN25) */
	
#define F_CPU 1000000UL
#define UBRR_1200 51
#define UBRR_2400 25		// for 1Mhz

// #define UBRR_2400 207	// for 8Mhz with .2% error
// #define UBRR_9600 51		// for 8Mhz with .2% error
// #define UBRR_19200 25	// for 8Mhz with .2% error


#define PORTLEDS PORTD
#define DDRLEDS	 DDRD
// LEDS PINS
#define LED1	 (1<<PIND4)
#define LED2	 (1<<PIND5)
#define LED3	 (1<<PIND6)
#define LED4	 (1<<PIND7)

// RVAR PINS (Reference 0 and Vref)
#define REF1	 (1<<PIND3)
#define REF0	 (1<<PIND2)

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void read_adc(void);		// Function Declarations
void adc_init(void);
void USART_init( unsigned int ubrr );
void USART_tx_string( char *data ); 

volatile unsigned int adc_temp;
char outs[20];

int main(void) {

int i=0; //FES
	
	//DDRD=0X0c;							// Initialize PORTD as output
	DDRLEDS|=(REF0|REF1|LED1|LED2|LED3|LED4); // Initialize PORTD as output
	//PORTD=0x08;							// PORTD = 0x08 (Reference Rvar)
	PORTLEDS=(REF1);
	adc_init();							// Initialize the ADC (Analog / Digital Converter)
	USART_init(UBRR_2400);				// Initialize the USART (RS232 interface)
	USART_tx_string("Connected!\r\n");	// we're alive!
	_delay_ms(125);						// wait a bit

	while(1)
	{	
		read_adc();
		snprintf(outs,sizeof(outs),"%3d %d\r\n", adc_temp,i);	// print it
		USART_tx_string(outs);
		_delay_ms(10);		// wait a bit
			

		// Cuando adc_temp sea menor que 20, es decir el valor del ADC es menor a 20, se debe cambiar de secuencia, se usa un delay para detener la conversion y dat tiempo al cambio de secuencia.
		if (adc_temp < 20)
		{
		
			// WRITE YOUR CODE HERE!!!!!!


			// Retardo para detener conversion y dar tiempo al cambio de secuencia
			_delay_ms(1200);						// wait a bit
		}

		if (i==0)
		{
			// SECUENCIA 1
			// WRITE YOUR CODE HERE!!!!!!

			
			
		}
		else if (i==1)
		{
			// SECUENCIA 2
			// WRITE YOUR CODE HERE!!!!!!


		}
	}
}

/* INIT ADC */
void adc_init(void)
{
	/** Setup and enable ADC **/
	ADMUX = (0<<REFS1)|	// Reference Selection Bits
			(1<<REFS0)|		// AVcc - external cap at AREF
			(0<<ADLAR)|		// ADC Left Adjust Result
			(0<<MUX2)|		// ANalog Channel Selection Bits
			(0<<MUX1)|		// ADC0 (PC2 PIN25)
			(0<<MUX0);
	
	ADCSRA = (1<<ADEN)|	// ADC ENable
			(0<<ADSC)|		// ADC Start Conversion
			(0<<ADATE)|		// ADC Auto Trigger Enable
			(0<<ADIF)|		// ADC Interrupt Flag
			(0<<ADIE)|		// ADC Interrupt Enable
			(1<<ADPS2)|		// ADC Prescaler Select Bits
			(0<<ADPS1)|
			(1<<ADPS0);
							// Timer/Counter1 Interrupt Mask Register
	TIMSK1 |= (1<<TOIE1);	// enable overflow interrupt
	
	TCCR1B |= (1<<CS11)|
			(1<<CS10);  // native clock
}

/* READ ADC PINS */
void read_adc(void) {
	unsigned char i =4;
	adc_temp = 0;
	while (i--) {
		ADCSRA |= (1<<ADSC);
		while(ADCSRA & (1<<ADSC));
		adc_temp+= ADC;
		_delay_ms(5);
	}
	adc_temp = adc_temp / 4;	// Average a few samples
}

/* INIT USART (RS-232)  */
void USART_init( unsigned int ubrr ) {

	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1 << TXEN0);		// Enable receiver, transmitter & RX interrupt
	UCSR0C = (3 << UCSZ00);	//asynchronous 8 N 1
}

/* SEND A STRING TO THE RS-232 */
void USART_tx_string( char *data ) { 
	while ((*data != '\0')) {
		while (!(UCSR0A & (1 <<UDRE0)));
		UDR0 = *data;
		data++;
	}   
}


