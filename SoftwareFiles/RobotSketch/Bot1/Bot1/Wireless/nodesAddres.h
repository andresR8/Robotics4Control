/*
 * nodesAdress.h
 *
 * Created: 18/03/2015 07:49:07 p.m.
 * Author: Universidad de los Andes Designed by: Andrés Rengifo
 * This work is licensed under a: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
 * http://creativecommons.org/licenses/by-nc-sa/4.0/
*/


#ifndef NODESADDRES_H_
#define NODESADDRES_H_
#include <stdint.h>

#define NODE_NUMBER 1//The number of the node in the Graph
#define NEXT_NODE NODE_NUMBER+1 
#define NODE_GPS 0xB0
#define NODE_GEN 0xCC


#ifndef NRF24L01_ADDRSIZE
#define NRF24L01_ADDRSIZE 5
#endif

#define NRF24L01_ADDRP0 {NODE_GEN,NODE_GEN,NODE_GEN,NODE_GEN,NODE_GEN} //pipe 0, 5 byte address //FOR star/Stop Commands
#define NRF24L01_ADDRP1 {NODE_GEN,NODE_GEN,NODE_GEN,NODE_GEN,NODE_GPS+NODE_NUMBER} //pipe 0, 5 byte address                //FOR GPS Functions
#define NRF24L01_ADDRP2 {NODE_GEN,NODE_GEN,NODE_GEN,NODE_GEN,NODE_NUMBER} //pipe 0, 5 byte address             //FOR MARS
#define NRF24L01_ENABLEDP0 1 //pipe 0
#define NRF24L01_ENABLEDP1 1 //pipe 0
#define NRF24L01_ENABLEDP2 1 //pipe 0
#define ADD_TX_1 {NODE_GEN,NODE_GEN,NODE_GEN,NODE_GEN,NEXT_NODE}
#define CMD_START 0xAB	
	
#define NRF24L01_ADDRTX NRF24L01_ADDRP0 //tx default address*/


#endif /* NODESADRESS_H_ */