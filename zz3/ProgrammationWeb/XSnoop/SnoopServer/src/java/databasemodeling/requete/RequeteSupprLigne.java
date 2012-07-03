/*
 * -------------------------------------------------------------------------------
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *-------------------------------------------------------------------------------"
 */
package databasemodeling.requete;

import databasemodeling.Ligne;
import databasemodeling.Table;

/**
 * Classe modelisant une requete de suppression d'une ligne donnee
 * @author Maxime ESCOURBIAC - Jean-Christophe SEPTIER
 */
public class RequeteSupprLigne {

    private Table table;
    private Ligne ligne;

    /**
     * Constructeur par defaut de la classe RequeteSupprLigne
     */
    public RequeteSupprLigne() {
        table = null;
        ligne = null;
    }

    /**
     * Constructeur de la classe RequeteSupprLigne
     * @param table Table ou la ligne doit etre supprime
     * @param ligne Ligne a supprimer
     */
    public RequeteSupprLigne(Table table, Ligne ligne) {
        this.table = table;
        this.ligne = ligne;
    }

    /**
     * Getter de la ligne a supprimer
     * @return La ligne a supprimer
     */
    public Ligne getLigne() {
        return ligne;
    }

    /**
     * Setter de la ligne a supprimer
     * @param ligne Ligne a supprimer
     */
    public void setLigne(Ligne ligne) {
        this.ligne = ligne;
    }

    /**
     * Getter de la table ou la ligne va etre supprimer
     * @return La table de destination
     */
    public Table getTable() {
        return table;
    }

    /**
     * Setter de la table de destination  
     * @param table Table de destination
     */
    public void setTable(Table table) {
        this.table = table;
    }
}
