/*
 * Supervisor.h
 *
 * Created: 24/02/2015 06:51:11 p.m.
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
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "../Odometry/Dynamics.h"
#include "../Driver/Motors.h"
#include "../Outputs/UART.h"
#include "GoToGoal.h"


#ifndef SUPERVISOR_H_
#define SUPERVISOR_H_



#define V_MIN  70//130  295.4
#define V_MAX  280//400//450
#define W_MAX  (physics.R/physics.L)*(V_MAX-V_MIN)
#define D_STOP 30

double * supervisor_limit_speeds(double *inputs_vrvl);
int * supervisor_velToPwm(double *inputs_vrvl);
double * supervisor_ensureW(double *inputs_vw);
void supervisor_execute(double *inputs_vw);
bool supervisorAtGoal();

double sign(double x);
double max(double x,double y);
double min(double x,double y);
double norm(double *vector);
#endif /* SUPERVISOR_H_ */