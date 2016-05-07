/*
 * IRSensors.h
 *
 * Created: 11/02/2015 03:55:32 p.m.
  * Author:  Andrés Rengifo at Universidad de los Andes
  * This work is licensed under a: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
  * http://creativecommons.org/licenses/by-nc-sa/4.0/
  */
#include <math.h>

#ifndef IRSENSORS_H_
#define IRSENSORS_H_

#define IR_EMITTER PD0
#define AVG_MESUREMENTS  10
#define MAX_SENSORS 5
#define CH_S1       3
#define CH_S2       6
#define CH_S3       7
#define CH_S4       1
#define CH_S5       2





void initIRSensors(void);
double * IRSensorsGetDistance(void);
double average(double a[]);
double * IRreadRaw(void);
double IRSensorsGetAvoidVectorHeading(void);




#endif /* IRSENSORS_H_ */