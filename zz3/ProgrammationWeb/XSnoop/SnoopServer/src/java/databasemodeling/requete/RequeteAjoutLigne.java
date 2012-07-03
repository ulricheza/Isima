/*
#-------------------------------------------------------------------------------
# All rights reserved. This program and the accompanying materials
# are made available under the terms of the Eclipse Public License v1.0
# which accompanies this distribution, and is available at
# http://www.eclipse.org/legal/epl-v10.html
#-------------------------------------------------------------------------------
*/

package databasemodeling.requete;

import databasemodeling.Ligne;
import databasemodeling.Table;

/**
 * Classe modelisant une requete pour ajouter une ligne dans une table
 * @author Maxime ESCOURBIAC - Jean-Christophe SEPTIER
 */
public class RequeteAjoutLigne {

    private Table table;
    private Ligne ligne;

    /**
     * Constructeur par defaut de la classe RequeteAjoutLigne
     */
    public RequeteAjoutLigne() {
        table = null;
        ligne = null;
    }

    public RequeteAjoutLigne(Table table) {
        this.table = table;
        this.ligne = null;
    }

    /**
     * Constructeur de la classe RequeteAjoutLigne
     * @param table Table ou la ligne va etre ajoute
     * @param ligne Ligne a ajouter
     */
    public RequeteAjoutLigne(Table table, Ligne ligne) {
        this.table = table;
        this.ligne = ligne;
    }

    /**
     * Getter de la ligne a ajouter
     * @return La ligne a ajouter 
     */
    public Ligne getLigne() {
        return ligne;
    }

    /**
     * Setter de la ligne a ajouter
     * @param ligne La ligne a ajouter
     */
    public void setLigne(Ligne ligne) {
        this.ligne = ligne;
    }

    /**
     * Getter de la table de destination
     * @return La table de destination
     */
    public Table getTable() {
        return table;
    }

    /**
     * Setter de la table de destination
     * @param table de destination
     */
    public void setTable(Table table) {
        this.table = table;
    }
}
