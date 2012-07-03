package simulateur;

import model.*;
import java.util.*;

public class TrafficLightSystem extends CoupledModel {

	public TrafficLightSystem(String name, String desc) {
		super(name, desc);

		// Definition of {Md}
		FailureGenerator Mfail = new FailureGenerator("SOURCE1","Generator of failure events");
		PatrolGenerator Mpat = new PatrolGenerator("SOURCE2","Generator of recovery events");
		WalkerGenerator Mwalm = new WalkerGenerator("SOURCE3","Generator of recovery events");
		WalkerGenerator Mwala = new WalkerGenerator("SOURCE4","Generator of recovery events");
		MainTrafficLight Mmlt = new MainTrafficLight("TARGET","System under study");
		AuxiliaryTrafficLight Malt = new AuxiliaryTrafficLight("SUBTARGET","Subsystem under study");
		Collector Mcoll = new Collector("SINK","Repository of results");
		
		// Definition of D
		addSubModel(Mfail);
		addSubModel(Mpat);
		addSubModel(Mwalm);
		addSubModel(Mwala);
		addSubModel(Mmlt);
		addSubModel(Malt);
		addSubModel(Mcoll);
		
		// There is no EIC, since the global model is input-free

		// Definition of IC:
		// SOURCE(OUT)-->(COMMAND)TARGET(COLOR)-->(STORE)SINK
		addIC(Mfail.getOutputPortStructure("SOURCE1.OUT"), Mmlt.getInputPortStructure("TARGET.COMMAND")) ;
		addIC(Mpat.getOutputPortStructure("SOURCE2.OUT"), Mmlt.getInputPortStructure("TARGET.COMMAND")) ;
		addIC(Mwalm.getOutputPortStructure("SOURCE3.OUT"), Mmlt.getInputPortStructure("TARGET.COMMAND")) ;
		addIC(Mwala.getOutputPortStructure("SOURCE4.OUT"), Malt.getInputPortStructure("SUBTARGET.COMMAND")) ;
		addIC(Mmlt.getOutputPortStructure("TARGET.AUX"), Malt.getInputPortStructure("SUBTARGET.COMMAND")) ;
		addIC(Malt.getOutputPortStructure("SUBTARGET.MAIN"), Mmlt.getInputPortStructure("TARGET.COMMAND")) ;
		addIC(Mmlt.getOutputPortStructure("TARGET.COLOR"), Mcoll.getInputPortStructure("SINK.STORE")) ;
		addIC(Malt.getOutputPortStructure("SUBTARGET.COLOR"), Mcoll.getInputPortStructure("SINK.STORE")) ;

		// There is no EOC, since the global model is output-free
	}
	
	public Model select(ArrayList<Model> possibleModels) {
		// The traffic light has the higher priority
		// Otherwise a kind of random choice is done
		for ( Model m : possibleModels ) {
			if ( m instanceof MainTrafficLight ) return m ;
		}
		return possibleModels.get(0);
	}
}
