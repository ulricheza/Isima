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
 * Classe modelisant une requete de duppression d'une table donnee
 * @author Maxime ESCOURBIAC - Jean-Christophe SEPTIER
 */
public class RequeteSupprTable {
    
    private Table table;
    
    /**
     * Constructeur par defaut de la table RequeteSupprTable
     */
    public RequeteSupprTable()
    {
        table = null;
    }
    
    /**
     * Constructeur de la table RequeteSupprTable
     * @param table Table a supprimer
     */
    public RequeteSupprTable(Table table)
    {
        this.table = table;
    }

    /**
     * Getter de la table a supprimer
     * @return La table a supprimer
     */
    public Table getTable() {
        return table;
    }

    /**
     * Setter de la table a supprimer
     * @param table La table a supprimer
     */
    public void setTable(Table table) {
        this.table = table;
    }
}
