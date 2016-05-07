package uniandes.iee;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.TooManyListenersException;

import gnu.io.*;


public class VirtualComm implements Runnable, SerialPortEventListener{
	static CommPortIdentifier portId;
	static Enumeration portList;
	InputStream inputStream;
	SerialPort serialPort;
	Thread readThread;	
    static OutputStream outputStream;

    
	 public VirtualComm(){

	 }

	 public void openPort(CommPortIdentifier portId) throws PortInUseException{
		 //Open Port
		 serialPort = (SerialPort) portId.open("VirtualCommApp", 2000);
		 System.out.println("Port: " + portId.getName() + " Opened");	

	 }
 
	 public void connectToPort(CommPortIdentifier portId){

		 try{
			 openPort(portId);
			 //Set input and Output Streams
			 inputStream = serialPort.getInputStream();			 
			 outputStream = serialPort.getOutputStream();	

			 //Set Port Params
			 serialPort.setSerialPortParams(256000,
					 SerialPort.DATABITS_8,
					 SerialPort.STOPBITS_1,
					 SerialPort.PARITY_NONE);
			 
			 readThread = new Thread(this);
		     readThread.start();
		 }
		 catch (PortInUseException e) {System.err.println("Error Port: " + portId.getName() + " in Use");}
		 catch (IOException e) {System.out.println("Error IOException " + e);}
		 catch (UnsupportedCommOperationException e) {System.out.println("UnsupportedCommOperation " + e);}		 
	 }
   	 
	 public void writeToPort(byte[] message){
		 try {
             outputStream.write(message);
         } catch (IOException e) {System.err.println(e);}
	 }
	 
	 public ArrayList<CommPortIdentifier> listPorts(){
		 ArrayList<CommPortIdentifier> ports=new ArrayList<CommPortIdentifier>();
		 
		 Enumeration port_list = CommPortIdentifier.getPortIdentifiers();
      
		 while (port_list.hasMoreElements()){
			 CommPortIdentifier port_id = (CommPortIdentifier)port_list.nextElement();
             
			 if (port_id.getPortType() == CommPortIdentifier.PORT_SERIAL)			
				 ports.add(port_id);	
						 
						
		 }
		 
		 return ports;
	 }

	@Override
     public void serialEvent(SerialPortEvent event) {
		System.out.println("SerialEvent");
        switch(event.getEventType()) {
        case SerialPortEvent.BI:
        case SerialPortEvent.OE:
        case SerialPortEvent.FE:
        case SerialPortEvent.PE:
        case SerialPortEvent.CD:
        case SerialPortEvent.CTS:
        case SerialPortEvent.DSR:
        case SerialPortEvent.RI:
        case SerialPortEvent.OUTPUT_BUFFER_EMPTY:
            break;
            
        case SerialPortEvent.DATA_AVAILABLE:
            byte[] readBuffer = new byte[20];

            try {
                while (inputStream.available() > 0) {
                    int numBytes = inputStream.read(readBuffer);
                }
                System.out.print(new String(readBuffer));
            } catch (IOException e) {System.out.println(e);}
         break;
         
        }
    }

	@Override
	 public void run() {
        try {
            Thread.sleep(20000);
        } catch (InterruptedException e) {System.out.println(e);}
    }


}
