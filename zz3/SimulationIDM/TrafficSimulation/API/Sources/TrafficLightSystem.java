import model.*;
import java.util.*;

public class TrafficLightSystem extends CoupledModel {

	public TrafficLightSystem(String name, String desc) {
		super(name, desc);

		// Definition of {Md}
		Generator Mgen = new Generator("SOURCE","Generator of random events");
		TrafficLight Mlight = new TrafficLight("TARGET","System under study");
		Collector Mcoll = new Collector("SINK","Repository of results");
		
		// Definition of D
		addSubModel(Mgen);
		addSubModel(Mlight);
		addSubModel(Mcoll);
		
		// There is no EIC, since the global model is input-free

		// Definition of IC:
		// SOURCE(OUT)-->(COMMAND)TARGET(COLOR)-->(STORE)SINK
		addIC(Mgen.getOutputPortStructure("SOURCE.OUT"), Mlight.getInputPortStructure("TARGET.COMMAND")) ;
		addIC(Mlight.getOutputPortStructure("TARGET.COLOR"), Mcoll.getInputPortStructure("SINK.STORE")) ;

		// There is no EOC, since the global model is output-free
	}
	
	public Model select(ArrayList<Model> possibleModels) {
		// The traffic light has the higher priority
		// Otherwise a kind of random choice is done
		for ( Model m : possibleModels ) {
			if ( m instanceof TrafficLight ) return m ;
		}
		return possibleModels.get(0);
	}
}
