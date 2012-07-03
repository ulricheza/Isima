package gui;

import exception.DEVS_Exception;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;
import javax.swing.JPanel;
import javax.swing.JSplitPane;
import simulateur.TrafficLightSystem;
import simulator.RootCoordinator;

public class Simulation extends JFrame implements ActionListener, Runnable {
	
	private Slider periode;
	private Slider vitesse;
	private JButton startButton;
	
	private ImageIcon feuNord;
	private JLabel imageNord;
	private ImageIcon feuSud;
	private JLabel imageSud;
	private ImageIcon feuEst;
	private JLabel imageEst;
	private ImageIcon feuOuest;
	private JLabel imageOuest;
	private JLabel pietonPrincipal;
	private JLabel pietonAuxiliaire;

	private Simulation() {
		super();
		//Creation de la fenetre
		this.setSize(950, 640);
		this.setLocationRelativeTo(null);
		this.setTitle("Feux tricolores");
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setResizable(false);
		//splitpane
		JSplitPane jsp = new JSplitPane();
		jsp.setOrientation(JSplitPane.HORIZONTAL_SPLIT);
		//panneau gauche (image du croisement)
		JLayeredPane jlp = new JLayeredPane();
		//croisement
		ImageIcon croisement = new ImageIcon("images/crossroad.png");
		JLabel image = new JLabel(croisement);
		JPanel jp = new JPanel();
		jp.add(image);
		jp.setBounds(0, 0,croisement.getIconWidth(),croisement.getIconHeight());
		jlp.add(jp,new Integer(0));
		//feux
		//nord
		feuNord = new ImageIcon("images/black.png");
		imageNord = new JLabel(feuNord);
		JPanel jpn = new JPanel();
		jpn.add(imageNord);
		jpn.setBounds(177, 101,feuNord.getIconWidth(),feuNord.getIconHeight());
		jlp.add(jpn,new Integer(1));
		//sud
		feuSud = new ImageIcon("images/black.png");
		imageSud = new JLabel(feuSud);
		JPanel jps = new JPanel();
		jps.add(imageSud);
		jps.setBounds(403, 343,feuSud.getIconWidth(),feuSud.getIconHeight());
		jlp.add(jps,new Integer(1));
		//est
		feuEst = new ImageIcon("images/black.png");
		imageEst = new JLabel(feuEst);
		JPanel jpe = new JPanel();
		jpe.add(imageEst);
		jpe.setBounds(404, 101,feuEst.getIconWidth(),feuEst.getIconHeight());
		jlp.add(jpe,new Integer(1));
		//ouest
		feuOuest = new ImageIcon("images/black.png");
		imageOuest = new JLabel(feuOuest);
		JPanel jpo = new JPanel();
		jpo.add(imageOuest);
		jpo.setBounds(176, 343,feuOuest.getIconWidth(),feuOuest.getIconHeight());
		jlp.add(jpo,new Integer(1));
		//pietons
		//principal
		pietonPrincipal = new JLabel("0");
		JPanel jppp = new JPanel();
		jppp.add(pietonPrincipal);
		jppp.setBounds(495, 350, 50, 25);
		jlp.add(jppp,new Integer(1));
		//auxiliaire
		pietonAuxiliaire = new JLabel("0");
		JPanel jppa = new JPanel();
		jppa.add(pietonAuxiliaire);
		jppa.setBounds(495, 170, 50, 25);
		jlp.add(jppa,new Integer(1));
		jsp.setLeftComponent(jlp);
		jsp.getLeftComponent().setMinimumSize(new Dimension(670,640));
		//panneau droit (parametrage de la simulation)
		JPanel jpr = new JPanel();
		//periode
		JLabel label = new JLabel("Paramètres de simulation");
		label.setBorder(BorderFactory.createEmptyBorder(10, 0, 10, 0));
		jpr.add(label);
		periode = new Slider("Période de simulation : ", 0,5000,1000);
		periode.setBorder(BorderFactory.createEmptyBorder(10, 0, 10, 0));
		jpr.add(periode);
		vitesse = new Slider("Vitesse de simulation : ", 1,100,10);
		vitesse.setBorder(BorderFactory.createEmptyBorder(10, 0, 10, 0));
		jpr.add(vitesse);
		startButton = new JButton("Démarrer la simulation");
		startButton.addActionListener(this);
		jpr.add(startButton);
		jsp.setRightComponent(jpr);
		jsp.setDividerLocation(670);
		this.setContentPane(jsp);
		this.setVisible(true);
	}	

	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == this.startButton) {
			this.startButton.setEnabled(false);
			this.periode.setEnabled(false);
			this.vitesse.setEnabled(false);
			// Creation of the study
			TrafficLightSystem study = new TrafficLightSystem("TLS","Experimentation of a traffic light system");
			// Creation of the simulation tree
			RootCoordinator root = new RootCoordinator(study.getSimulator());
			// Experimentation:
			// initial time is 0.0
			// final time is 1000.0
			try {
				root.init(0.0);
				root.run(this.periode.getValue());
			} catch (DEVS_Exception ex) {
				ex.printStackTrace();
			}
			new Thread(this).start();
		}
	}
	
	@Override
	public void run() {
		try{
			FileInputStream fstream = new FileInputStream("SINK.txt");
			DataInputStream in = new DataInputStream(fstream);
			BufferedReader br = new BufferedReader(new InputStreamReader(in));
			String strLine;
			ArrayList<String> data = new ArrayList<String>();
			while ((strLine = br.readLine()) != null) {
				data.add(strLine);
			}
			br.close();
			in.close();
			fstream.close();
			double time = 0;
			int size = data.size();
			int speed = this.vitesse.getValue();
			for (int i = 0; i < size; ++i) {
				// read next event time
				String[] tokens = data.get(i).split(":");
				time = Double.parseDouble(tokens[0]);
				String fireType = tokens[1].trim();
				// get the next image(color) of the traffic light
				String color = tokens[2].trim();
				System.out.println(time+" : "+fireType+" : "+color);
				if(fireType.equals("MAIN")) {
					if(!color.equals("Walker")) {
						setFeuPrincipal(color);
					} else {
						setPietonPrincipal(1);
					}
				} else {
					if(!color.equals("Walker")) {
						setFeuAuxiliaire(color);
					} else {
						setPietonAuxiliaire(1);
					}
				}
				// stay in the current state for a time period according to simulation results
				double timeToSleep = 0;
				if (i < size - 1) {
					String[] nextTokens = data.get(i+1).split(":");
					timeToSleep = Double.parseDouble(nextTokens[0]) - time;
				}
				try {
					Thread.sleep((int)((timeToSleep * 1000)/speed));
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}catch (Exception e){
			System.err.println("Error: " + e.getMessage());
		}
		this.startButton.setEnabled(true);
		this.periode.setEnabled(true);
		this.vitesse.setEnabled(true);
	}
	
	public void setFeuPrincipal(String couleur) {
		if(couleur.equals("Green")) {
			this.feuNord.setImage(new ImageIcon("images/green.png").getImage());
			this.feuSud.setImage(new ImageIcon("images/green.png").getImage());
		} else if(couleur.equals("Yellow")) {
			this.feuNord.setImage(new ImageIcon("images/yellow.png").getImage());
			this.feuSud.setImage(new ImageIcon("images/yellow.png").getImage());
		} else if(couleur.equals("Red")) {
			this.feuNord.setImage(new ImageIcon("images/red.png").getImage());
			this.feuSud.setImage(new ImageIcon("images/red.png").getImage());
			setPietonPrincipal(0);
		} else if(couleur.equals("Off")) {
			this.feuNord.setImage(new ImageIcon("images/black.png").getImage());
			this.feuSud.setImage(new ImageIcon("images/black.png").getImage());
		}
		this.imageNord.repaint();
		this.imageSud.repaint();
	}
	
	public void setFeuAuxiliaire(String couleur) {
		if(couleur.equals("Green")) {
			this.feuEst.setImage(new ImageIcon("images/green.png").getImage());
			this.feuOuest.setImage(new ImageIcon("images/green.png").getImage());
		} else if(couleur.equals("Yellow")) {
			this.feuEst.setImage(new ImageIcon("images/yellow.png").getImage());
			this.feuOuest.setImage(new ImageIcon("images/yellow.png").getImage());
		} else if(couleur.equals("Red")) {
			this.feuEst.setImage(new ImageIcon("images/red.png").getImage());
			this.feuOuest.setImage(new ImageIcon("images/red.png").getImage());
			setPietonAuxiliaire(0);
		} else if(couleur.equals("Off")) {
			this.feuEst.setImage(new ImageIcon("images/black.png").getImage());
			this.feuOuest.setImage(new ImageIcon("images/black.png").getImage());
		}
		this.imageEst.repaint();
		this.imageOuest.repaint();
	}
	
	public void setPietonPrincipal(int valeur) {
		if(valeur == 1) {
			int tmp = Integer.parseInt(this.pietonPrincipal.getText());
			this.pietonPrincipal.setText(Integer.toString(tmp+1));
		} else {
			this.pietonPrincipal.setText("0");
		}
	}
	
	public void setPietonAuxiliaire(int valeur) {
		if(valeur == 1) {
			int tmp = Integer.parseInt(this.pietonAuxiliaire.getText());
			this.pietonAuxiliaire.setText(Integer.toString(tmp+1));
		} else {
			this.pietonAuxiliaire.setText("0");
		}
	}
	
	public static void main(String[] args) {
		try {
			for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
				if ("Nimbus".equals(info.getName())) {
					javax.swing.UIManager.setLookAndFeel(info.getClassName());
					break;
				}
			}
		} catch (ClassNotFoundException ex) {
			java.util.logging.Logger.getLogger(Simulation.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
		} catch (InstantiationException ex) {
			java.util.logging.Logger.getLogger(Simulation.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
		} catch (IllegalAccessException ex) {
			java.util.logging.Logger.getLogger(Simulation.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
		} catch (javax.swing.UnsupportedLookAndFeelException ex) {
			java.util.logging.Logger.getLogger(Simulation.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
		}
		Simulation sim = new Simulation();
	}
}
