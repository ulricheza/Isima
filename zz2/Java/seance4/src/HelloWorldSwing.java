import java.awt.BorderLayout;
import java.awt.Button;

import javax.swing.JFrame;

public class HelloWorldSwing {
   @SuppressWarnings("deprecation")
private static void createAndShowGUI() {

	   JFrame frame = new JFrame("HelloWorldSwing");
	   frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	  
	   /* Creation des labels et des fenetres modale
	   JLabel label = new JLabel("Hello World");
	   JDialog modal = new JDialog(frame,"coucou",false);
	   modal.setSize(100, 100);
	   frame.getContentPane().add(label);
	   frame.pack();
	   modal.setVisible(true);*/
	   
	   frame.setVisible(true);
	   frame.setSize(400,400);
	   
	   Button b1 = new Button("PAGE_START");
	   Button b2 = new Button("PAGE_END");
	   Button b3 = new Button("LINE_START");
	   Button b4 = new Button("LINE_END");
	   Button b5 = new Button("CENTER");
	   
	   //creation du design BorderLayout
	   frame.getContentPane().setLayout(new BorderLayout());
	   frame.getContentPane().add(b1, BorderLayout.NORTH);
	   frame.getContentPane().add(b2, BorderLayout.SOUTH);
	   frame.getContentPane().add(b3, BorderLayout.WEST);
	   frame.getContentPane().add(b4, BorderLayout.EAST);
	   frame.getContentPane().add(b5, BorderLayout.CENTER);
	   
	   b1.addActionListener(new GestionBoutonCenter(frame,"NORTH"));
	   b2.addActionListener(new GestionBoutonCenter(frame,"SOUTH"));
	   b3.addActionListener(new GestionBoutonCenter(frame,"WEST"));
	   b4.addActionListener(new GestionBoutonCenter(frame,"EAST"));
	   b5.addActionListener(new GestionBoutonCenter(frame,"CENTER"));
	   frame.addMouseListener(new GestionSouris(frame));
	   
	   

	   
   }
   
   public static void main(String[] args){
	   javax.swing.SwingUtilities.invokeLater(new Runnable(){
		   public void run(){
			   createAndShowGUI();
		   }
	   });
   }
}
