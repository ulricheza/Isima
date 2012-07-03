package trafficsimulation;

import exception.DEVS_Exception;
import model.*;
import types.*;

/**
 * Classes modélisant les feux primaires
 * @author Jean-Christophe SEPTIER
 */
public class TrafficLight extends AtomicModel {

    // Listes des états des feux
    enum States {

        v, // Vert
        oar, // Orange avant rouge
        oav, // Orange avant 
        r, // Rouge
        co, // Cassé orange
        c,     // Cassé jaune
    }
    // Etats des feux
    States stateColor;
    // Liste des couleurs
    String[] couleurs = {"vert", "orange", "rouge", "eteint"};

    /**
     * Constructeur du TrafficLight
     * @param name nom du modèle
     * @param desc descriptions
     */
    public TrafficLight(String name, String desc) {

        super(name, desc);

        // Sortie des couleurs
        addOutputPortStructure(new DEVS_Enum(couleurs), this.getName() + ".COLOR", "Color sent out for users");

        // Entrée des pannes
        String[] commands = {"Failure", "Recovery"};
        addInputPortStructure(new DEVS_Enum(commands), this.getName() + ".COMMAND", "Trigger received");

        // Démarre à vert
        stateColor = States.v;
    }

    @Override
    public void deltaInt() {
        // Change l'état
        switch (stateColor) {
            case v:
                stateColor = States.oar;
                break;
            case oar:
                stateColor = States.r;
                break;
            case oav:
                stateColor = States.v;
                break;
            case r:
                stateColor = States.oav;
                break;
            case c:
                stateColor = States.co;
                break;
            case co:
                stateColor = States.c;
                break;
        }
    }

    // Temps des feux
    @Override
    public double ta() {

        double sigma;
        switch (stateColor) {
            case v:
                sigma = Configuration.tempsVert;
                break;
            case oar:
                sigma = Configuration.tempsOrange;
                break;
            case oav:
                sigma = Configuration.tempsOrange;
                break;
            case r:
                sigma = Configuration.tempsRouge;
                break;
            case co:
                sigma = Configuration.tempsClignotant;
                break;
            case c:
                sigma = Configuration.tempsClignotant;
                break;
            default:
                sigma = DEVS_Real.POSITIVE_INFINITY;
        }
        return sigma;
    }

    // Envoie la couleur dans l'output
    @Override
    public void lambda() throws DEVS_Exception {

        String name = "";
        switch (stateColor) {
            case v:
                name = couleurs[1];
                break;
            case oar:
                name = couleurs[2];
                break;
            case oav:
                name = couleurs[0];
                break;
            case r:
                name = couleurs[1];
                break;
            case c:
                name = couleurs[1];
                break;
            case co:
                name = couleurs[3];
                break;
        }

        setOutputPortData(this.getName() + ".COLOR", name);
    }

    // Entrée
    @Override
    public void deltaExt(double e) throws DEVS_Exception {

        String received = getInputPortData(this.getName() + ".COMMAND").toString();
        System.out.println(received);
        // Si patrouille
        if (received.compareTo("Recovery") == 0) {
            setOutputPortData(this.getName() + ".COLOR", "Passage de la patrouille");
            // Répare le feux s'il est en panne
            if (stateColor == States.co || stateColor == States.c) {
                setOutputPortData(this.getName() + ".COLOR", "Réparation");
                System.out.println("Réparé");
                stateColor = States.oav;
            }
            // Si panne
        } else if (received.compareTo("Failure") == 0) {
            // Passe en mode panne
            setOutputPortData(this.getName() + ".COLOR", "Panne");
            System.out.println("Cassé");
            stateColor = States.c;
            // Si pieton sur le feux principal 
        } else if (received.compareTo("Walker1") == 0) {   // Passage au rouge si vert
            setOutputPortData(this.getName() + ".COLOR", "Pieton1");
            if (stateColor == States.v) {
                stateColor = States.oar;
            }
        } //Si pieton sur le feux secondaire
        else if (received.compareTo("Walker2") == 0) {
            // Passage au vert si rouge
            setOutputPortData(this.getName() + ".COLOR", "Pieton1");
            if (stateColor == States.r) {
                stateColor = States.oav;
            }
        }
    }
}