package simulateur;

import exception.DEVS_Exception;
import model.*;
import types.*;

public class MainTrafficLight extends AtomicModel {
	// Definition of S: a state variable is used for the current color

	int stateColor;
	int walkerRequests;
	int previousState;
	double elapsedTime;
	// 0 for Go
	// 1 for Ready
	// 2 for Stop (go auxiliary)
	// 3 for Stop (ready auxiliary)
	// 10 for ShutDown-temp
    // 11 for ShutDown
	// 12 for walker request
	
	public MainTrafficLight(String name, String desc) {
		super(name, desc);
		walkerRequests = 0;
		// Definition of the output port (for Y):
		// the name of the port is xxx.color if the name of the model is xxx
		// the value sent out is a color: "Green", "Yellow", "Red" or "Off"
		String[] colors = { "Green", "Yellow", "Red", "Off"};
		addOutputPortStructure(new DEVS_Enum(colors), this.getName()+".COLOR", "Color sent out for users");
		addOutputPortStructure(new DEVS_Enum(colors), this.getName()+".AUX", "Color sent out for auxiliary light");
		
		// Definition of the input port (for X):
		// the name of the port is xxx.command if the name of the model is xxx
		// the value received is a command: "Failure" or "Recovery"
		String[] commands = { "Failure", "Recovery", "Walker"};
		addInputPortStructure(new DEVS_Enum(commands), this.getName()+".COMMAND", "Trigger received");
		
		// State initialization: the light starts Green
		stateColor = 0;
		elapsedTime = 0;
	}

	public void deltaInt() {
		// The behavior is the following:
		// Go -> Ready -> Stop -> Go -> Ready -> ...
		if(stateColor < 4) {
			stateColor = (stateColor +1) % 4;
			elapsedTime = 0;
		} else if(stateColor == 12){
			if(walkerRequests >= 4 && previousState==0) {
				elapsedTime = 0;
				stateColor = 1;
			} else {
				stateColor = previousState;	
			}
		} else {
			stateColor = 11;
		}
		if(stateColor == 2) {
			walkerRequests = 0;
		}
	}

	public double ta() {
		// ta(Go) = 5
		// ta(Ready) = 1
		// ta(Stop) = 3
		// ta(ShutDown) = +infinity
		double res = 0;
        if (stateColor == 0) {
			res=2.0-elapsedTime;
		} else if (stateColor == 1) {
			res=5.0-elapsedTime;
		} else if (stateColor == 2) {
			res=1.0-elapsedTime;
		} else if (stateColor == 3) {
			res=1.0-elapsedTime;
		} else if (stateColor == 10) {
			res=0.0;
		} else if (stateColor == 12) {
			res=0.0;
		} else {
			res=DEVS_Real.POSITIVE_INFINITY;
		}
		return res;
	}

	public void lambda() throws DEVS_Exception {
		// L(Go) = Yellow
		// L(Ready) = Red
		// L(Stop) = Green
		// There is no L for ShutDown, since ta(ShutDown) = +infinity
		String toCollector = " MAIN : ";
		String toAuxiliary = "";
        if(stateColor == 0) {
            toCollector += "Green";
			toAuxiliary = "Red";
        } else if(stateColor == 1) {
            toCollector += "Yellow";
        } else if(stateColor==2) {
            toCollector += "Red";
			toAuxiliary = "Green";
        } else if(stateColor==3) {
			toAuxiliary = "Yellow";
        } else if(stateColor==12) {
            toCollector += "Walker";
        } else {
            toCollector += "Off";
			toAuxiliary = "Off";
        }
		if(!toCollector.equals(" MAIN : ")) {
			setOutputPortData(this.getName()+".COLOR", toCollector);
		}
		if(!toAuxiliary.isEmpty()) {
			setOutputPortData(this.getName()+".AUX", toAuxiliary);
		}
	}

	public void deltaExt(double e) throws DEVS_Exception {
		// Let's get the value received
		String received = getInputPortData(this.getName()+".COMMAND").toString();
		
		// Then process it:
		// in case of failure, the system goes to ShutDown
		// in case of recovery, it goes to Green
		// these are done whatever the current state is and whatever the elapsed time is
		if (received.compareTo("Failure") == 0) {
			if(stateColor < 10) {
				stateColor = 10;
			}
		} else if (received.compareTo("Recovery") == 0) {
			if(stateColor == 11) {
				stateColor = 0;
			}
		} else if(received.compareTo("Walker") == 0) {
			if(stateColor==0 || stateColor==1) {
				elapsedTime += e;
				previousState = stateColor;
				stateColor = 12;
				walkerRequests++;
			}
		} else if (received.compareTo("Auxiliary") == 0) {
			if(stateColor == 3) {
				stateColor = 4;
			} else if(stateColor == 4) {
				stateColor = 0;
			}
		}else {
			System.out.println("Unexpected value received in " + this.getName() + ":" + received);
			throw new DEVS_Exception();
		}
	}
}