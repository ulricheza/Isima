import exception.DEVS_Exception;
import model.*;
import types.*;

public class TrafficLight extends AtomicModel {
	// Definition of S: a state variable is used for the current color

	int stateColor;
	// 0 for Go
	// 1 for Ready
	// 2 for Stop
	// 3 for ShutDown
	
	public TrafficLight(String name, String desc) {
		super(name, desc);
		
		// Definition of the output port (for Y):
		// the name of the port is xxx.color if the name of the model is xxx
		// the value sent out is a color: "Green", "Yellow", "Red" or "Off"
		String[] colors = { "Green", "Yellow", "Red", "Off"};
		addOutputPortStructure(new DEVS_Enum(colors), this.getName()+".COLOR", "Color sent out for users");
		
		// Definition of the input port (for X):
		// the name of the port is xxx.command if the name of the model is xxx
		// the value received is a command: "Failure" or "Recovery"
		String[] commands = { "Failure", "Recovery"};
		addInputPortStructure(new DEVS_Enum(commands), this.getName()+".COMMAND", "Trigger received");
		
		// State initialization: the light starts Green
		stateColor = 0;
	}

	public void deltaInt() {
		// The behavior is the following:
		// Go -> Ready -> Stop -> Go -> Ready -> ...
		stateColor = (stateColor +1) % 3;
	}

	public double ta() {
		// ta(Go) = 5
		// ta(Ready) = 1
		// ta(Stop) = 3
		// ta(ShutDown) = +infinity
		if (stateColor == 0) return 5.0;
		else if (stateColor == 1) return 1.0;
		else if (stateColor == 2) return 3.0;
		else return DEVS_Real.POSITIVE_INFINITY;
	}

	public void lambda() throws DEVS_Exception {
		// L(Go) = Yellow
		// L(Ready) = Red
		// L(Stop) = Green
		// There is no L for ShutDown, since ta(ShutDown) = +infinity
		String toSend = (stateColor==0)?"Yellow":((stateColor==1)?"Red":"Green");
		setOutputPortData(this.getName()+".COLOR", toSend);
	}

	public void deltaExt(double e) throws DEVS_Exception {
		// Let's get the value received
		String received = getInputPortData(this.getName()+".COMMAND").toString();
		
		// Then process it:
		// in case of failure, the system goes to ShutDown
		// in case of recovery, it goes to Green
		// these are done whatever the current state is and whatever the elapsed time is
		if (received.compareTo("Failure") == 0) stateColor = 3;
		else if (received.compareTo("Recovery") == 0) stateColor = 0;
		else {
			System.out.println("Unexpected value received in " + this.getName() + ":" + received);
			throw new DEVS_Exception();
		}
	}
}