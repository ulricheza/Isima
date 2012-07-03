package trafficsimulation;


/**
 *
 * @author JC
 */
public class Configuration {

    static double tempsSimulation = 1000.0;     // Temps de la simulation
    /*----------------------------------------------------  */
    /* Générateur                                           */
    /*----------------------------------------------------  */
    /**
     * Temps minimum d'apparition d'une évènement
     */
    static int min = 4;
    /**
     * Temps maximum d'apparition d'un évènement
     */
    static int max = 15;
    /**
     * Pourcentage d'avoir un événement : pieton sur le feux principal
     */
    static double pourcentageFeuxPieton = 0.3;
    /**
     * Pourcentage d'avoir un événement : pieton sur le feux secondaire
     */
    static double pourcentageFeuxAuxiliairePieton = 0.3;
    /**
     * Pourcentage d'avoir un événement : panne
     */
    static double pourcentagePanne = 0.2;
    /**
     * Pourcentage d'avoir un événement : patrouille
     */
    static double pourcentagePatrouille = 0.2;
    /*----------------------------------------------------  */
    /* Feux                                                 */
    /*----------------------------------------------------  */
    /**
     * Temps en seconde du feux verts
     */
    static int tempsVert = 5;
    /**
     * Temps en seconde du feux orange
     */
    static int tempsOrange = 2;
    /**
     * Temps en seconde du feux rouge
     */
    static int tempsRouge = 5;
    /**
     * Temps clignotant
     */
    static int tempsClignotant = 1;
}
