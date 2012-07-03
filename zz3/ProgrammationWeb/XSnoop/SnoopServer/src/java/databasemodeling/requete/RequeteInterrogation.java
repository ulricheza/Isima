/*
 * -------------------------------------------------------------------------------
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *-------------------------------------------------------------------------------"
 */
package databasemodeling.requete;

import databasemodeling.Attribut;
import databasemodeling.Contrainte;
import databasemodeling.Table;
import java.util.ArrayList;

/**
 * Classe modelisant une requete d'interogation a executer pour un SGBD
 * @author Maxime ESCOURBIAC - Jean-Christophe SEPTIER
 */
public class RequeteInterrogation {

    private ArrayList<Attribut> attributs;
    private Table table;
    private ArrayList<Contrainte> contraintes;

    /**
     * Constructeur de la clsse RequeteInterrogation
     */
    public RequeteInterrogation() {
    }

    public RequeteInterrogation(ArrayList<Attribut> attributs, Table table, ArrayList<Contrainte> contraintes) {
        this.attributs = attributs;
        this.table = table;
        this.contraintes = contraintes;
    }

    /**
     * getter des attributs
     * @return La liste des attributs que retournera le SGBD
     */
    public ArrayList<Attribut> getAttributs() {
        return attributs;
    }

    /**
     * setter des attributs
     * @param attributs La liste des attributs que retournera le SGBD
     */
    public void setAttributs(ArrayList<Attribut> attributs) {
        this.attributs = attributs;
    }

    /**
     * Getters des contraintes
     * @return La liste des contraintes
     */
    public ArrayList<Contrainte> getContraintes() {
        return contraintes;
    }

    /**
     * Setter des contriantes
     * @param contraintes la liste des contraintes
     */
    public void setContraintes(ArrayList<Contrainte> contraintes) {
        this.contraintes = contraintes;
    }

    /**
     * Getter de la table
     * @return La table ou sera execute la requete
     */
    public Table getTable() {
        return table;
    }

    /**
     * Setter de la table
     * @param table La table ou sera execute la requete
     */
    public void setTable(Table table) {
        this.table = table;
    }
}
