/*
 * AvoidObstacles.h
 *
 * Created: 30/05/2015 7:16:52 p. m.
 * Author:  Andrés Rengifo at Universidad de los Andes
 * This work is licensed under a: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
 * http://creativecommons.org/licenses/by-nc-sa/4.0/
 */ 
#include <avr/io.h>
#include "stdlib.h"
#include "../Outputs/UART.h"
#include "../IRSensors/IRSensors.h"
#include "Supervisor.h"


#ifndef AVOIDOBSTACLES_H_
#define AVOIDOBSTACLES_H_

struct MFCN{
	double w;
	double center;	
	int number;
};

#define MEMBER_ERROR 5
#define MEMBER_ERROR_DOT 7
#define MEMBER_W 7

void initAvoidObstacles(void);
double avoidObstaclesExecute(double desiredHeading);
double * computeErrorMembershipFcn(double error);
double * computeErrorDotMembershipFcn(double errorDot);
double * interference(double * error, double * errorDot);
double deFuzzyfication(double * wInterference);

double triangularFcn(double x,double w,double center);





#endif /* AVOIDOBSTACLES_H_ */
