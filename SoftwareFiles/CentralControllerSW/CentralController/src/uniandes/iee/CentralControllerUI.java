package uniandes.iee;

import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JButton;

import java.awt.Dialog;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.Window;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

import javax.swing.JSlider;
import javax.swing.event.ChangeListener;
import javax.swing.event.ChangeEvent;
import javax.swing.JTextPane;
import javax.swing.JPopupMenu;

import java.awt.Component;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;

import javax.swing.JMenuBar;

import org.opencv.core.Point;

import uniandes.iee.hardware.Robot;
import uniandes.iee.markerDetector.MyCam;


public class CentralControllerUI extends JFrame implements ActionListener, WindowListener {
	
	private static final long serialVersionUID = 1L;
	private CentralController controller;	
	private JButton btnStart,btnStop,btnTest,btnStartRobots,btnStopRobots;
	private JPanel jPanel;
    private JMenuBar menuBar;
    private CameraConfigUI cameraConfig;
    private PortConfigUI   comConfig;
    private JMenuItem cameraMenuItem,comMenuItem; 
   
	
	public CentralControllerUI() {
		
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		getContentPane().setLayout(null);
		
		
		jPanel = new JPanel();
		jPanel.setBounds(24, 26, 640, 480);
		getContentPane().add(jPanel);
		
		btnStart = new JButton("Start Camera");
		btnStart.addActionListener(this);
		btnStart.setBounds(529, 533, 117, 23);
		btnStart.setEnabled(true);
		getContentPane().add(btnStart);
		
		btnStop = new JButton("Stop Camera");
		btnStop.setBounds(529, 579, 117, 23);
		btnStop.setEnabled(false);
		btnStop.addActionListener(this);
		getContentPane().add(btnStop);
		
		btnTest = new JButton("StartRobots");
		btnTest.setBounds(135, 579, 108, 23);
		getContentPane().add(btnTest);
		btnTest.addActionListener(this);
		
		btnStartRobots = new JButton("StartRobots+GPS");
		btnStartRobots.addActionListener(this);
		btnStartRobots.setBounds(24, 528, 219, 23);
		getContentPane().add(btnStartRobots);
		
		btnStopRobots = new JButton("StopRobots");
		btnStopRobots.setBounds(24, 579, 101, 23);
		btnStopRobots.addActionListener(this);
		getContentPane().add(btnStopRobots);
		
		
		setVisible(true);
		setBounds(100, 100,687,678);
		
		controller=new CentralController(this);
		cameraConfig=new CameraConfigUI(this);
		comConfig=new PortConfigUI(controller.getAvalilablePorts(),this);
		
		menuBar = new JMenuBar();	   
		setJMenuBar(menuBar);
		
		
		JMenu config = new JMenu("Config");
		cameraMenuItem = new JMenuItem("Camera");
		cameraMenuItem.addActionListener(this);
		
		comMenuItem = new JMenuItem("COM port");
		comMenuItem.addActionListener(this);
		
		config.add(cameraMenuItem);
		config.add(comMenuItem);
		menuBar.add(config);
	    
		setLocationRelativeTo(null);
		setResizable(false);
		revalidate();
		
	}
		
	public static void main(String[] args) {
		System.out.println("Controller UI Started"); // Display the string.
		CentralControllerUI gui = new CentralControllerUI();
		
		 gui.addWindowListener(gui);
				
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource().equals(btnStart)){
			btnStart.setEnabled(false);
			btnStop.setEnabled(true);
			controller.startCamera(cameraConfig.getCameraSource());
		}
		else if(e.getSource().equals(btnStop)){
			btnStart.setEnabled(true);
			btnStop.setEnabled(false);
			controller.stopCamera();
		}
		else if(e.getSource().equals(btnTest)){			
			
			
			if(comConfig.isConected()){				
				ArrayList<byte[]> message=controller.generateMessage(null,controller.MESSAGE_START);							
				controller.sendMSG(message.get(0));	
				
				/*
				for (byte[] bs : message) { 				 
					
						 System.out.println("Start:");
						 for (int i = 0; i < bs.length; i++) 
					        	System.out.format("0x%x ",bs[i]);	
					
				}	*/	
		
			}
			else{
				/*
				JOptionPane.showMessageDialog(this,
					    "First connect the COM port in menu options");
					    */
				
				comConfig.setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
				comConfig.setVisible(true);	
				comConfig.setLocationRelativeTo(this);
				
			}     
			
			
		}
		else if(e.getSource().equals(btnStartRobots)){
			
			if(comConfig.isConected()){				
				ArrayList<byte[]> message=controller.generateMessage(null,controller.MESSAGE_START);							
				controller.sendMSG(message.get(0));
				
			    controller.setFlagSend(CentralController.MESSAGE_GPS);
			    			
		
			}
			else{
				/*
				JOptionPane.showMessageDialog(this,
					    "First connect the COM port in menu options");
					    */
				
				comConfig.setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
				comConfig.setVisible(true);	
				comConfig.setLocationRelativeTo(this);
				
			}
			
		}
	    else if(e.getSource().equals(btnStopRobots)){
			
			if(comConfig.isConected()){				
			
				 controller.setFlagSend(CentralController.FLAG_SEND_NO);
				 ArrayList<byte[]> message=controller.generateMessage(null,controller.MESSAGE_STOP);							
				 controller.sendMSG(message.get(0));
				 
			
			}
			else{
				
				comConfig.setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
				comConfig.setVisible(true);	
				comConfig.setLocationRelativeTo(this);
				/*
				JOptionPane.showMessageDialog(this,
					    "First connect the COM port in menu options");*/
			}
			
		}
		else if(e.getSource().equals(comMenuItem)){			
			comConfig.setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
			comConfig.setVisible(true);	
			comConfig.setLocationRelativeTo(this);			
		}
		else if(e.getSource().equals(cameraMenuItem)){			
			cameraConfig.setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
			cameraConfig.setVisible(true);	
			cameraConfig.setLocationRelativeTo(this);
			controller.setFilter(MyCam.FILTER_HSV);
		}
	
		
	}


	public JPanel getJpanel() {
		return jPanel;
	}

	private static void addPopup(Component component, final JPopupMenu popup) {
		component.addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e) {
				if (e.isPopupTrigger()) {
					showMenu(e);
					System.out.println(e);
				}
			}
			public void mouseReleased(MouseEvent e) {
				if (e.isPopupTrigger()) {
					showMenu(e);
				}
			}
			private void showMenu(MouseEvent e) {
				popup.show(e.getComponent(), e.getX(), e.getY());
			}
		});
	}
	
	public CentralController getController() {
		return controller;
	}

	@Override
	public void windowActivated(WindowEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowClosed(WindowEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowClosing(WindowEvent arg0) {
		System.out.println("closing");
		
		if(controller.isCam())
		controller.stopCamera();
		
		if(controller.isPort())
		controller.disconnect();
		
	}

	@Override
	public void windowDeactivated(WindowEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowDeiconified(WindowEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowIconified(WindowEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowOpened(WindowEvent arg0) {
		// TODO Auto-generated method stub
		
	}
}
