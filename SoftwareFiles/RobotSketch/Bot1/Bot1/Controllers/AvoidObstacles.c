/*
 * AvoidObstacles.c
 *
 * Created: 30/05/2015 7:16:24 p. m.
 * Author:  Andrés Rengifo at Universidad de los Andes
 * This work is licensed under a: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
 * http://creativecommons.org/licenses/by-nc-sa/4.0/
 */
#include "AvoidObstacles.h"

double error=0;
double errorDot=0;

void initAvoidObstacles(void){
	initIRSensors();
	
}


double avoidObstaclesExecute(double desiredHeading){
	 double pastError=error;
	 double g1=1/(M_PI/5);
	 double g2=1/(M_PI/5); 
	 double g0=W_MAX;
	 
	 error=-desiredHeading*g1;
	 errorDot=(pastError-error)*g2;//normalize
	 
	
	 double* eMF=computeErrorMembershipFcn(error);
	 double* e_dotMF=computeErrorDotMembershipFcn(errorDot);
	 
	 #if DEBUG_UART==1
	 printD("h%s ",error);
	 printD("ed%s \n",errorDot);
	 
	 printf("EMF");
	 for (uint8_t i=0;i<MEMBER_ERROR;i++)
		 printD("%s ",eMF[i]);
	 
	 printf("\n");	 
	 printf("E_dotMF");
	 for (uint8_t i=0;i<MEMBER_ERROR_DOT;i++)
	 printD("%s ",e_dotMF[i]);
	 
	 printf("\n");
	 #endif
	 
	 
	 double * wInterference=interference(computeErrorMembershipFcn(error),computeErrorDotMembershipFcn(errorDot));	
	 
	 double w=deFuzzyfication(wInterference)*g0;
	 
	 #if DEBUG_UART==1
	 printD("w%s\n",w);
	 #endif
		 
	 return w;	 
}


double * computeErrorMembershipFcn(double error){
	struct MFCN negbig={0.6667,-0.6667,0};  //trapezoid
    struct MFCN negsmall={0.6667,-0.3333,1};
	struct MFCN zero={0.6667,0,2};
	struct MFCN possmall={0.6667,0.3333,3};
    struct MFCN posbig={0.6667,0.6667,4};   //trapezoid 
	
	struct MFCN memberShipsFcn[MEMBER_ERROR];
	
	memberShipsFcn[0]=negbig;
	memberShipsFcn[1]=negsmall;
	memberShipsFcn[2]=zero;
	memberShipsFcn[3]=possmall;
	memberShipsFcn[4]=posbig;
	
    
	static double out[MEMBER_ERROR];
	
	for (uint8_t i=0;i<MEMBER_ERROR;i++)out[i]=0;
	
	
	if(error<negbig.center){				
		out[negbig.number]=1;		 
		return out;
	}
	else if(error>posbig.center){				
		out[posbig.number]=1;		
		return out;
	}
	else{
		for (uint8_t i=0;i<MEMBER_ERROR;i++){
			double u=triangularFcn(error,memberShipsFcn[i].w,memberShipsFcn[i].center);
			out[i]=u;
		}
	}
	
	
	return out;

		
	
}


double * computeErrorDotMembershipFcn(double errorDot){
	struct MFCN negbig={0.8,-1,0}; 
	struct MFCN negmed={0.8,-0.6,1}; 
	struct MFCN negsmall={0.8,-0.2,2};
	struct MFCN zero={0.4,0,3};
	struct MFCN possmall={0.8,0.2,4};
	struct MFCN possmed={0.8,0.6,5};
	struct MFCN posbig={0.8,1,6};  
		
	
	struct MFCN memberShipsFcn[MEMBER_ERROR_DOT];
	
	memberShipsFcn[0]=negbig;
	memberShipsFcn[1]=negmed;
	memberShipsFcn[2]=negsmall;
	memberShipsFcn[3]=zero;
	memberShipsFcn[4]=possmall;
	memberShipsFcn[5]=possmed;
	memberShipsFcn[6]=posbig;
	
	
	static double out[MEMBER_ERROR_DOT];
	
	
	for (uint8_t i=0;i<MEMBER_ERROR_DOT;i++){
		double u_premise=triangularFcn(errorDot,memberShipsFcn[i].w,memberShipsFcn[i].center);
		out[i]=u_premise;
	}
	
	
	
	return out;

}


double * interference(double * error, double * errorDot){
	
	int RuleTable[MEMBER_ERROR][MEMBER_ERROR_DOT]={
		{6,6,6,5,4,3,2},
		{6,6,5,4,3,2,1},
		{6,5,4,3,2,1,0},
		{5,4,3,2,1,0,0},
		{4,3,2,1,0,0,0},
		};
   
   double num=0;
   double den=0;
	
   double centers[MEMBER_W]={-1,-0.6,-0.2,0,0.2,0.6,1};
	
		
	for (uint8_t i=0;i<MEMBER_ERROR;i++){
		for (uint8_t j=0;j<MEMBER_ERROR_DOT;j++){
			if(error[i]!=0 && errorDot[j]!=0){  
				int idx=RuleTable[i][j];
				double premise=min(error[i],errorDot[j]);
				num=num+centers[idx]*premise;  //using 1/2wh Area
				den=den+premise;
			}
		}
	}
	
	static double out[2];
	out[0]=num;
	out[1]=den;
	
	return out;
}


double deFuzzyfication(double * wInterference){
	
	double w_crisp=wInterference[1]==0?0:wInterference[0]/wInterference[1];	
	return w_crisp;
	
}


double triangularFcn(double x,double w,double center){
	double y=max(1-(2/w)*fabs(x-center),0);	  //Triangular Fcn
	return y;
}


