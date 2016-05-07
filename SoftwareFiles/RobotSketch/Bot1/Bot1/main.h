/*
 * main.h
 *
 * Created: 26/09/2014 12:43:27 p.m.
 * Author:  Andrés Rengifo at Universidad de los Andes
 * This work is licensed under a: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
 * http://creativecommons.org/licenses/by-nc-sa/4.0/
 *//

#include <avr/io.h>
#include <avr/boot.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <string.h>


#include "Outputs/LedRGB.h"
#include "Outputs/UART.h"
#include "Wireless/nrf24l01.h"
#include "Wireless/nodesAddres.h"
#include "Driver/Motors.h"
#include "Odometry/Dynamics.h"
#include "Controllers/GoToGoal.h"
#include "Controllers/Supervisor.h"
#include "Controllers/LightSearch.h"
#include "Controllers/AvoidObstacles.h"
#include "ExternalModules/AnalogToDigital.h"
#include "IRSensors/IRSensors.h"



#ifndef F_CPU
#define F_CPU		8000000
#endif

#include <util/delay.h>

#ifndef MAIN_H_
#define MAIN_H_

#define MAX_TX  10

#define BOOTADDR	0x3800
#define TIMEOUT		1000
#define SIGRD 5                /* Necesario para leer el signature del sipositivo Signature Atmega 168A= 0x1E9406 boot_signature_byte_get(0x0)=0x1E
                                 Atmega 328P= 0x1E950F boot_signature_byte_get(0x0)=0x1E*/

static void init();




#endif /* MAIN_H_ */