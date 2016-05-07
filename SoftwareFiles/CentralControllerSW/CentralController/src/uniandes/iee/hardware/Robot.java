package uniandes.iee.hardware;

import org.opencv.core.Point;

public class Robot {
	
	private Point center,front;


	
	public static final int RED=0x1,BLUE=0x2,YELLOW=0x3,ORANGE=0x4,PURPLE=0x5,PINK=0x6;



	private int id;
	
	public Robot(Point center, Point front, int id) {			
		this.id = id;
		this.center=center;
		this.front = front;
			
	}
		
	


	private double rad2deg(double d) {
		d=d*(180/Math.PI);
		return d;
	}


	public double getHeading() {
		Point translate=new Point(front.x-center.x,front.y-center.y);
		double norm=Math.sqrt(Math.pow(translate.x,2)+Math.pow(translate.y,2));
		
		translate.x=translate.x/norm;
		translate.y=translate.y/norm;
		Point originX=new Point(1,0);	
		
		double dot = originX.x*translate.x + originX.y*translate.y;    // dot product
		double det = originX.x*translate.y - originX.y*translate.x;    // determinant
		double heading = Math.atan2(det, dot);
		
		if(heading<0)
			heading=2*Math.PI+heading;
		
		heading=rad2deg(heading);
		
		//double heading = rad2deg(Math.acos(translate.x*originX.x+translate.y*originX.y));
		
		return heading;
	}

	public int getId() {
		return id;
	}
	
	public Point getCenter() {
		return center;
	}
	
	public Point getFront(){
		return front;
	}
	
	
	
	
	

}
