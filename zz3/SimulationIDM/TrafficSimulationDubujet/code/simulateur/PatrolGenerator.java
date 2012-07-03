package simulateur;

import model.AtomicModel;
import exception.DEVS_Exception;
import types.DEVS_Enum;
import java.util.*;

public class PatrolGenerator extends AtomicModel {
	// Definition of S : no state variable since there is only one single possible state
	
	// Additional attribute necessary for random number generation
	Random rd;
	
	public PatrolGenerator(String name, String desc) {
		super(name, desc);
		
		// Definition of the output port (for Y):
		// the name of the port is xxx.out if the name of the model is xxx
		// the value sent out is a command: "Recovery"
		String[] commands = {"Recovery"};
		addOutputPortStructure(new DEVS_Enum(commands), this.getName()+".OUT", "My single output port");
		
		// No input port : X = {}
		
		// No state initialization: the state will always be the same implicit one
		
		// Initialization of the additional attribute
		rd = new Random();
	}

	public void deltaInt() {
		// Nothing to say: we always return to the same implicit state
	}

	public double ta() {
		return 15.0;
	}

	public void lambda() throws DEVS_Exception {
			setOutputPortData(this.getName()+".OUT", "Recovery");
	}

	public void deltaExt(double e) throws DEVS_Exception {
		// Not defined, since there is no input
	}
}