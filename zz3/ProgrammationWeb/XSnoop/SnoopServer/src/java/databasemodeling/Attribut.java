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
 * Classe modelisant un attribut dans une base de donnee
 * @author Maxime ESCOURBIAC - Jean-Christophe SEPTIER
 */
public class Attribut {

    private String name;
    private String type;
    private String valeur;
    private boolean primaryKey;

    /**
     * Constructeur de la classe Attribut
     * @param name Nom de l'attribut
     * @param type Type de l'attribut
     */
    public Attribut(String name, String type) {
        this.name = name;
        this.type = type;
        this.valeur = null;
        this.primaryKey = false;
    }

    /**
     * Constructeur de la classe Attribut
     * @param name
     * @param type
     * @param primary
     */
    public Attribut(String name, String type, boolean primary) {
        this.name = name;
        this.type = type;
        this.primaryKey = primary;
        this.valeur = null;
    }

    /**
     * Constructeur de la classe Attribut
     * @param name
     * @param type
     * @param valeur
     */
    public Attribut(String name, String type, String valeur) {
        this.name = name;
        this.type = type;
        this.valeur = valeur;
        this.primaryKey = false;
    }

    /**
     * Getter du nom de l'attribut
     * @return Nom de l'attribut
     */
    public String getName() {
        return name;
    }

    /**
     * Getter du type de l'attribut
     * @return Type de l'attribut sous forme de String
     */
    public String getType() {
        return type;
    }

    /**
     * getter de la valeur de l'attribut
     * @return la valeur de l'attribut
     */
    public String getValeur() {
        return valeur;
    }

    /**
     * Setter de la valeur de l'attribut
     * @param valeur Valeur de l'attribut
     */
    public void setValeur(String valeur) {
        this.valeur = valeur;
    }

    /**
     * Setter du booleen de cle primaire
     * @param primaryKey
     */
    public void setPrimaryKey(boolean primaryKey) {
        this.primaryKey = primaryKey;
    }

    /**
     * Methode de test si l'attribut est une cle primaire de la table
     * @return true si l'attribut est cle primaire
     */
    public boolean isPrimaryKey() {
        return primaryKey;
    }
}
