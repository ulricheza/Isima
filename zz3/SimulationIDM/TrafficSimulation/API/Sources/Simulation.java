import simulator.RootCoordinator;
import exception.DEVS_Exception;
	
public class Simulation {

	public static void main(String[] args) {
		// Creation of the study
		TrafficLightSystem study = new TrafficLightSystem("TLS","Experimentation of a traffic light system");
		
		// Creation of the simulation tree
		RootCoordinator root = new RootCoordinator(study.getSimulator());
		
		// Experimentation:
		// initial time is 0.0
		// final time is 1000.0
		try {
			root.init(0.0);
			root.run(1000.0);
		} catch (DEVS_Exception e) {
			e.printStackTrace();
		}	
	}
}
