import javax.swing.JFrame;
import javax.swing.JLabel;


public class Affichage {
	public static void afficher()
	{
		   JFrame frame = new JFrame("HelloWorldSwing");
		   frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		  
		   //Creation des labels
		   JLabel label = new JLabel("Hello World");
		   frame.setSize(200, 200);
		   frame.getContentPane().add(label);
		   frame.pack();
		   frame.setVisible(true);
	}

}
