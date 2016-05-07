/*
 * Supervisor.c
 *
 * Created: 24/02/2015 06:51:59 p.m.
 * Author:  Andrés Rengifo at Universidad de los Andes
 * This work is licensed under a: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
 * http://creativecommons.org/licenses/by-nc-sa/4.0/
 *-----------------------------------------------------------------------------------------------------------------
 * Functions:  supervisor_limit_speeds
 *			    supervisor_ensureW
 *		        supervisor_velToPwm
 * Are based on MOOC control of mobile robots: Copyright (c) 2013, Georgia Tech Research Corporation All rights reserved.
 *------------------------------------------------------------------------------------------------------------------
 */

/*
Copyright (c) 2013, Georgia Tech Research Corporation
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
* Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
* Neither the name of the Georgia Institute of Technology, Georgia Tech
Research Corporation nor the names of its contributors may be used to
endorse or promote products derived from this software without specific
prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTOR BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/


#include "Supervisor.h"
#define STRINGIFY(s) XSTRINGIFY(s)
#define XSTRINGIFY(s) #s





double * supervisor_limit_speeds(double *inputs_vrvl){
	double vel_r=*inputs_vrvl;
	double vel_l=*(inputs_vrvl+1);
	
	// actuator hardware limits
	double vel_r_out = max(min(vel_r, V_MAX), -V_MAX);
	double vel_l_out = max(min(vel_l, V_MAX), -V_MAX);
	
	
	if(fabs(vel_r_out) <= V_MIN)
	vel_r =sign(vel_r_out)* V_MIN;
	
	if(fabs(vel_l_out) <= V_MIN)
	vel_l_out =sign(vel_l_out)* V_MIN;
	
	if(vel_l_out==0)vel_l_out=V_MIN;
	if(vel_r_out==0)vel_r_out=V_MIN;
	
	static double vel_vector[2];
	vel_vector[0]=vel_r_out;
	vel_vector[1]=vel_l_out;	
	
	#if DEBUG_UART==1	
	printD("vel_r%s\n",vel_r);	
	printD("vel_l%s\n",vel_l);	
	printD("vel_r_out%s\n",vel_r_out);	
	printD("vel_l_out%s\n",vel_l_out);	
	printD("vel_r_out%s\n",vel_r_out);	
	printD("vel_l_out%s\n",vel_l_out);
	#endif
	
	return vel_vector;
}

int * supervisor_velToPwm(double *inputs_vrvl){
	
	
	double *vel_vector=supervisor_limit_speeds(inputs_vrvl);
	
    double right_rps = *vel_vector;
    double left_rps = *(vel_vector+1);
		
	
	double m=  6.2044;
	double b=  -64.4954;	
	
	double right_pwm = sign(right_rps)*(fabs(right_rps)-b)/m;
	double left_pwm = sign(left_rps)*(fabs(left_rps)-b)/m;	
	
	static int pwm_vector[2];
	pwm_vector[0]= (int)max(min(right_pwm, 100), -100);
	pwm_vector[1]= (int)max(min(left_pwm, 100), -100);
	
	#if DEBUG_UART==1	
		printD("right_rps%s\n",right_rps);
		printD("left_rps%s\n",left_rps);
		printD("right_pwm%s\n",right_pwm);
		printD("left_pwm%s\n",left_pwm);
	#endif

	
	return pwm_vector;
	
}

double * supervisor_ensureW(double *inputs_vw){
	 
// 	 This function ensures that w is respected as best as possible
// 	 by scaling v.
	 double v=*inputs_vw;	 
	 double w=*(inputs_vw+1); 
	 
	 double R = physics.R;
	 double L = physics.L;
	 double vel_r=0;
	 double vel_l=0;	 
	 
	 
	 if(fabs(v) > 0){
/*	 1. Limit v,w to be possible in the range [vel_min, vel_max]
	 (avoid stalling or exceeding motor limits)*/
	 double v_lim =max(min(fabs(v), R*V_MAX), R*V_MIN);		 
	 double w_lim =max(min(fabs(w), (R/L)*(V_MAX-V_MIN)), 0);
		 
	 /*2. Compute the desired curvature of the robot's motion*/	 
	double *vector_vel = dynamics_uni_to_diff(v_lim, w_lim); 
	
	double vel_r_d=*vector_vel;
	double vel_l_d=*(vector_vel+1);
  
	 
    /*3. Find the max and min vel_r/vel_l*/
	 double vel_rl_max =max(vel_r_d, vel_l_d);
	 double vel_rl_min =min(vel_r_d, vel_l_d);
	 
	 
	/*Shift vel_r and vel_l if they exceed max/min vel*/
	       
			 if (vel_rl_max > V_MAX){
				 vel_r = vel_r_d - (vel_rl_max-V_MAX);
				 vel_l = vel_l_d - (vel_rl_max-V_MAX);
			 }
			 else if(vel_rl_min < V_MIN){
			     vel_r = vel_r_d + (V_MIN-vel_rl_min);
				 vel_l = vel_l_d + (V_MIN-vel_rl_min);
			 }
			 else{
				 vel_r = vel_r_d;
				 vel_l = vel_l_d;
			 }


	      //Fix signs (Always either both positive or negative)
		 double *vw_shift_vector = dynamics_diff_to_uni(vel_r, vel_l);
	 	 v = sign(v)* (*vw_shift_vector);
	 	 w = sign(w)* (*(vw_shift_vector+1));	 
		 
		#if DEBUG_UART==1
		printD("W%s\n",*(inputs_vw+1));		
		printD("W_lim%s\n",w_lim);		
		printD("v_lim%s\n",v_lim);			
		printD("vel_r_d%s\n",vel_r_d);		
		printD("vel_l_d%s\n",vel_l_d);		
		printD("vv%s\n",v);		 			
		printD("ww%s\n",w);
		#endif
		
	 }	 
	 else{
/*	 Robot is stationary, so we can either not rotate, or
	rotate with some minimum/maximum angular velocity*/
			 double w_min = R/L*(2*V_MIN);
			 double w_max = R/L*(2*V_MAX);
			 
			 if (fabs(w) > w_min)
			 w = sign(w)*max(min(abs(w), w_max), w_min);
			 else
			 w = 0;
	 
	 }
	double *vrvl_vector =dynamics_uni_to_diff(v,w);
	
	#if DEBUG_UART==1
	printD("vvv%s\n",v);		
	printD("www%s\n",w);
    #endif	

	return vrvl_vector;

}

void supervisor_execute(double *inputs_vw){

	
	double *vrvl_vector=supervisor_ensureW(inputs_vw);
		 
	int *pwm_vector=supervisor_velToPwm(vrvl_vector);
    
	#if DEBUG_UART==0
	printf("r%i   l%i\n",*pwm_vector,*(pwm_vector+1));
    #endif
		
	
	
	motorRight(*pwm_vector);
	motorLeft(*(pwm_vector+1));
}

double sign(double x){
	if (x > 0) return 1.0;
	if (x < 0) return -1.0;
	return 0;
}

double max(double x,double y){
	if (x > y) return x;
	if (y > x) return y;
	return x;
}

double min(double x,double y){
	if (x < y) return x;
	if (y < x) return y;
	return x;
}

bool supervisorAtGoal(){
	 bool resp = false;
	 
	 // Test distance from goal
	 double vector[2];
	 vector[0]=position.x-goal.x;
	 vector[1]=position.y-goal.y;
		
	 if (norm(vector) < D_STOP)
	 resp = true;
	 
	 return resp;	 
	 
}

double norm(double *vector){
	double x=*vector;
	double y=*(vector+1);
	return (double)sqrt(pow(x,2)+pow(y,2));
}