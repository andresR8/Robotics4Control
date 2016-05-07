package uniandes.iee;
import uniandes.iee.hardware.Robot;
import uniandes.iee.markerDetector.*;
import gnu.io.CommPortIdentifier;
import gnu.io.PortInUseException;

import java.nio.ByteBuffer;
import java.util.ArrayList;

import javax.print.attribute.standard.PrinterMessageFromOperator;

import org.opencv.core.Core;



public class CentralController{
	 private VirtualComm myVirtualComm;
     private MyCam camera;
 	 private Thread readThread;	
 	 private ArrayList<Robot> robots;
 	 public static final char MESSAGE_CONNECT='C',NRF24L01_PAYLOAD=1,MESSAGE_START='S',MESSAGE_GPS='G',FLAG_SEND_NO='X', MESSAGE_STOP='T'; //PAYLOAD de 1 para algoritmos de SYNC
 	                                                                                                                                       //PAYLOAD de 8 o >8 para algoritmos de GPS
	
	
 	 private char flagSend=FLAG_SEND_NO;
     private boolean isCam=false,isPort=false;
 
	public CentralController(CentralControllerUI gui){
		 myVirtualComm=new VirtualComm();		 
		 System.loadLibrary(Core.NATIVE_LIBRARY_NAME);
		 camera=new MyCam(gui,this);	
	 }
	 
	public String[] getAvalilablePorts(){		
		 ArrayList<CommPortIdentifier> ports=myVirtualComm.listPorts();
		 int size=ports.size()==0?1:ports.size();
		 String[] out=new String[size];
		 
		 if(ports.size()>0){		 
		 for (int i = 0; i < ports.size(); i++)
			 out[i]=ports.get(i).getName();
		 }
		 else out[0]="No ports Available";
		 
		 return out;
	 }
	 	
	public void startCamera(int source){
		 camera.startCamera(source);
		 isCam=true;
	 }
	 
	public boolean conecToPort(int port){
		 isPort=true;
		 ArrayList<CommPortIdentifier> ports=myVirtualComm.listPorts();
		 try {
			 myVirtualComm.connectToPort(ports.get(port));			
			 
		} catch (Exception e) {
			System.out.println(e);
			isPort=false;
		}
		
		return isPort;
	}
	
	public void stopCamera(){
		 camera.stopCamera();
		 isCam=false;
	 }

	public void disconnect() {
		 if(isPort)
		 myVirtualComm.serialPort.close();
		 isPort=false;
		
	}

	public void viewHSV(int[][] hSV, int channel) {
		camera.viewHSV(hSV,channel);		
	
	}
	
	public void setDebugView(boolean b){
		camera.setDebug(b);
	}
	
	

	public void setFilter(int filter) {
		camera.setFlagFilter(filter);		
	}


	
	public void connectToRobots(){		
				
	}
	
	public void sendRobots(ArrayList<Robot> robots,boolean debug){
		this.robots=robots;
		
		if (robots.size()>0 && flagSend!=FLAG_SEND_NO) {
			 
			 ArrayList<byte[]> message = null;
			
		     message=generateMessage(robots,flagSend);			
			if(debug) System.out.println(flagSend);
			 
			 for (byte[] bs : message) { 				 
				 myVirtualComm.writeToPort(bs);
				 if(debug){
					  System.out.println("RobotSend:");
					 for (int i = 0; i < bs.length; i++) 
				        	System.out.format("0x%x ",bs[i]);	
				 }
			}		
			 
			 if(debug)System.out.println(""); 		    
		    
		}
		
	}
	
	public ArrayList<byte[]> generateMessage(ArrayList<Robot> robots,int message) {
		
		ArrayList<byte[]> resp=new ArrayList<>();
		switch (message) {
		case MESSAGE_CONNECT:
			for (Robot robot : robots) {
				if(robot!=null){	
				byte[] out = new byte[2+NRF24L01_PAYLOAD];
				out[0]=MESSAGE_CONNECT;				
				out[1]=(byte) robot.getId();
				resp.add(out);
				}
				
			}
		break;	
		
		case MESSAGE_GPS:
			for (Robot robot : robots) {				
				if(robot!=null){
				byte[] out = new byte[2+NRF24L01_PAYLOAD];
				out[0]=MESSAGE_GPS;				
				out[1]=(byte) robot.getId();
				byte[] temp=getBytesString(robot.getCenter().x);
				out[2]=temp[0];
				out[3]=temp[1];
				
				temp=getBytesString(robot.getCenter().y);
				out[4]=temp[0];
				out[5]=temp[1];
				
				temp=getBytesString(robot.getFront().x);
				out[6]=temp[0];
				out[7]=temp[1];

				temp=getBytesString(robot.getFront().y);
				out[8]=temp[0];
				out[9]=temp[1];	
				resp.add(out);
				}
				
			}
		break;
		
		
		case MESSAGE_START:			
				byte[] out = new byte[2+NRF24L01_PAYLOAD];
				out[0]=MESSAGE_START;
				resp.add(out);			
		break;		
		
		case MESSAGE_STOP:			
			byte[] outs = new byte[2+NRF24L01_PAYLOAD];
			outs[0]=MESSAGE_STOP;
			resp.add(outs);			
	    break;	
	
		
		
		
		
		}
		return resp;
	}
	
	 
	 public void setFlagSend(char flagSend) {
		this.flagSend = flagSend;
	}

	 
	public byte[] getBytesString(double number){
		
		int N=(int)number;
		byte[] bytes= ByteBuffer.allocate(4).putInt(N).array();
		byte[] out= new byte[bytes.length-2];		
		
        for (int i = 2; i < bytes.length; i++)         	
			out[i-2]=bytes[i];        
       
        return out;
	}

	public void sendMSG(byte[] message) {
		myVirtualComm.writeToPort(message);
		
	}

	public boolean isCam() {		
		return isCam;
	}
	
	public boolean isPort() {		
		return isPort;
	}

	
	
	


}


