package gui;

import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.util.Hashtable;

import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JSlider;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

/**
 * 
 * @author Rémi Dubujet
 *
 */

public class Slider extends JPanel implements ChangeListener {
	
	private JLabel name;
	private JSlider slider;
	private int init;
	private JTextField value;
	private GridBagConstraints c;
	
	/**
	 * Constructor
	 * @param innom name of the control, displayed in the interface
	 * @param min minimum value of the slider
	 * @param max maximum value of the slider
	 * @param initValue initial value of the slider
	 */
	public Slider(String innom,int min,int max,int initValue) {
		this.init = initValue;
		name=new JLabel(innom);
		this.setLayout(new GridBagLayout());
		c = new GridBagConstraints();
		c.anchor=GridBagConstraints.FIRST_LINE_START;
		c.gridx=0;
		c.gridy=0;
		this.add(name,c);
		//display the value
		value=new JTextField(Integer.toString(initValue));
		value.setHorizontalAlignment(SwingConstants.CENTER);
		value.setEnabled(false);
		value.setPreferredSize(new Dimension(50,25));
		c.anchor=GridBagConstraints.FIRST_LINE_END;
		c.gridx=1;
		c.gridy=0;
		this.add(value,c);
		slider=new JSlider(min,max,initValue);
		slider.addChangeListener(this);
		//add a label for every meter
		Hashtable labelTable = new Hashtable();
		labelTable.put( new Integer(min), new JLabel(""+min));
		labelTable.put( new Integer(max), new JLabel(""+max));
		slider.setMajorTickSpacing(max/10);
		slider.setPaintTicks(true);
		slider.setLabelTable(labelTable);
		slider.setPaintLabels(true);
		slider.setPreferredSize(new Dimension(250,40));
		c.gridx=0;
		c.gridy=1;
		c.gridwidth=2;
		c.fill = GridBagConstraints.HORIZONTAL;
		this.add(slider,c);
	}

	/**
	 * change the string in the text field when the slider is modified
	 */
	public void stateChanged(ChangeEvent event) {
		if(event.getSource()==slider) {
			value.setText(Integer.toString(slider.getValue()));
		}
	}
	
	/**
	 * get the value displayed in the textfield
	 * @return the value displayed
	 */
	public int getValue() {
		return Integer.parseInt(value.getText());
	}
	
	@Override
	public void setEnabled(boolean enabled) {
		this.slider.setEnabled(enabled);
	}
}
