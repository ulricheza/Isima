import javax.swing.*;
import java.awt.event.*;

public class GestionSouris implements MouseListener{
	JFrame frame;
    JDialog dia;
	public GestionSouris(JFrame frame) {
		super();
		this.frame = frame;
		this.dia = new JDialog(frame,"Avertissement");
		this.dia.setSize(200, 200);
		this.dia.add(new JLabel("ARRETE DE BOUGER LA SOURIS"));
	}
	@Override
	public void mouseClicked(MouseEvent e) {
		dia.setVisible(true);
		
	}
	@Override
	public void mousePressed(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void mouseEntered(MouseEvent e) {
		dia.setVisible(true);
		
	}
	@Override
	public void mouseExited(MouseEvent e) {
		dia.setVisible(true);
		
	}
	


	
}
