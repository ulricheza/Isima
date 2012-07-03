/* 
#-------------------------------------------------------------------------------
# All rights reserved. This program and the accompanying materials
# are made available under the terms of the Eclipse Public License v1.0
# which accompanies this distribution, and is available at
# http://www.eclipse.org/legal/epl-v10.html
#-------------------------------------------------------------------------------
*/

package databasemodeling.requete;

import databasemodeling.Table;

/**
 * Classe modelisant une requete pour ajouter une table dans une BDD
 * @author Maxime ESCOURBIAC - Jean-Christophe SEPTIER
 */
public class RequeteAjoutTable {

    private Table table;

    /**
     * Constructeur par defaut de la classe RequeteAjoutTable
     */
    public RequeteAjoutTable() {
        table = null;
    }

    /**
     * Constructeur par defaut de la classe RequeteAjoutTable
     * @param table Table a ajouter
     */
    public RequeteAjoutTable(Table table) {
        this.table = table;
    }

    /**
     * Getter de la table a ajouter
     * @return La table a ajouter
     */
    public Table getTable() {
        return table;
    }

    /**
     * Setter de la table a ajouter
     * @param table Table a ajouter
     */
    public void setTable(Table table) {
        this.table = table;
    }
}
