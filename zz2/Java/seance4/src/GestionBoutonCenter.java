import javax.swing.*;

import java.awt.event.*;

public class GestionBoutonCenter implements ActionListener {

	
	public GestionBoutonCenter(JFrame frame, String but) {
		this.frame = frame;
		this.but = but;
	}

	JFrame frame;
	String but;
	
	@Override
	public void actionPerformed(ActionEvent e) {
		JDialog dialog = new JDialog(frame,but);
		dialog.add(new JLabel(but));
		dialog.setSize(150, 150);
		dialog.setVisible(true);
	}
}
