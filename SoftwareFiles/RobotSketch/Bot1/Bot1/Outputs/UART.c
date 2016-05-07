/* UART.c
*
* Created: 26/03/2015
* Author: Universidad de los Andes Designed by: Andrés Rengifo
* This work is licensed under a: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* http://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#include "UART.h"


void initUART() {
	int16_t ubrr=MYUBRR;
	// Set baud rate
	UBRR0H = (uint8_t)(ubrr>>8);
	UBRR0L = (uint8_t)ubrr;
	// Enable receiver and transmitter
	UCSR0B = (1<<TXEN0);//(1<<RXEN0)|(1<<TXEN0)|(1 << RXCIE0); // Rx Tx enable y interrupciones
	// Set frame format: 8data, 1stop bit
	UCSR0C = (3<<UCSZ00); // Set frame format: 8data, 1 stop bit
	stdout=&mystdout;	
	
}
void UART_send_char(uint8_t data) {
	// Wait for empty transmit buffer
	while ( !(UCSR0A & (_BV(UDRE0))) );
	// Start transmission
	UDR0 = data;
}
char usart_getchar(void) {
	// Wait for incoming data
	while ( !(UCSR0A & (_BV(RXC0))) );
	// Return the data
	return UDR0;
}
unsigned char usart_kbhit(void) {
	//return nonzero if char waiting polled version
	unsigned char b;
	b=0;
	if(UCSR0A & (1<<RXC0)) b=1;
	return b;
}
void usart_pstr(char *s) {
	// loop through entire string
	while (*s) {
		UART_send_char(*s);
		s++;
	}
}
// this function is called by printf as a stream handler
int usart_putchar_printf(char var, FILE *stream) {
	// translate \n to \r for br@y++ terminal
	if (var == '\n') UART_send_char('\r');
	UART_send_char(var);
	return 0;
}

void printD(char *str,double d){
	dtostrf(d,10,3,STRING);
	printf(str,STRING);	
}