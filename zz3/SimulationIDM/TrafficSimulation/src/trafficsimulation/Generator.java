package trafficsimulation;

import model.AtomicModel;
import exception.DEVS_Exception;
import types.DEVS_Enum;
import java.util.*;

/**
 * Générateur d'événement pour les feux
 * @author Jean-Christophe SEPTIER Maxime ESCOURBIAC
 */
public class Generator extends AtomicModel {

    private Random rd;
    /*
     * Probabilité des évênements
     */
    double p1;
    double p2;
    double p3;

    /**
     * Constructeur du générateur
     * @param name nom du générateur
     */
    public Generator(String name, String desc) {
        super(name, desc);

        // Construit un OutputPort pour envoyer les pannes
        String[] commands = {"Failure", "Recovery", "WalkerAuxiliaire", "Walker"};
        addOutputPortStructure(new DEVS_Enum(commands), this.getName() + ".OUT", "My single output port");

        // Initialise le Random
        rd = new Random();

        // Initialise les probabilités
        p1 = Configuration.pourcentageFeuxPieton;
        p2 = Configuration.pourcentageFeuxAuxiliairePieton + p1;
        p3 = Configuration.pourcentagePanne + p2;
    }

    @Override
    public void deltaInt() {
        // Rien
    }

    @Override
    public double ta() {
        // Retourne le temps du prochain évenement
        return (rd.nextDouble() * Configuration.max + Configuration.min);
    }

    @Override
    public void lambda() throws DEVS_Exception {
        // Récupère un nombre entre 0 et 1
        double probaEvenement = rd.nextDouble();
        String toSend;

        // Envoie un message
        if (probaEvenement < p1) {
            toSend = "Walker1";
        } else if (probaEvenement < p2) {
            toSend = "Walker2";
        } else if (probaEvenement < p3) {
            toSend = "Failure";
        } else {
            toSend = "Recovery";
        }
        // Envoie l'évênement
        setOutputPortData(this.getName() + ".OUT", toSend);
    }

    @Override
    public void deltaExt(double e) throws DEVS_Exception {
        // Not defined, since there is no input
    }
}