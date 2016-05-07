/* main.c
*
* Created: 26/09/2014 12:43:27 p.m.
* Author:  Andrés Rengifo at Universidad de los Andes 
* This work is licensed under a: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* http://creativecommons.org/licenses/by-nc-sa/4.0/
*/


#include "main.h"
//-------------Communication Buffers--------------------
uint8_t bufferout[NRF24L01_PAYLOAD];
uint8_t bufferin[NRF24L01_PAYLOAD];
//-----------------------------------------------------

//-------------Rx/Tx address-------------------------
static uint8_t addTx_1[NRF24L01_ADDRSIZE] =  ADD_TX_1;
static uint8_t addTx_start[NRF24L01_ADDRSIZE] = NRF24L01_ADDRP0;
static uint8_t addRx_1[NRF24L01_ADDRSIZE] =  NRF24L01_ADDRP1;
//-----------------------------------------------------

//----------------FLags--------------------------------
volatile bool flagStart=false;
volatile bool flagGps=false;
//-----------------------------------------------------

//-----------------Linear Speed-------------------------------
double v=0.035;
//-----------------------------------------------------

/*--------------------MAIN FUNCTION-------------------------------------*/
int main(void){	
	
	init();		 //Initialize all required peripherals	
    
    
    //Run continuously 
    while(1){
		
			
		while(flagStart){
        /*The flagStart is true, use this block to perform the robot actions and apply controllers
		
		Example1: Move Robot Forward
		set_color(COLOR_GREEN);   //Set the RGB led to  color (also available: COLOR_GREEN, COLOR_BLUE, COLOR_RED, COLOR_CYAN, COLOR_MAGENTA, COLOR_YELLOW, COLOR_WHITE, and COLOR_OFF)
		motorRight(50);   // Set the motor speed to any value between 0-99
		motorLeft(50);	
		-----------------------------------------------------------------------------------------------------------------
		Example 2: Go to goal behaviour
		dynamics_update_pose_from_camera(bufferin);    //Update  the actual position information over bufferin
		double *controller=gotoGoalExecute(v);        //Obtain the controller action W (*controller)
		supervisor_execute(controller);               //Execute the new angular speed (W) applying a certain PWM to motors
		-----------------------------------------------------------------------------------------------------------------
		Example 3: Light Search Behaviour (Light search module required over the expansion socket)
	    uint16_t lightRight=AnalogToDigital_getAverage(ADC4_RIGHT);  //Get the ADC values for each light sensor 
	    uint16_t lightLeft=AnalogToDigital_getAverage(ADC5_LEFT);
	     
		 //Choose one of the two controllers inputs: ligth sensors values, output: Motor PWM values
	     int * motorOutputs=lightSearchExecuteMLP(lightRight,lightLeft);
	     int * motorOutputs=lightSearchExecuteOF(lightRight,lightLeft);
		 
		 //Send values to motors
	     int rightMotor=motorOutputs[0];
	     int leftMotor=motorOutputs[1];
		 motorRight(rightMotor);
		 motorLeft(leftMotor);
		-----------------------------------------------------------------------------------------------------------------
		Example4: Using AvoidOsbtacles Controller 
			double h=IRSensorsGetAvoidVectorHeading();  //Obtain the desired heading
			double u[2];                                //Save  the linear (V) and angular (u[1]=W) speed
			u[0]=v;         
			u[1]=avoidObstaclesExecute(h);              //Apply the controller (Input: the desired heading. Output: The new angular speed).
			supervisor_execute(u);                      //Execute the new angular speed (W) applying a certain PWM to motors.
		
		*/
		/*---------------------Start your code Here------------------------*/	
	
		/*-----------------------------------------------------------------*/
	
	   }
		
       /*The flagStart is false, use this block to stop the robot
		
		Example: Stop Robot
		set_color(COLOR_WHITE);   //Set the RGB led to white color
		motorLeft(0);             // Set the speed of each motor to 0
		motorRight(0);		
		*/
	   
		//-------------------------Write Your Code Here--------------------------------_
		
		
		//------------------------------------------------------------------------------
		
		
		
	}

	return 0;
}


/*
* Initialization method
* Start all the peripherals needed for you application
*/
static void init(){		
		
		initLedRGB(); //Enable Led RGB Functions		
		initUART();	  //Enable Uart debugging mode
		
		//Disable ~SS pin for SPI functions		    
		DDRB |= (1 << DDB2);    
		
		//--------------------------------setup output/input buffers------------------------------------------------
		for(uint8_t i=0; i<sizeof(bufferout); i++)
		bufferout[i] = NODE_NUMBER;
		
		for(int i=0; i<sizeof(bufferin); i++)
		bufferin[i] = 0;    
	   
		nrf24l01_init();                        //Init Wireless Module		
		nrf24l01_settxaddr(addTx_start);       //Setup address to send Data (Next Node)
	    //------------------------------------------------------------------------------------------------------------------
				
		sei();  // Enable Global Interrupts
        
		initMotors();   // Init motors
		
		//--------------------------Init the desired Controller options:  initAvoidObstacles(), initGotoGoal(goalx,goaly) 
	     
		//-----------------------------------------------------------
		
		//Set the initial position and heading
		initDynamics(0, 0, 0);
     
	    
}



/* --------------Interrupt for incoming message------------------- 
 Change the robot Address in /Wireless/nodesAdress.h	
 To understand the Communications topologys see the NRF24L01 module datasheet in:
 
*/
ISR(INT0_vect){	  
	
		uint8_t pipe=0xFF;
		nrf24l01_readready(&pipe);	 //Read the pipe of the incomming message            		
		
		
		nrf24l01_read(bufferin);	 //Read the RXbuffer
		
		/*---------------------------------------------------------------------
		        Perform any action depends on the incomming pipe
		pipe0: Use as a broadcast to start and stop command from CentralController
		pipe1: Use as a GPS to overhead camera positioning system
		pipe2: Any other purpose
		-----------------------------------------------------------------------*/
		
		if(pipe==0){ 
			
			flagStart=false;
			
			if(bufferin[0]==CMD_START)
			flagStart=true;
			
			
		}	
		
		if(pipe==1)
		flagGps=true;
		else if(pipe==2){
			
		}
			
		
}


