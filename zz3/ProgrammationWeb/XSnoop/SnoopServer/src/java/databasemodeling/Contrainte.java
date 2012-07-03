/*
 * -------------------------------------------------------------------------------
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *-------------------------------------------------------------------------------"
 */
package databasemodeling;

/**
 * Classe modelisant une contrainte pour une requete donnee
 * @author Maxime ESCOURBIAC - Jean-Christophe SEPTIER
 */
public class Contrainte {
    private Attribut attribut;
    private String valeur;
    private Operator operateur;

    /**
     * Constructeur oar defaut de la classe contrainte
     */
    public Contrainte() {
    }
    
    /**
     * Constructeur de la classe Contrainte.
     * @param attribut Attribut de la contrainte.
     * @param valeur Valeur de la contrainte.
     * @param operator Operateur de comparaison de la contrainte.
     */
    public Contrainte(Attribut attribut, String valeur, Operator operator)
    {
        this.attribut = attribut;
        this.valeur = valeur;
        this.operateur = operator;
    }
    
    /**
     * Getter de l'attribut
     * @return L'attribut a utiliser pour la contrainte
     */
    public Attribut getAttribut() {
        return attribut;
    }

    /**
     * Setter de l'attribut
     * @param attribut L'attribut a utiliser pour la contrainte
     */
    public void setAttribut(Attribut attribut) {
        this.attribut = attribut;
    }

    /**
     * Getter de l'operateur
     * @return L'operateur de comparaison
     */
    public Operator getOperateur() {
        return operateur;
    }

    /**
     * Setter de l'operateur
     * @param operateur Operateur de comparaison
     */
    public void setOperateur(Operator operateur) {
        this.operateur = operateur;
    }

    /**
     * Getter de la valeur
     * @return La valeur de reference de la comparaison
     */
    public String getValeur() {
        return valeur;
    }

    /**
     * Setter de la valeur
     * @param valeur Valeur de reference de la comparaison
     */
    public void setValeur(String valeur) {
        this.valeur = valeur;
    }
}
