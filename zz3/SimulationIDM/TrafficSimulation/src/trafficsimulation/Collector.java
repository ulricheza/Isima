package trafficsimulation;

import exception.DEVS_Exception;
import model.*;
import types.*;
import java.io.*;

public class Collector extends AtomicModel {
    // Definition of S :
    // there is only one single possible state which lasts for ever until a trigger is received 
    // a state variable is used for the current repository (a file)

    PrintStream trajectory;

    public Collector(String name, String desc) {
        super(name, desc);

        // No output port: Y = {}

        // Definition of the input port (for X):
        // the name of the port is xxx.store if the name of the model is xxx
        // the value received is a color: "Green", "Yellow", "Red" or "Blink"
        String[] couleurs = {"vert", "orange", "rouge", "eteint"};
        addInputPortStructure(new DEVS_Enum(couleurs), this.getName() + ".STORE", "Data to store");


        // State initialization: the name of the file is xxx.txt if the name of the model is xxx
        try {
            trajectory = new PrintStream(name + ".txt");
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    @Override
    public double ta() {
        return DEVS_Real.POSITIVE_INFINITY;
    }

    @Override
    public void deltaInt() {
        // Not defined, since there is a single possible state which time advance value is +infinity
    }

    public void lambda() throws DEVS_Exception {
        // Not defined, for the same reasons
    }

    @Override
    public void deltaExt(double e) throws DEVS_Exception {
        // Let's get the value received and the simulation time it has been received
        String received = getInputPortData(this.getName() + ".STORE").toString();
        double when = this.getSimulator().getTL();

        // Then store them in the following shape:
        // simulation time : data received
        trajectory.println(when + " : " + received);
    }
}