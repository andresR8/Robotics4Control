/*
 * Dynamics.c
 *
 * Created: 20/02/2015 03:24:02 p.m.
 * Author: Universidad de los Andes Designed by: Andrés Rengifo
 * This work is licensed under a: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
 * http://creativecommons.org/licenses/by-nc-sa/4.0/
 *-----------------------------------------------------------------------------------------------------------------
 * Functions:  dynamics_update_pose
 *			   dynamics_uni_to_diff
 *		       dynamics_diff_to_uni
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

#include "Dynamics.h"



void initDynamics(double x, double y, double theta){
	position.x=x;        //Init de Init Position Of the Robot
	position.y=y;
	position.theta=theta;
	physics.L=0.055235;                  //55.235mm
	physics.R=0.0004;                    //0.4mm
	physics.ticks_per_rev=2;
}


void dynamics_update_pose(uint8_t *newTicksRight,uint8_t *newTicksLeft){	
	 
	 uint8_t ticksRight = *newTicksRight;
	 uint8_t ticksLeft  = *newTicksLeft;
	 
	 //Reset the tick count
	 *newTicksRight=0;
	 *newTicksLeft=0;


	 double m_per_tick = (2*M_PI*physics.R)/physics.ticks_per_rev;
	 
	 double d_right =ticksRight*m_per_tick;
	 double d_left = ticksLeft*m_per_tick;
	 
	 double d_center =(d_right + d_left)/2;
	 double phi = (d_right - d_left)/physics.L;
	 
	 double theta_new =fixAngle(position.theta + phi);	 
	 double x_new = position.x + d_center*cos(position.theta);
	 double y_new = position.y + d_center*sin(position.theta);
	  
	  // Update your estimate of (x,y,theta)
	  position.x=x_new;
	  position.y=y_new;
	  position.theta=theta_new; 
}

void dynamics_update_pose_from_camera(uint8_t *newPosition){
	
	struct Point front,center,translate,originX;        
	
	
	center.x=(uint16_t)(newPosition[0]<<8|newPosition[1]);
	center.y=(uint16_t)(newPosition[2]<<8|newPosition[3]);
	front.x =(uint16_t)(newPosition[4]<<8|newPosition[5]);
	front.y =(uint16_t)(newPosition[6]<<8|newPosition[7]);
	
	/*
	for (uint8_t i=0;i<8;i++)
	printf("0x%x\n",newPosition[i]);
	
	
	printD("cx %s  ",center.x);	
	printD("cy %s  ",center.y);	
	printD("fx %s  ",front.x);	
	printD("fy %s  \n",front.y);*/
	 
	 translate.x=front.x-center.x;
	 translate.y=front.y-center.y;
	 
	 double norm=sqrt(pow(translate.x,2)+pow(translate.y,2));
	 //Normalize Vector	
	 translate.x=translate.x/norm;
	 translate.y=translate.y/norm;
	 originX.x=1;
	 originX.y=0;
		
	 
	 double dot = originX.x*translate.x + originX.y*translate.y;    // dot product
	 double det = originX.x*translate.y - originX.y*translate.x;    // determinant
	 double heading = atan2(det, dot);
	 
	 if(heading<0)
	   heading=(2*M_PI)+heading;
	 	 
	  #if DEBUG_UART==1
       printD("h %s \n",rad2deg(heading));
      #endif
	 	
	
	  // Update your estimate of (x,y,theta)
	  position.x=center.x;
	  position.y=center.y;
	  position.theta=heading;
}

double * dynamics_uni_to_diff(double v, double w){
 
 static double vector_vel[2];
 vector_vel[0] = (2*v+(w*physics.L))/(2*physics.R);
 vector_vel[1] = (2*v-(w*physics.L))/(2*physics.R);
 
 return vector_vel;
 
}

double * dynamics_diff_to_uni(double r, double l ){

	double v = (physics.R/2)*(r+l);
	double w = (physics.R/physics.L)*(r-l);
	static double vw_vector[2];
	vw_vector[0]=v;
	vw_vector[1]=w;
	
	return vw_vector; 
}
//Necessary Math Functions

double rad2deg(double rad)
{
	return (180.0 * rad / (M_PI));
}

double fixAngle(double angle){
	
	    double angle_pi=angle/M_PI;
	    double temp_angle=angle_pi-floor(angle_pi);
				
		temp_angle=(int)floor(angle_pi)%2 ? (1-temp_angle)*(-M_PI) : temp_angle*M_PI;	 // Is Odd cuadrants 3 or 4	 Is Even cuadrants 1 or 2		
		 
		return temp_angle;		 
		 
}