/*
 * Dynamics.h
 *
 * Created: 20/02/2015 03:23:39 p.m.
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

#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "../Outputs/UART.h"

#ifndef DYNAMICS_H_
#define DYNAMICS_H_


struct Physics{
	double L;
	double R;
	uint8_t ticks_per_rev;
}physics;

struct Pose
{
	double  x;
	double  y;
	double theta;
} position;

struct Point
{
	double  x;
	double  y;
};


void dynamics_update_pose(uint8_t *newTicksRight,uint8_t *newTicksLeft);
void dynamics_update_pose_from_camera(uint8_t *newPosition);
double * dynamics_uni_to_diff(double v, double w);
double * dynamics_diff_to_uni(double r, double l );
void initDynamics(double x, double y, double theta);
double rad2deg(double rad);
double fixAngle(double angle);




#endif /* DYNAMICS_H_ */