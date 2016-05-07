package uniandes.iee;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.util.ArrayList;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JComboBox;
import javax.swing.JLabel;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class PortConfigUI extends JDialog {

	private final JPanel contentPanel = new JPanel();
    private CentralControllerUI parent;
    private JComboBox comboBox;
    private JLabel lblState;
    private boolean conected=false;
	
	/**
	 * Create the dialog.
	 */
	public PortConfigUI(String[] comPorts, CentralControllerUI parent) {

    	this.parent=parent;
		setTitle("COM port Configuration");
		setBounds(100, 100, 389, 138);
		getContentPane().setLayout(new BorderLayout());
		contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
		getContentPane().add(contentPanel, BorderLayout.CENTER);
		contentPanel.setLayout(null);
		{
			comboBox = new JComboBox();
			comboBox.setBounds(130, 17, 98, 25);			
			comboBox.setModel(new javax.swing.DefaultComboBoxModel(comPorts));
			contentPanel.add(comboBox);
		}
		{
			JLabel lblAva = new JLabel("Available \r\n COM ports");
			lblAva.setBounds(10, 22, 110, 14);
			contentPanel.add(lblAva);
		}
		{
			lblState = new JLabel("State:  Disconnect\r\n");
			lblState.setBounds(96, 65, 146, 14);
			contentPanel.add(lblState);
		}
		
		JButton btnRefresh = new JButton("Refresh");
		btnRefresh.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				String [] model=parent.getController().getAvalilablePorts();
				comboBox.setModel(new javax.swing.DefaultComboBoxModel(model));
			}
		});
		btnRefresh.setBounds(252, 18, 89, 23);
		contentPanel.add(btnRefresh);
		{
			JButton connectButton = new JButton("Connect");
			connectButton.addMouseListener(new MouseAdapter() {
				@Override
				public void mouseClicked(MouseEvent e) {	
					if(connectButton.getText().equals("Connect")){
						if(parent.getController().conecToPort(comboBox.getSelectedIndex())){
						lblState.setText("State:  Connect\r\n");
						connectButton.setText("Disconnect");						
						conected=true;
						}
						else{
							JOptionPane.showMessageDialog(parent,
								    "COM port in use",
								    "COM port error",
								    JOptionPane.ERROR_MESSAGE);
						}
					}
					else{
						parent.getController().disconnect();
						connectButton.setText("Connect");
						lblState.setText("State:  Disconnect");
						conected=false;
					}
				}
			});
			connectButton.setBounds(252, 61, 89, 23);
			contentPanel.add(connectButton);
			connectButton.setActionCommand("Cancel");
		}
	}

	public boolean isConected() {
		return conected;
	}
}
