/*
nrf24l01 lib 0x02

copyright (c) Davide Gironi, 2012

References:
  -  This library is based upon nRF24L01 avr lib by Stefan Engelke
     http://www.tinkerer.eu/AVRLib/nRF24L01
  -  and arduino library 2011 by J. Coliz
     http://maniacbug.github.com/RF24

Released under GPLv3.
Please refer to LICENSE file for licensing information.
*/

#ifndef _NRF24L01_H_
#define _NRF24L01_H_



#include <avr/io.h>
#include "nodesAddres.h"

//CE and CSN port definitions
#define NRF24L01_DDR DDRB
#define NRF24L01_PORT PORTB
#define NRF24L01_CSN PB0

#define NRF24L01_CE_DDR DDRB
#define NRF24L01_CE_PORT PORTB
#define NRF24L01_CE PB5

//IRQ port definitions
#define NRF24L01_IRQ_DDR DDRD
#define NRF24L01_IRQ_PORT PORTD
#define NRF24L01_IRQ PD0

//define the spi path
#define NRF24L01_SPIPATH "spi.h" //spi lib path

//CE and CSN functions
#define nrf24l01_CSNhi NRF24L01_PORT |= (1<<NRF24L01_CSN);
#define nrf24l01_CSNlo NRF24L01_PORT &= ~(1<<NRF24L01_CSN);
#define nrf24l01_CEhi NRF24L01_CE_PORT |=  (1<<NRF24L01_CE);
#define nrf24l01_CElo NRF24L01_CE_PORT &= ~(1<<NRF24L01_CE);

//power setup
#define NRF24L01_RF24_PA_MIN 1
#define NRF24L01_RF24_PA_LOW 2
#define NRF24L01_RF24_PA_HIGH 3
#define NRF24L01_RF24_PA_MAX 4
#define NRF24L01_RF24_PA NRF24L01_RF24_PA_MAX

//speed setup
#define NRF24L01_RF24_SPEED_250KBPS 1
#define NRF24L01_RF24_SPEED_1MBPS 2
#define NRF24L01_RF24_SPEED_2MBPS 3
#define NRF24L01_RF24_SPEED NRF24L01_RF24_SPEED_2MBPS

//crc setup
#define NRF24L01_RF24_CRC_DISABLED 1
#define NRF24L01_RF24_CRC_8 2
#define NRF24L01_RF24_CRC_16 3
#define NRF24L01_RF24_CRC NRF24L01_RF24_CRC_16

//transmission channel
#define NRF24L01_CH 76

//payload lenght
#define NRF24L01_PAYLOAD 1

//auto ack enabled
#define NRF24L01_ACK 1

//auto retransmit delay and count
//define NRF24L01_RETR (0b0100 << NRF24L01_REG_ARD) | (0b0111 << NRF24L01_REG_ARC) //1500uS, 15 times
#define NRF24L01_RETR (0b0010 << NRF24L01_REG_ARD) | (0b0111 << NRF24L01_REG_ARC) //750uS, 15 times
//#define NRF24L01_RETR (0b0000 << NRF24L01_REG_ARD) | (0b0000 << NRF24L01_REG_ARC) //Retransmit Disable


//address size
#define NRF24L01_ADDRSIZE 5




 //enable print info function
#define NRF24L01_PRINTENABLE 1


extern void nrf24l01_init();
uint8_t nrf24l01_getstatus();
uint8_t nrf24l01_readready();
void nrf24l01_read(uint8_t *data);
uint8_t nrf24l01_write(uint8_t *data);
void nrf24l01_setrxaddr(uint8_t channel, uint8_t *addr);
void nrf24l01_settxaddr(uint8_t *addr);
void nrf24l01_setirq();  
extern uint8_t nrf24l01_writeRT();
extern uint8_t nrf24l01_readregister(uint8_t reg);

#if NRF24L01_PRINTENABLE == 1
 void nrf24l01_printinfo();
#endif


#endif
