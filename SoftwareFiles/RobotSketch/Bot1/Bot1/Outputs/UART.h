/* UART.h
*
* Created: 26/03/2015
* Author:  Andrés Rengifo at Universidad de los Andes 
* This work is licensed under a: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* http://creativecommons.org/licenses/by-nc-sa/4.0/
*/


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <avr/io.h>



#ifndef UART_H_
#define UART_H_


// Use UART0 on architectures having two UARTs
#ifndef UDR
#define UDR UDR0
#define UCSRA UCSR0A
#define UCSRB UCSR0B
#define UCSRC UCSR0C
#define URSEL 0
#ifndef RXC
#define UCSZ0 UCSZ00
#define UCSZ1 UCSZ01
#define RXEN RXEN0
#define TXEN TXEN0
#define RXC RXC0
#define UDRE UDRE0
#endif
#define UBRRH UBRR0H
#define UBRRL UBRR0L
#ifndef U2X
#define U2X U2X0
#endif
#endif

#define FOSC 8000000             // Clock Speed

#define BAUD 4800                // Baud rate
#define MYUBRR FOSC/16/BAUD-1  // Calcule for communication settings

#ifndef DEBUG_UART
#define DEBUG_UART 0
#endif


char STRING[10];
char STRING1[10];
char STRING2[10];
char STRING3[10];
char STRING4[10];

void UART_send_char(uint8_t  c);
char usart_getchar( void );
void usart_pstr (char *s);
unsigned char usart_kbhit(void);
int usart_putchar_printf(char var, FILE *stream);
void initUART();
void printD(char *str,double d);

#pragma GCC diagnostic ignored "-Wunused-variable"   //Hide Warning in compilation results
static FILE mystdout = FDEV_SETUP_STREAM(usart_putchar_printf, NULL, _FDEV_SETUP_WRITE);




#endif /* UART_H_ */