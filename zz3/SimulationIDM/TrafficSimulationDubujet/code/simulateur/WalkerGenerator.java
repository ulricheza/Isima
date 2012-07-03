package simulateur;

import model.AtomicModel;
import exception.DEVS_Exception;
import types.DEVS_Enum;
import java.util.*;

public class WalkerGenerator extends AtomicModel {
	// Definition of S : no state variable since there is only one single possible state
	
	// Additional attribute necessary for random number generation
	Random rd;
	
	public WalkerGenerator(String name, String desc) {
		super(name, desc);
		
		// Definition of the output port (for Y):
		// the name of the port is xxx.out if the name of the model is xxx
		// the value sent out is a command: "Walker"
		String[] commands = {"Walker"};
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
		return (rd.nextInt(5));
	}

	public void lambda() throws DEVS_Exception {
		if(rd.nextInt(100)+1 < 60) {
			setOutputPortData(this.getName()+".OUT", "Walker");
		}
	}

	public void deltaExt(double e) throws DEVS_Exception {
		// Not defined, since there is no input
	}
}