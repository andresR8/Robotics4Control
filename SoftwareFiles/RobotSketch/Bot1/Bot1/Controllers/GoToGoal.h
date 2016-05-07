/*
 * GoToGoal.h
 *
 * Created: 25/02/2015 10:15:49 a.m.
 * Author:  Andrés Rengifo at Universidad de los Andes
 * This work is licensed under a: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
 * http://creativecommons.org/licenses/by-nc-sa/4.0/
 */ 
#include "../Odometry/Dynamics.h"
#include "../Outputs/UART.h"
#include <math.h>

#ifndef GOTOGOAL_H_
#define GOTOGOAL_H_


struct PID{
	  float Kp;
	  float Ki;	 
	  float Kd;
}pid;

struct GOAL{
	double x;
	double y;
}goal;


 float E_k;
 float e_k_1;

static double e, e1, e2, u, delta_u;
 
 double * gotoGoalExecute(float v);
 void initGotoGoal(double x,double y); 
 double signG(double x);



#endif /* GOTOGOAL_H_ */