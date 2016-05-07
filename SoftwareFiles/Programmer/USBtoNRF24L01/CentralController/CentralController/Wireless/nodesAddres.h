/*
 * nodesAdress.h
 *
 * Created: 18/03/2015 07:49:07 p.m.
 *  Author: af.rengifo239
 */ 


#ifndef NODESADDRES_H_
#define NODESADDRES_H_
#include <stdint.h>

#define NODE_NUMBER 8//The number of the node in the Graph
#define NODE_NEXT NODE_NUMBER+1 
#define NODE_GPS 0xB0
#define NODE_GEN 0xCC


#ifndef NRF24L01_ADDRSIZE
#define NRF24L01_ADDRSIZE 5
#endif

#define NRF24L01_ADDRP0 {NODE_NUMBER,NODE_NUMBER,NODE_NUMBER,NODE_NUMBER,NODE_NUMBER} //pipe 0, 5 byte address
#define NRF24L01_ENABLEDP0 1 //pipe 0
#define ADD_TX_GEN {NODE_GEN,NODE_GEN,NODE_GEN,NODE_GEN,NODE_GEN} 
	
#define NRF24L01_ADDRTX NRF24L01_ADDRP0 //tx default address*/

#define CMD_START 0xAB
#define CMD_STOP 0xBA


#endif /* NODESADRESS_H_ */