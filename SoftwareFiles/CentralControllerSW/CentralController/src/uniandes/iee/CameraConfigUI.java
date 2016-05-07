package uniandes.iee;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.util.ArrayList;

import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JTextPane;
import javax.swing.border.EmptyBorder;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.plaf.basic.BasicBorders.RadioButtonBorder;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.DefaultComboBoxModel;

import uniandes.iee.markerDetector.MyCam;

import javax.swing.JRadioButton;
import javax.swing.JCheckBox;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeEvent;

public class CameraConfigUI extends JDialog implements ActionListener, ChangeListener, WindowListener {

	private static final long serialVersionUID = 1L;
	private final JPanel contentPanel = new JPanel();
	private JSlider slider_SMAX,slider_SMIN,slider_VMAX,slider_VMIN,slider_HMIN,slider_HMAX;
	private JTextPane txtpnHmin,txtpnHmax, txtpnSmin ,	txtpnVmin ,txtpnSmax,txtpnVmax;
	private CentralControllerUI controllerUI;
	private JButton okButton;
	private JComboBox comboBoxSource;
	private JComboBox comboBoxChannel; 
	private JRadioButton rdbtnHsvFilter,rdbtnCloseFilter,rdbtnErode;
	JCheckBox chckbxShow;
	
	private int cameraSource=0;
	

	 
	 
	 private int[][] HSV = {{208,161,51,0,0,25}, //H_MIN
			 {240,180,87,27,280,337},  //H_MAX
			 {83,197,33,107,193,120}, //S_MIN
			 {183,253,217,180,403,380}, //S_MAX
			 {150,100,173,143,107,123},  //V_MIN
			 {290,133,270,240,177,500}}; //V_MAX
	 

	 
	 
	private String[] colorsChannels={"Pink","Blue","Yellow","Orange","Red","Purple"};
	private int channel=0;
	

	/**
	 * Create the dialog.
	 */
	public CameraConfigUI(CentralControllerUI parent) {
		controllerUI=parent;
		setTitle("CameraSettings");
		setBounds(100, 100, 373, 378);
		getContentPane().setLayout(null);
		contentPanel.setBounds(0, 0, 0, 0);
		contentPanel.setLayout(new FlowLayout());
		contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
		getContentPane().add(contentPanel);
		{
			JPanel buttonPane = new JPanel();
			buttonPane.setBounds(1, 316, 353, 33);
			buttonPane.setLayout(new FlowLayout(FlowLayout.RIGHT));
			getContentPane().add(buttonPane);
			{
				okButton = new JButton("OK");
				okButton.setActionCommand("OK");
				okButton.addActionListener(this);
				buttonPane.add(okButton);
				getRootPane().setDefaultButton(okButton);
			}
		}
		
		slider_HMIN = new JSlider();		
		slider_HMIN.setMaximum(500);
		slider_HMIN.setBounds(10, 35, 151, 26);
		slider_HMIN.addChangeListener(this);
		getContentPane().add(slider_HMIN);
		
		slider_HMAX = new JSlider();		
		slider_HMAX.setMaximum(500);
		slider_HMAX.setBounds(190, 35, 164, 26);
		slider_HMAX.addChangeListener(this);
		getContentPane().add(slider_HMAX);	
		
		
		slider_SMIN = new JSlider();		
		slider_SMIN.setMaximum(500);
		slider_SMIN.setBounds(10, 103, 164, 26);
		slider_SMIN.addChangeListener(this);
		getContentPane().add(slider_SMIN);
		
		slider_SMAX = new JSlider();		
		slider_SMAX.setMaximum(500);
		slider_SMAX.setBounds(190, 103, 164, 26);
		slider_SMAX.addChangeListener(this);
		getContentPane().add(slider_SMAX);
		
		slider_VMIN = new JSlider();		
		slider_VMIN.setMaximum(500);
		slider_VMIN.setBounds(10, 171, 164, 26);
		slider_VMIN.addChangeListener(this);
		getContentPane().add(slider_VMIN);	
		
		slider_VMAX = new JSlider();		
		slider_VMAX.setMaximum(500);
		slider_VMAX.setBounds(184, 171, 164, 26);
		slider_VMAX.addChangeListener(this);
		getContentPane().add(slider_VMAX);		
		
		txtpnHmin = new JTextPane();		
		txtpnHmin.setBounds(51, 11, 89, 20);
		getContentPane().add(txtpnHmin);
		
		txtpnHmax = new JTextPane();		
		txtpnHmax.setBounds(237, 11, 89, 20);
		getContentPane().add(txtpnHmax);
		
		txtpnSmin = new JTextPane();		
		txtpnSmin.setBounds(51, 72, 89, 20);
		getContentPane().add(txtpnSmin);
		
		txtpnSmax = new JTextPane();		
		txtpnSmax.setBounds(237, 72, 89, 20);
		getContentPane().add(txtpnSmax);
		
		txtpnVmin = new JTextPane();		
		txtpnVmin.setBounds(51, 140, 89, 20);
		getContentPane().add(txtpnVmin);		
		
		txtpnVmax = new JTextPane();		
		txtpnVmax.setBounds(239, 134, 87, 26);
		getContentPane().add(txtpnVmax);
		
        updateSliders();
		
		comboBoxSource = new JComboBox();	
		comboBoxSource.setModel(new DefaultComboBoxModel(new String[] {"0", "1"}));
		comboBoxSource.setBounds(102, 208, 59, 20);
		comboBoxSource.addActionListener(this);
		comboBoxSource.setSelectedItem(cameraSource);;
		getContentPane().add(comboBoxSource);
		
		JLabel lblNewLabel = new JLabel("Camera Source");
		lblNewLabel.setBounds(20, 214, 79, 14);
		getContentPane().add(lblNewLabel);
		
		comboBoxChannel = new JComboBox();
		comboBoxChannel.setBounds(237, 208, 89, 20);
		comboBoxChannel.setModel(new DefaultComboBoxModel(colorsChannels));
		comboBoxChannel.addActionListener(this);
		getContentPane().add(comboBoxChannel);
		
		JLabel lblFilter = new JLabel("Filter");
		lblFilter.setBounds(194, 214, 38, 14);
		getContentPane().add(lblFilter);
		
		rdbtnHsvFilter = new JRadioButton("HSV Filter");
		rdbtnHsvFilter.setSelected(true);
		rdbtnHsvFilter.setBounds(41, 259, 71, 23);
		rdbtnHsvFilter.addActionListener(this);
		getContentPane().add(rdbtnHsvFilter);
		
		rdbtnCloseFilter = new JRadioButton("CLOSE Filter");
		rdbtnCloseFilter.setBounds(127, 259, 109, 23);
		rdbtnCloseFilter.addActionListener(this);
		getContentPane().add(rdbtnCloseFilter);
		
		
		rdbtnErode = new JRadioButton(" ERODE Filter");
		rdbtnErode.setBounds(239, 259, 109, 23);
		rdbtnErode.addActionListener(this);
		getContentPane().add(rdbtnErode);
		
		ButtonGroup btnGroup=new ButtonGroup();
		btnGroup.add(rdbtnErode);
		btnGroup.add(rdbtnCloseFilter);
		btnGroup.add(rdbtnHsvFilter);
		
		chckbxShow = new JCheckBox("Show");
		chckbxShow.addChangeListener(this);
		chckbxShow.setSelected(false);
		chckbxShow.setBounds(135, 286, 97, 23);
		getContentPane().add(chckbxShow);
		
		addWindowListener(this);
		
		setResizable(false);
	}

	@Override
	public void stateChanged(ChangeEvent e) {
		
		if(e.getSource().equals(slider_HMIN)){		    
			HSV[0][channel]=slider_HMIN.getValue();
		    txtpnHmin.setText("HMIN: " + slider_HMIN.getValue());
		}
		else if(e.getSource().equals(slider_HMAX)){			
			HSV[1][channel]=slider_HMAX.getValue();
			txtpnHmax.setText("HMAX: " + slider_HMAX.getValue());
		}		
		else if(e.getSource().equals(slider_SMIN)){			
			HSV[2][channel]=slider_SMIN.getValue();
			txtpnSmin.setText("SMIN: " + slider_SMIN.getValue());
		}
		else if(e.getSource().equals(slider_SMAX)){			
			HSV[3][channel]=slider_SMAX.getValue();
			txtpnSmax.setText("SMAX: " + slider_SMAX.getValue());
		}
		else if(e.getSource().equals(slider_VMIN)){			
			HSV[4][channel]=slider_VMIN.getValue();
			txtpnVmin.setText("VMIN: " + slider_VMIN.getValue());
		}
		else if(e.getSource().equals(slider_VMAX)){			
			HSV[5][channel]=slider_VMAX.getValue();
			txtpnVmax.setText("VMAX: " + slider_VMAX.getValue());
		}
		else if(e.getSource().equals(chckbxShow)){
			controllerUI.getController().setDebugView(chckbxShow.isSelected());
			System.out.println("checkBox");
		}
		
		
		
		if(isVisible())
		controllerUI.getController().viewHSV(HSV,channel);
		
	}
    
	

	@Override
	public void actionPerformed(ActionEvent e) {
		
		if(e.getSource().equals(okButton)){
		   setVisible(false);
		   controllerUI.getController().setFilter(MyCam.FILTER_NO);
		}
		else if(e.getSource().equals(comboBoxSource))
		 cameraSource=comboBoxSource.getSelectedIndex();
		else if(e.getSource().equals(comboBoxChannel)){
			channel=comboBoxChannel.getSelectedIndex();
			updateSliders();
			controllerUI.getController().viewHSV(HSV,channel);
		}
		else if(e.getSource().equals(rdbtnCloseFilter) || e.getSource().equals(rdbtnErode) || e.getSource().equals(rdbtnHsvFilter)){
			if(rdbtnCloseFilter.isSelected())
				controllerUI.getController().setFilter(MyCam.FILTER_CLOSE);
			else if(rdbtnErode.isSelected())
				controllerUI.getController().setFilter(MyCam.FILTER_ERODE);
			else if (rdbtnHsvFilter.isSelected())
				controllerUI.getController().setFilter(MyCam.FILTER_HSV);
				
		}
		
	}
	
	public void updateSliders(){				
			JTextPane[] Jtexts={txtpnHmin,txtpnHmax,txtpnSmin,txtpnSmax,txtpnVmin,txtpnVmax};
			JSlider[] Jslider={slider_HMIN,slider_HMAX,slider_SMIN,slider_SMAX,slider_VMIN,slider_VMAX};
			String[] labels={"HMIN: ","H_MAX: ","SMIN: ","S_MAX: ","VMIN: ","V_MAX: "};
			for (int i = 0; i < Jtexts.length; i++) {
				Jtexts[i].setText(labels[i]+HSV[i][channel]);
				Jslider[i].setValue(HSV[i][channel]);
			}					    
	}
	
	public int getCameraSource() {
		return cameraSource;
	}

	@Override
	public void windowActivated(WindowEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowClosed(WindowEvent arg0) {
		controllerUI.getController().setFilter(MyCam.FILTER_NO);
		
	}

	@Override
	public void windowClosing(WindowEvent arg0) {
		// TODO Auto-generated method stub
		
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
