package trafficsimulation;

import exception.DEVS_Exception;
import model.AtomicModel;
import types.DEVS_Enum;
import types.DEVS_Real;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 * Feux secondaire
 * @author Jean-Christophe SEPTIER Maxime ESCOURBIAC
 */
public class TrafficLightSecondaire extends AtomicModel {
    // Si le feux est cassé

    Boolean casse = false;

    // Listes des états
    enum States {

        v, // Vert
        oar, // Orange avant rouge
        oav, // Orange avant 
        r, // Rouge
        co, // Cassé orange
        c,     // Cassé jaune
    }
    // Liste des couleurs
    String[] couleurs = {"2vert", "2orange", "2rouge", "2eteint"};
    // Etat du feux
    States stateColor;

    /**
     * Constructeur
     * @param name nom du modèle
     * @param desc description du modèle
     */
    public TrafficLightSecondaire(String name, String desc) {
        super(name, desc);

        // Entrée des couleurs du feux principals
        addInputPortStructure(new DEVS_Enum(couleurs), this.getName() + ".COMMANDCOLOR", "Data to store");

        // Entrée des évènements
        String[] commands = {"Failure", "Recovery"};
        addInputPortStructure(new DEVS_Enum(commands), this.getName() + ".COMMAND", "Trigger received");

        // Envoie des couleurs du feux secondaire
        addOutputPortStructure(new DEVS_Enum(couleurs), this.getName() + ".COLOR", "Color sent out for users");

        stateColor = States.v;
    }

    @Override
    public void lambda() throws DEVS_Exception {
    }

    @Override
    public void deltaInt() {
    }

    @Override
    public void deltaExt(double d) throws DEVS_Exception {

        String received = getInputPortData(this.getName() + ".COMMAND").toString();

        // Met en pannes
        if (received.compareTo("Failure") == 0 && !casse) {
            setOutputPortData(this.getName() + ".COLOR", "Panne");
            System.out.println("2Casse");
            stateColor = States.c;
            casse = true;
        }

        // Répare
        if (received.compareTo("Recovery") == 0) {
            casse = false;
        }

        // Récupère la couleur du feux principal et prend la couleur inverse
        String received2 = getInputPortData(this.getName() + ".COMMANDCOLOR").toString();
        if (!casse) {
            if (received2.compareTo("rouge") == 0) {
                setOutputPortData(this.getName() + ".COLOR", "2vert");
                stateColor = States.v;
            }
            if (received2.compareTo("orange") == 0) {
                setOutputPortData(this.getName() + ".COLOR", "2orange");
                stateColor = States.oar;
            }
            if (received2.compareTo("vert") == 0) {
                setOutputPortData(this.getName() + ".COLOR", "2rouge");
                stateColor = States.r;
            }
        } else {
            // Si une panne, met la meme couleur que le feux
            if (received2.compareTo("eteint") == 0) {
                setOutputPortData(this.getName() + ".COLOR", "2eteint");
                stateColor = States.c;
            }
            if (received2.compareTo("orange") == 0) {
                setOutputPortData(this.getName() + ".COLOR", "2orange");
                stateColor = States.co;
            }
        }

    }

    @Override
    public double ta() {
        return DEVS_Real.POSITIVE_INFINITY;
    }
}
