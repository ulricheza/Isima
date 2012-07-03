package trafficsimulation;

import model.*;
import java.util.*;

public class TrafficLightSystem extends CoupledModel {

    public TrafficLightSystem(String name, String desc) {
        super(name, desc);

        // Definition of {Md}
        Generator Mgen = new Generator("SOURCE", "Generator of random events");
        TrafficLight Mlight = new TrafficLight("TARGET", "System under study");
        Collector Mcoll = new Collector("SINK", "Repository of results");
        TrafficLightSecondaire Msecond = new TrafficLightSecondaire("SECONDAIRE", "Systeme secondaire");

        // Definition of D
        addSubModel(Mgen);
        addSubModel(Mlight);
        addSubModel(Mcoll);
        addSubModel(Msecond);

        // Definition of IC:
        addIC(Mgen.getOutputPortStructure("SOURCE.OUT"), Mlight.getInputPortStructure("TARGET.COMMAND"));

        addIC(Mlight.getOutputPortStructure("TARGET.COLOR"), Msecond.getInputPortStructure("SECONDAIRE.COMMANDCOLOR"));
        addIC(Mgen.getOutputPortStructure("SOURCE.OUT"), Msecond.getInputPortStructure("SECONDAIRE.COMMAND"));

        addIC(Mlight.getOutputPortStructure("TARGET.COLOR"), Mcoll.getInputPortStructure("SINK.STORE"));
        addIC(Msecond.getOutputPortStructure("SECONDAIRE.COLOR"), Mcoll.getInputPortStructure("SINK.STORE"));

    }

    @Override
    public Model select(ArrayList<Model> possibleModels) {
        // The traffic light has the higher priority
        // Otherwise a kind of random choice is done
        for (Model m : possibleModels) {
            if (m instanceof TrafficLight) {
                return m;
            }
        }
        return possibleModels.get(0);
    }
}
