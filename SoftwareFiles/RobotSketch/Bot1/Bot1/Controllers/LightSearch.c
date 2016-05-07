/*
 * LightSearch.c
 *
 * Created: 28/05/2015 7:43:49 p. m.
 * Author:  Andrés Rengifo at Universidad de los Andes
 * This work is licensed under a: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
 * http://creativecommons.org/licenses/by-nc-sa/4.0/
 */ 
#include "LightSearch.h"


int * lightSearchExecute(uint16_t lightRight, uint16_t lightLeft){
     
	  
	  int error=inputLayer(lightRight,lightLeft);
	  
	  
	  double *secondLayerOutputs=secondHiddenLayer(error);
	 
	  
	  
	  double *thirdLayerOutputs=thirdHiddenLayer(secondLayerOutputs[0],secondLayerOutputs[1]);

	  
	  double *outputs=outputLayer(thirdLayerOutputs[0],thirdLayerOutputs[1]);
	  
	  
	  #if DEBUG_UART==1
	  printf("error %i\n",error);
	  printD("SL1%s\n",secondLayerOutputs[0]);
	  printD("SL2%s\n",secondLayerOutputs[1]);
	  printD("TL1%s\n",thirdLayerOutputs[0]);
	  printD("TL2%s\n",thirdLayerOutputs[1]);
	  printD("O1%s\n",outputs[0]);
	  printD("O2%s\n",outputs[1]);
	  #endif
	  
	  
	  
	  int right=(int) outputs[0];
	  int left=(int) outputs[1];
	  
	  static int outVector[2];
	  outVector[0]=right;
	  outVector[1]=left;
	  
	  return outVector;
}

int inputLayer(int d1, int d2){
	int W11=1;
	int W12=-1;
	
	return d1*W11+d2*W12; //Linear activation Function y=x	
}

double * secondHiddenLayer(int d){
	 double W21=smooth;
	 double W22=smooth;
	 double b21=-5;
	 double b22=5;
	 
	 double x1=W21*d+b21;
	 double x2=W22*d+b22;
	 
	 double top= logisticSigmoidalFcn(x1);
	 double bottom= logisticSigmoidalFcn(x2);
	
	
	 static double outVector[2];
	 outVector[0]=top;
	 outVector[1]=bottom;
	 
	 return outVector;
}

double * thirdHiddenLayer(double d1, double d2){
	double W31=-(halfPoint-minSpeed);
	double W32=-(halfPoint-minSpeed);
	double b31=0; 
	double b32=topSpeed-halfPoint;
	
	double top=W31*d1+b31;      //Linear activation Fcn
	double bottom=W32*d2+b32;   //Linear activation Fcn
	
	static double outVector[2];
	outVector[0]=top;
	outVector[1]=bottom;
	
	return outVector;
	
}

double * outputLayer(double d1,double d2){
	//Motor Right Output
	double W1=1;
	double W2=1;
	double b1=halfPoint;	
	double right=(W1*d1+W2*d2)+b1; //Linear activation Fcn
	
	
	//Motor Left Output
    double W3=-1;
	double W4=-1;
	double b2=halfPoint;	
	double left=(W3*d1+W4*d2)+b2; //Linear activation Fcn
	
	static double outVector[2];
	outVector[0]=right;
	outVector[1]=left;
	
	return outVector;
}

double logisticSigmoidalFcn(double x){
	return 1/(1+pow(M_E,-x));
}

