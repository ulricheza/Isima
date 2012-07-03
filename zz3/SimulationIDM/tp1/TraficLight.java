import exception.DEVS_Exception;
import model.*;
import types.*;

public class TraficLight extends AtomicModel {
	// S
	// 0 pour Vert
	// 1 pour Orange
	// 2 pour Rouge
	int state;
	
	public TraficLight(String name, String desc) {
		super(name, desc);
		// Y
		String[] colors = { "green", "yellow", "red"};
		addOutputPortStructure(new DEVS_Enum(colors), "color", "color of the light");		
		// init state
		state = 0;
	}

	public void lambda() throws DEVS_Exception {
		if (state == 0) setOutputPortData("color", "yellow");
		else if (state == 1) setOutputPortData("color", "red");
		else setOutputPortData("color", "green");
	}

	public void deltaInt() {
		state = (state +1)	% 3;
	}

	public void deltaExt(double e) throws DEVS_Exception {
	}

	public double ta() {
		if (state == 0) return 5.0;
		else if (state == 1) return 1.0;
		else return 3.0;
	}
}