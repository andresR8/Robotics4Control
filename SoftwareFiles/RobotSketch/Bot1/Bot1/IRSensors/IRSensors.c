/*
 * IRSensors.c
 *
 * Created: 11/02/2015 03:52:59 p.m.
 * Author:  Andrés Rengifo at Universidad de los Andes
 * This work is licensed under a: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
 * http://creativecommons.org/licenses/by-nc-sa/4.0/
 */
#include "IRSensors.h"
#include "adc.h"


double sensors[MAX_SENSORS]={0,0,0,0,0};
double distance[MAX_SENSORS];
double geometry_Xs[MAX_SENSORS]={-3.2512,-2.4892,0,2.4892,3.2512};
double geometry_Ys[MAX_SENSORS]={2.794,4.826,5.9994,4.826,2.794};
double geometry_Hs[MAX_SENSORS]={M_PI,3*M_PI_4,M_PI_2,M_PI_4,0};

//Channels for each IR sensor to ADMUX setting
double muxChannels[5] = {CH_S1, CH_S2, CH_S3, CH_S4, CH_S5};

void initIRSensors(void){
	initAdc();
	DDRD|=(1<<IR_EMITTER);              //set PD0 as output for IR emitters	
	
}

double * IRreadRaw(void){
	double temp[AVG_MESUREMENTS];
	
	for (int i=0; i<MAX_SENSORS;i++)      // Scan for each channel
	{
		for(int j=0;j<AVG_MESUREMENTS;j++)
		temp[j]=readAdc(muxChannels[i]);  //Take AVG_MESUREMENTS mesurements
		
		sensors[i]=average(temp);         //Average for each sensor
	}
	
	return sensors;	
}

double * IRSensorsGetDistance(void){
	PORTD|=(1<<IR_EMITTER);//Turn On the IR_EMITTER
	//Power Linealization
	double a[MAX_SENSORS]={89.31,104,368.9,380,124.6};
	double b[MAX_SENSORS]={-0.5107,-0.6161,-0.7247,-0.8061,-0.6311};
    //double offsets[MAX_SENSORS]={4,6.7,22.8,25.3,6};
    //double min[MAX_SENSORS]={11,10,42,30,12};
	IRreadRaw();
	
	
	for (int i=0; i<MAX_SENSORS;i++){    // Scan for each channel
	  distance[i]=a[i]*pow(sensors[i],b[i]);
	  if(distance[i]>=25)
	  distance[i]=25;
	}
	
	
	
	return distance;
}

double IRSensorsGetAvoidVectorHeading(void){
	
	 IRSensorsGetDistance();
	 
	 double x[MAX_SENSORS];
	 double y[MAX_SENSORS];
	 
	 double x_g=0;
	 double y_g=0;
	 
	 
	 for (uint8_t i=0; i<MAX_SENSORS;i++){    
		 
		 x[i]=distance[i]*cos(geometry_Hs[i])+geometry_Xs[i];
		 y[i]=distance[i]*sin(geometry_Hs[i])+geometry_Ys[i];	
		 
		 x_g=x_g+x[i];	
		 y_g=y_g+*(y+i);	 		 
		 
	 }
	 
	 
	
	 
	 double theta_g=atan2(y_g,x_g)-M_PI_2;
	 
	 return theta_g;
}

double average(double a[]){
	int i;
	double avg, sum=0.0;
	
	for(i=0;i<AVG_MESUREMENTS;i++){
		sum+=a[i];
	}
	avg =(sum/AVG_MESUREMENTS);
	return avg;
}

