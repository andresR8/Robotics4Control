/*
 * CentralController.c
 *
 * Created: 06/03/2015 04:15:00 p.m.
 *  Author: af.rengifo239
 *  Based in LUFA library USBtoSerial project

             LUFA Library
     Copyright (C) Dean Camera, 2014.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2014  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Main source file for the USBtoSerial project. This file contains the main tasks of
 *  the project and is responsible for the initial application hardware configuration.
 */

#include "CentralController.h"

/** Circular buffer to hold data from the host before it is sent to the device via the serial port. */
static RingBuffer_t USBtoWireless_Buffer;

/** Underlying data buffer for \ref USBtoUSART_Buffer, where the stored bytes are located. */
static uint8_t   USBtoWireless_Buffer_Data[NRF24L01_PAYLOAD+2];


static uint8_t bufferin[NRF24L01_PAYLOAD];

const char MESSAGE_CONNECT=0x43,MESSAGE_GPS=0x47,MESSAGE_START=0x53,MESSAGE_STOP=0x54;

static uint8_t totalRobots=6;




/** LUFA CDC Class driver interface configuration and state information. This structure is
 *  passed to all CDC Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface =
	{
		.Config =
			{
				.ControlInterfaceNumber         = INTERFACE_ID_CDC_CCI,
				.DataINEndpoint                 =
					{
						.Address                = CDC_TX_EPADDR,
						.Size                   = CDC_TXRX_EPSIZE,
						.Banks                  = 1,
					},
				.DataOUTEndpoint                =
					{
						.Address                = CDC_RX_EPADDR,
						.Size                   = CDC_TXRX_EPSIZE,
						.Banks                  = 1,
					},
				.NotificationEndpoint           =
					{
						.Address                = CDC_NOTIFICATION_EPADDR,
						.Size                   = CDC_NOTIFICATION_EPSIZE,
						.Banks                  = 1,
					},
			},
	};


/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	SetupHardware();

	RingBuffer_InitBuffer(&USBtoWireless_Buffer, USBtoWireless_Buffer_Data, sizeof(USBtoWireless_Buffer_Data));


	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	GlobalInterruptEnable();
    
	nrf24l01_init();
		 


	while(1){	
						 
		// Only try to read in bytes from the CDC interface if the transmit buffer is not full 
		
		if (!(RingBuffer_IsFull(&USBtoWireless_Buffer))){
			int16_t ReceivedByte = CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);
			
			//Store received byte into the USART transmit buffer
			if (!(ReceivedByte < 0))
			   RingBuffer_Insert(&USBtoWireless_Buffer, ReceivedByte);			 
		}
		else
			processAndSendtoWireless();
			
		
	
		
	/*
		if(nrf24l01_readready()){
            nrf24l01_read(bufferin);
			CDC_Device_SendByte(&VirtualSerial_CDC_Interface,bufferin[0]);	
		}*/
			
		CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
		USB_USBTask();
		   
	}
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
#if (ARCH == ARCH_AVR8)
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);
#endif

	/* Hardware Initialization */
	LEDs_Init();	
	USB_Init();
	

	
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;

	ConfigSuccess &= CDC_Device_ConfigureEndpoints(&VirtualSerial_CDC_Interface);

	LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
	CDC_Device_ProcessControlRequest(&VirtualSerial_CDC_Interface);
}


/** Event handler for the CDC Class driver Line Encoding Changed event.
 *
 *  \param[in] CDCInterfaceInfo  Pointer to the CDC class interface configuration structure being referenced
 */
void EVENT_CDC_Device_LineEncodingChanged(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo)
{
	uint8_t ConfigMask = 0;

	switch (CDCInterfaceInfo->State.LineEncoding.ParityType)
	{
		case CDC_PARITY_Odd:
			ConfigMask = ((1 << UPM11) | (1 << UPM10));
			break;
		case CDC_PARITY_Even:
			ConfigMask = (1 << UPM11);
			break;
	}

	if (CDCInterfaceInfo->State.LineEncoding.CharFormat == CDC_LINEENCODING_TwoStopBits)
	  ConfigMask |= (1 << USBS1);

	switch (CDCInterfaceInfo->State.LineEncoding.DataBits)
	{
		case 6:
			ConfigMask |= (1 << UCSZ10);
			break;
		case 7:
			ConfigMask |= (1 << UCSZ11);
			break;
		case 8:
			ConfigMask |= ((1 << UCSZ11) | (1 << UCSZ10));
			break;
	}

}

void processAndSendtoWireless(){
	   


	uint8_t Byte=RingBuffer_Remove(&USBtoWireless_Buffer); //Process the first byte: COMMAND_BYTE-ROBOT_ID-DATA
	uint8_t addBroadcast[NRF24L01_ADDRSIZE]=ADD_TX_GEN;
	uint8_t add[NRF24L01_ADDRSIZE]=ADD_TX_GEN;
	uint8_t bufferout[NRF24L01_PAYLOAD];
  
	if(Byte==MESSAGE_GPS){
		Byte=RingBuffer_Remove(&USBtoWireless_Buffer); //Robot ID
		
		add[NRF24L01_ADDRSIZE-1]=NODE_GPS+Byte;  
	
				
		//SET TX
		for (uint8_t i=0;i<NRF24L01_PAYLOAD;i++){
		 Byte=RingBuffer_Remove(&USBtoWireless_Buffer);
		// CDC_Device_SendByte(&VirtualSerial_CDC_Interface,Byte);		
		 bufferout[i]=Byte;
		}		
		
		nrf24l01_settxaddr(add);
		nrf24l01_write(bufferout);
		
	}
	else if(Byte==MESSAGE_START){	
		for (uint8_t i=0;i<NRF24L01_PAYLOAD;i++){				
			bufferout[i]=CMD_START; //DummyByte
		}	
		nrf24l01_settxaddr(addBroadcast);
		nrf24l01_write(bufferout);		
		for (uint8_t i=1;i<sizeof(USBtoWireless_Buffer_Data);i++)  //Flush Buffer by Default
		Byte=RingBuffer_Remove(&USBtoWireless_Buffer);	
	}
	else if(Byte==MESSAGE_STOP){
		for (uint8_t i=0;i<NRF24L01_PAYLOAD;i++){
			bufferout[i]=CMD_STOP; //DummyByte
		}
		nrf24l01_settxaddr(addBroadcast);
		nrf24l01_write(bufferout);
		for (uint8_t i=1;i<sizeof(USBtoWireless_Buffer_Data);i++)  //Flush Buffer by Default
		Byte=RingBuffer_Remove(&USBtoWireless_Buffer);
	}
	else{
		for (uint8_t i=1;i<sizeof(USBtoWireless_Buffer_Data);i++)  //Flush Buffer by Default
		Byte=RingBuffer_Remove(&USBtoWireless_Buffer);
	}
	
		
		


		

}

