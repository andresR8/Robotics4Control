package uniandes.iee.markerDetector;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.SecondaryLoop;

import uniandes.iee.hardware.Robot;

import java.awt.image.BufferedImage;
import java.io.ByteArrayInputStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

import javax.imageio.ImageIO;

import org.opencv.core.Core;
import org.opencv.core.CvType;
import org.opencv.core.Mat;
import org.opencv.core.MatOfByte;
import org.opencv.core.MatOfPoint;
import org.opencv.core.MatOfPoint2f;
import org.opencv.core.Point;
import org.opencv.core.Rect;
import org.opencv.core.Size;
import org.opencv.gpu.Gpu;
import org.opencv.highgui.Highgui;
import org.opencv.highgui.VideoCapture;
import org.opencv.imgproc.Imgproc;
import org.opencv.photo.Photo;

import uniandes.iee.CentralController;
import uniandes.iee.CentralControllerUI;

import org.opencv.core.Scalar;

public class MyCam {
	 private DaemonThread myThread = null;
	 private   int count = 0;
	 private   VideoCapture camera;

	 private double H_MIN,H_MAX, S_MIN,S_MAX, V_MIN, V_MAX;
	 
	 private int[][] HSV = {{208,161,51,0,0,25}, //H_MIN
			 {240,180,87,27,280,337},  //H_MAX
			 {83,197,33,107,193,120}, //S_MIN
			 {183,253,217,180,403,380}, //S_MAX
			 {150,100,173,143,107,123},  //V_MIN
			 {290,133,270,240,177,500}}; //V_MAX
	 
	 private static double AREAMAX_THRESHOLD=200000;
	 private static double AREAMIN_THRESHOLD=70;
	 //private ArrayList<Robot> robots;
	 private CentralController controller;
	 
	 private ArrayList<Mat> filters = new ArrayList<Mat>();
	 
	 
	 private int channel=0;	
     private int numChannels=4;	 


	
    public static final int FILTER_NO=0,FILTER_HSV=1,FILTER_CLOSE=2,FILTER_ERODE=3;
    private int flagFilter=FILTER_NO;
	public boolean debug=true;
	 
	public void setDebug(boolean debug) {
		this.debug = debug;
	}

	// private MyMarkerDetector markerDetector;
	 public static int FRAME_WIDTH = 640;
	 public static int FRAME_HEIGHT = 480;
	 
	 
    public MyCam(CentralControllerUI gui,CentralController controller){			 
	    myThread = new DaemonThread(gui);	
	 	H_MIN=(double)HSV[0][channel];
		H_MAX=(double)HSV[1][channel];
		S_MIN=(double)HSV[2][channel];
		S_MAX=(double)HSV[3][channel];
		V_MIN=(double)HSV[4][channel];
		V_MAX=(double)HSV[5][channel];
		this.controller=controller;
		
	     
   }	

	public void startCamera(int source){		
		   camera=new VideoCapture(source);
		   System.out.println("cam source"+source);
		   
		   
		   Thread t = new Thread(myThread);
		   t.setDaemon(true);
		   myThread.runnable = true;
		   t.start(); 
	   }
	   
	public void stopCamera(){
		   myThread.runnable = false;                   
           camera.release();
	}
	   
class DaemonThread implements Runnable  {
	    protected volatile boolean runnable = false;
	    protected Graphics g;
	    protected CentralControllerUI gui;
	    	 
	    
	    public DaemonThread(CentralControllerUI gui){
	    	this.g=gui.getJpanel().getGraphics();
	    	this.gui=gui;
	    } 
	    
	    @Override
	    public  void run() {
	    	synchronized(this)
	    	{
	    		while(runnable)
	    		{
	    			if(camera.grab())
	    			{
	    				try
	    				{
	    					
	    					 
	    					 Mat frame = new Mat();
	    					 MatOfByte mem = new MatOfByte();
	    					 
	    					 //long startTime = System.currentTimeMillis();
	    					 //System.out.println(startTime);
	    					 camera.retrieve(frame);	    			
	    					//camera.read(frame);
	    					 
	    					 
	    					// frame.convertTo(frame, -1, 1, 40);
	    					//frame.convertTo(frame, -1, 0.5, 0); //increase the contrast (double)
	    					 
	    					  double angle = ((180 / 90) % 4) * 90;
                              
	    					   //0 : flip vertical; 1 flip horizontal
	    					   int  flip_horizontal_or_vertical = angle > 0 ? 1 : 0;
	    					   int  number =(int) Math.abs(angle / 90);          

	    					   for(int i = 0; i != number; ++i){
	    					       Core.transpose(frame, frame);
	    					       Core.flip(frame, frame, flip_horizontal_or_vertical);
	    					   }
	    					   
	    					   
	    					 
	    					
	    	                
	    					Mat filter=new Mat();
	    					Imgproc.cvtColor(frame,filter,Imgproc.COLOR_BGR2HSV_FULL);		    					
	    					Core.inRange(filter, new Scalar(H_MIN,S_MIN,V_MIN),new Scalar(H_MAX,S_MAX,V_MAX),filter);
	    					
	    					
	    					
	    					Mat kernel = Imgproc.getStructuringElement(Imgproc.MORPH_ELLIPSE, new Size(19,19));
	    					Mat closed = new Mat(); // closed will have type CV_32F
	    					Imgproc.morphologyEx(filter, closed, Imgproc.MORPH_CLOSE, kernel);	    					
	    					Core.divide(closed, closed, closed, 1, CvType.CV_32F);
	    					Core.normalize(closed, closed, 0, 255, Core.NORM_MINMAX, CvType.CV_8U);
	    					Imgproc.threshold(closed, closed, -1, 255, Imgproc.THRESH_BINARY_INV
	    							+Imgproc.THRESH_OTSU); 
                            
	    					Mat erode=new Mat();
	    					Imgproc.erode(closed, erode, Imgproc.getStructuringElement(Imgproc.MORPH_ELLIPSE,  new org.opencv.core.Size (8,8)));
	    					Imgproc.dilate(erode, erode, Imgproc.getStructuringElement(Imgproc.MORPH_RECT, new Size(4,4)));
	    					
	    					
	    						    					
	    					if(flagFilter==FILTER_NO){
	    						ArrayList<Robot> robots=new ArrayList<Robot>();
	    						for (int i = 0; i < numChannels; i++){	    						   
	    						   Robot r=detectRobot(i,frame);	    						   
				                   robots.add(i,r);
				                   
				                   if(r!=null && debug){
				                   //Core.putText(frame, "H "+ r.getHeading(), new Point(100,100),1,1,new Scalar(0,0,0),2);
				                	   System.out.println(r.getHeading());
				                	   System.out.println("x "+r.getCenter().x+"y "+r.getCenter().y);
				                	   
				                	   Core.circle(frame,new Point( r.getFront().x,640-r.getFront().y), 10, new Scalar(255,0,0));
				                   }
				                   
	    						}
	    						
	    						
	    						
	    						controller.sendRobots(robots,debug);
    							robots.clear();
	    						filters.clear();
	    						
	    						
	    						
	    						if(debug){
	    							//drawObject(500, 0, frame); //INIT
	    							drawObject(200, 300, frame); //GOAL
	    							
		    						drawObject(0, 480, frame);
		    						
	    						}
	    						Highgui.imencode(".bmp", frame, mem);
	    					}
	    					else if(flagFilter==FILTER_HSV)
	    						Highgui.imencode(".bmp", filter, mem);
	    					else if(flagFilter==FILTER_CLOSE)
	    						Highgui.imencode(".bmp", closed, mem);
	    					else if(flagFilter==FILTER_ERODE)
	    						Highgui.imencode(".bmp", erode, mem);
	    					
	    					
	    					
	    					Image im = ImageIO.read(new ByteArrayInputStream(mem.toArray()));
	    					BufferedImage buff = (BufferedImage) im;  
	    					
	    					if(debug)
	    					if (g.drawImage(buff, 0, 0, gui.getWidth()-50, gui.getHeight()-200 , 0, 0, buff.getWidth(), buff.getHeight(), null));
                           
	    					System.nanoTime();
	    					
	    						if(runnable == false)
	    						{
	    							System.out.println("Going to wait()");
	    							this.wait();
	    						}
	    				  
	    						//long estimatedTime = System.currentTimeMillis() - startTime;
	    						//System.out.println("TIME"+estimatedTime);
	    						
	    				}
	    				catch(Exception ex)
	    				{
	    					System.out.println("Error " +ex.getMessage());
	    				}
	    			}
	    		}
	    	}
	    }
 
        
	 
}




public Robot detectRobot(int channel, Mat frame){
			filters.add(new Mat());
			Imgproc.cvtColor(frame,filters.get(channel),Imgproc.COLOR_BGR2HSV_FULL);	
			double tempH_MIN=(double)HSV[0][channel];
			double tempH_MAX=(double)HSV[1][channel];
			double tempS_MIN=(double)HSV[2][channel];
			double tempS_MAX=(double)HSV[3][channel];
			double tempV_MIN=(double)HSV[4][channel];
			double tempV_MAX=(double)HSV[5][channel];
			Core.inRange(filters.get(channel), new Scalar(tempH_MIN,tempS_MIN,tempV_MIN),new Scalar(tempH_MAX,tempS_MAX,tempV_MAX),filters.get(channel));


			Mat kernel = Imgproc.getStructuringElement(Imgproc.MORPH_ELLIPSE, new Size(19,19));
			Mat closed = new Mat(); // closed will have type CV_32F
			Imgproc.morphologyEx(filters.get(channel), closed, Imgproc.MORPH_CLOSE, kernel);
			Core.divide(filters.get(channel), closed, closed, 1, CvType.CV_32F);
			Core.normalize(filters.get(channel), filters.get(channel), 0, 255, Core.NORM_MINMAX, CvType.CV_8U);
			Imgproc.threshold(filters.get(channel), filters.get(channel), -1, 255, Imgproc.THRESH_BINARY_INV
					+Imgproc.THRESH_OTSU); 

			
			Imgproc.erode(filters.get(channel), filters.get(channel), Imgproc.getStructuringElement(Imgproc.MORPH_RECT,  new org.opencv.core.Size (8, 8)));			
			Imgproc.dilate(filters.get(channel), filters.get(channel), Imgproc.getStructuringElement(Imgproc.MORPH_RECT, new Size(4,4)));
			
			
            

			List<MatOfPoint> contours = new ArrayList<MatOfPoint>();
			Mat hierarchy = new Mat();
			// find contours:
			Imgproc.findContours(filters.get(channel), contours, hierarchy, Imgproc.RETR_TREE,Imgproc.CHAIN_APPROX_SIMPLE);
			MatOfPoint2f approxCurve = new MatOfPoint2f();


			List<MatOfPoint> subContours = new ArrayList<MatOfPoint>();
			ArrayList<Point> objects=new ArrayList<Point>();
			ArrayList<Scalar> colors=new ArrayList<Scalar>();
			
			// Get contour index with largest area
			if(debug){			
				colors.add(new Scalar(211,14,255));  //pink			
				colors.add(new Scalar(155,0,0)); //Blue
				colors.add(new Scalar(0,255,255));  //Yellow
				colors.add(new Scalar(0,0,255));   //Red
				colors.add(new Scalar(211,14,145));  //purple			
				colors.add(new Scalar(0,78,255));   //Orange
				
			}
			
				
			
			for (int i=1;i<contours.size();i++) {
				
				if(Imgproc.contourArea(contours.get(i))>AREAMIN_THRESHOLD){ // remove noise
					//Convert contours(i) from MatOfPoint to MatOfPoint2f
					MatOfPoint2f contour2f = new MatOfPoint2f( contours.get(i).toArray() );
					//Processing on mMOP2f1 which is in type MatOfPoint2f
					double approxDistance = Imgproc.arcLength(contour2f, true)*0.02;
					//Imgproc.approxPolyDP(contour2f, approxCurve, approxDistance, true);
					Imgproc.approxPolyDP(contour2f, approxCurve, 12.0, true);        

					//Convert back to MatOfPoint
					MatOfPoint points = new MatOfPoint( approxCurve.toArray() );

					// Get bounding rect of contour
					Rect rect = Imgproc.boundingRect(points);
					
					if(debug){
					//draw enclosing rectangle (all same color, but you could use variable i to make them unique)					
					Core.rectangle(frame, rect.tl(), rect.br(), colors.get(channel),2, 8,0);
					}
					
										
					Point center=new Point((int)(rect.tl().x+(rect.br().x-rect.tl().x)/2), 640-(int)(rect.tl().y+(rect.br().y-rect.tl().y)/2));					
					objects.add(center);
					subContours.add(contours.get(i));
				}
			}
			int maxAreaIndex = getMaxValueIdx(subContours);	
			
			Robot robot=null;
			if(objects.size()==2){
				Point front=objects.get(maxAreaIndex);
				objects.remove(maxAreaIndex);
				robot=new Robot(objects.get(0), front, channel+1);
			}
			
				
			
			return robot;
	    	
	    }
	
public void setFlagFilter(int flagFilter) {	
	this.flagFilter = flagFilter;
}

public void drawObject(double x, double y,Mat frame){

	//use some of the openCV drawing functions to draw crosshairs
	//on your tracked image!

    //UPDATE:JUNE 18TH, 2013
    //added 'if' and 'else' statements to prevent
    //memory errors from writing off the screen (ie. (-25,-25) is not within the window!)

	Core.circle(frame,new Point(x,y),30,new Scalar(0,255,0),2);
    if(y-25>0)
    Core.line(frame,new Point(x,y),new Point(x,y-25),new Scalar(0,255,0),2);
    else Core.line(frame,new Point(x,y),new Point(x,0),new Scalar(0,255,0),2);
    if(y+25<FRAME_HEIGHT)
    	Core.line(frame,new Point(x,y),new Point(x,y+25),new Scalar(0,255,0),2);
    else Core.line(frame,new Point(x,y),new Point(x,FRAME_HEIGHT),new Scalar(0,255,0),2);
    if(x-25>0)
    	Core.line(frame,new Point(x,y),new Point(x-25,y),new Scalar(0,255,0),2);
    else Core.line(frame,new Point(x,y),new Point(0,y),new Scalar(0,255,0),2);
    if(x+25<FRAME_WIDTH)
    	Core.line(frame,new Point(x,y),new Point(x+25,y),new Scalar(0,255,0),2);
    else Core.line(frame,new Point(x,y),new Point(FRAME_WIDTH,y),new Scalar(0,255,0),2);
    
    
	Core.putText(frame,x+","+(640-y),new Point(x,y+30),1,1,new Scalar(0,255,0),2);

}

public void viewHSV(int[][] hSV, int ch) {
	HSV=hSV;
	channel=ch;
	H_MIN=(double)HSV[0][channel];
	H_MAX=(double)HSV[1][channel];
	S_MIN=(double)HSV[2][channel];
	S_MAX=(double)HSV[3][channel];
	V_MIN=(double)HSV[4][channel];
	V_MAX=(double)HSV[5][channel];	
	flagFilter=FILTER_HSV;
	
}

public static int getMaxValueIdx(List<MatOfPoint> contours){  
	double maxValue=-1;
	int index=0;
	for(int i=0;i<contours.size();i++){ 
		double area=Imgproc.contourArea(contours.get(i));
		if(area > maxValue && area<AREAMAX_THRESHOLD ){  
			maxValue = area; 
			index=i;
		}  
	}  
	
	return index;  
}

public Point approxPoint(Point src,Point dst){
	Point out=src;
	if(Math.abs(src.x-dst.x)<2)
	   out.x=dst.x;
	if(Math.abs(src.y-dst.y)<2)
		   out.y=dst.y;	
	
	return out;	
}

/*
public ArrayList<Robot> getRobots() {
	return robots;
	
}  */

}