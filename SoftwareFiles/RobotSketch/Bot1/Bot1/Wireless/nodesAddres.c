/*
 * nodesAddres.c
 *
 * Created: 20/03/2015 11:26:46 a.m.
 *  Author: af.rengifo239
 */ 
#include "nodesAddres.h"


#ifdef ADD_TX_1
static uint8_t addTx_1[NRF24L01_ADDRSIZE] = ADD_TX_1;
#endif


#ifdef ADD_TX_2
static uint8_t addTx_2[NRF24L01_ADDRSIZE] = ADD_TX_2;
#endif



#ifdef ADD_TX_3
static uint8_t addTx_3[NRF24L01_ADDRSIZE] = ADD_TX_3;
#endif // ADD_TX_3



void initNodesAddres(){	 
	           
			for (uint8_t i=0;i<NRF24L01_ADDRSIZE;i++){	
				
				#ifdef ADD_TX_1
				addTx[0][i]=addTx_1[i];	
		        #endif // ADD_TX_1
				
				#ifdef ADD_TX_2
				addTx[1][i]=addTx_2[i];
                #endif // AD_TX_"
		
				
					
				#ifdef ADD_TX_3
				addTx[2][i]=addTx_3[i];				
				#endif // ADD_TX_3
				
			}	 	
}