/*
 * GoToGoal.c
 *
 * Created: 25/02/2015 10:16:13 a.m.
 * Author:  Andrés Rengifo at Universidad de los Andes
 * This work is licensed under a: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
 * http://creativecommons.org/licenses/by-nc-sa/4.0/
 */

#include "GoToGoal.h"

void initGotoGoal(double x,double y){
	goal.x=x;
	goal.y=y;
	E_k=0;
	e_k_1=0;
	pid.Kp=3;
	pid.Ki=0.04;//0.01;
	pid.Kd=0.03;//0.01;
	e=0;
	e1=0;
	e2=0;
	u=0;
	delta_u=0;
}	



double * gotoGoalExecute(double v){
	
	double k1= pid.Kp + pid.Ki + pid.Kd;
	double k2=-pid.Kp - 2*pid.Kd;
	double k3= pid.Kd;
	
	// distance between goal and robot in x-direction
	double u_x = goal.x-position.x;
	//distance between goal and robot in y-direction
	double u_y = goal.y-position.y;
		    
	//angle from robot to goal. Hint: use ATAN2, u_x, u_y here.
	double theta_g = atan2(u_y,u_x);
	if(theta_g<0)
	theta_g=2*M_PI+theta_g;
			
	//2. Calculate the heading error.
	double e_k = theta_g-position.theta;
	e_k =atan2(sin(e_k),cos(e_k)); // Put angle between  pi and  -pi
		
	
	e2 = e1; // update error variables
	e1 = e;
	e = e_k;		
	
	delta_u = k1*e + k2*e1 + k3*e2; // PID algorithm (3.17)
	
	u =u+ delta_u;	
		
	static double outVector[2];
	outVector[0]=v;
	outVector[1]=u;  // Angular Speed W
		
	#if DEBUG_UART==1
	printD("X%s\n",position.x);	
	printD("Y%s\n",position.y);	
	printD("theta_g%s\n",theta_g);	
	printD("theta%s\n",position.theta);		
	printD("deltau%s\n",delta_u);	
	printD("u%s\n",u);	
	printD("e2%s\n",e2);	
	printD("e1%s\n",e1);	
	printD("e%s\n",e);
	#endif	
	   
	return outVector;
}


double signG(double x){
	if (x > 0) return 1.0;
	if (x < 0) return -1.0;
	return 0;
}