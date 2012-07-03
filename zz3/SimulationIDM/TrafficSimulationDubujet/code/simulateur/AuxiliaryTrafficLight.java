package simulateur;

import exception.DEVS_Exception;
import model.*;
import types.*;

public class AuxiliaryTrafficLight extends AtomicModel {
	// Definition of S: a state variable is used for the current color

	int stateColor;
	int walkerRequests;
	int previousState;
	double elapsedTime;
	// 0 for Go
	// 1 for Ready
	// 2 for Stop
	// 3 for ShutDown-temp
    // 4 for ShutDown
	// 5 for walker request
	
	public AuxiliaryTrafficLight(String name, String desc) {
		super(name, desc);
		walkerRequests = 0;
		// Definition of the output port (for Y):
		// the name of the port is xxx.color if the name of the model is xxx
		// the value sent out is a color: "Green", "Yellow", "Red" or "Off"
		String[] colors = { "Green", "Yellow", "Red", "Off"};
		addOutputPortStructure(new DEVS_Enum(colors), this.getName()+".COLOR", "Color sent out for users");
		addOutputPortStructure(new DEVS_Enum(colors), this.getName()+".MAIN", "Color sent out for main light");
		
		// Definition of the input port (for X):
		// the name of the port is xxx.command if the name of the model is xxx
		// the value received is a command: "Failure" or "Recovery"
		String[] commands = {"Green", "Yellow", "Red", "Off", "Walker"};
		addInputPortStructure(new DEVS_Enum(commands), this.getName()+".COMMAND", "Trigger received");
		
		// State initialization: the light starts Green
		stateColor = 0;
	}

	public void deltaInt() {
		if(stateColor == 12){
			stateColor = previousState;	
		}
	}

	public double ta() {
		double res;
		if (stateColor == 12) {
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
		String toSend = " AUXILIARY : ";
		String toMain = "";
        if(stateColor == 0) {
            toSend += "Green";
        } else if(stateColor == 1) {
            toSend += "Yellow";
        } else if(stateColor==2) {
            toSend += "Red";
        } else if(stateColor==12) {
            toSend += "Walker";
			if(walkerRequests >= 4) {
				toMain = "Auxiliary";
			}
        } else {
            toSend += "Off";
        }
		setOutputPortData(this.getName()+".COLOR", toSend);
		if(!toMain.isEmpty()) {
			setOutputPortData(this.getName()+".MAIN", toMain);
		}
	}

	public void deltaExt(double e) throws DEVS_Exception {
		String received = getInputPortData(this.getName()+".COMMAND").toString();
		if(received.compareTo("Green") == 0) {
			stateColor = 0;
		} else if(received.compareTo("Yellow") == 0) {
			stateColor = 1;
		} else if(received.compareTo("Red") == 0) {
			stateColor = 2;
		} else if(received.compareTo("Off") == 0) {
			stateColor = 4;
		} else if(received.compareTo("Walker") == 0) {
			if(stateColor==0 || stateColor==1) {
				elapsedTime += e;
				previousState = stateColor;
				stateColor = 12;
				walkerRequests++;
			}
		} else {
			System.out.println("Unexpected value received in " + this.getName() + ":" + received+"*");
			throw new DEVS_Exception();
		}
		lambda();
	}
}