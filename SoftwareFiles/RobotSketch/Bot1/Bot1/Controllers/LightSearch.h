/*
 * LightSearch.h
 *
 * Created: 28/05/2015 7:43:30 p. m.
 * Author:  Andrés Rengifo at Universidad de los Andes
 * This work is licensed under a: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
 * http://creativecommons.org/licenses/by-nc-sa/4.0/
 */
#include <math.h>
#include <avr/io.h>
#include "../Outputs/UART.h"

#ifndef LIGHTSEARCH_H_
#define LIGHTSEARCH_H_

int * lightSearchExecute(uint16_t lightRight, uint16_t lightLeft);
int inputLayer(int d1, int d2);
double * secondHiddenLayer(int d);
double * thirdHiddenLayer(double d1, double d2);
double * outputLayer(double d1,double d2);

double logisticSigmoidalFcn(double x);

#define topSpeed 70
#define minSpeed 40
#define smooth  0.2
#define halfPoint (topSpeed+minSpeed)/2


#endif /* LIGHTSEARCH_H_ */