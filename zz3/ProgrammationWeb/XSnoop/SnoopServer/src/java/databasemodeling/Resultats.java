/*
 * -------------------------------------------------------------------------------
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *-------------------------------------------------------------------------------"
 */
package databasemodeling;

import java.util.ArrayList;

/**
 * Classe modelisant les resultats retournes par un SGBD 
 * @author Maxime ESCOURBIAC - Jean-Christophe SEPTIER
 */
public class Resultats {

    private String table;
    private ArrayList<ArrayList<String>> result;

    /**
     * Constructeur de la classe Resultat
     */
    public Resultats() {
        this.result = new ArrayList<ArrayList<String>>();
        this.table = null;
    }

    public Resultats(String table) {
        this.table = table;
        this.result = new ArrayList<ArrayList<String>>();
    }

    /**
     * Retourne la liste des attributs demandes
     * @return la liste des attributs demandes
     */
    public ArrayList<String> getColumnName() {
        return result.get(0);
    }

    /**
     * Ajoute la ligne des attributs
     * @param row La liste des attributs
     */
    public void setColumName(ArrayList<String> row) {
        result.add(0, row);
    }

    public String getTable() {
        return table;
    }

    public void setTable(String table) {
        this.table = table;
    }

    
    /**
     * Recupepere la ieme liste des resultat
     * @param i indice de la ligne
     * @return Une ligne de resultat
     * 
     * Attention les lignes de resultat sont compris entre 1 et size
     */
    public ArrayList<String> getRow(int i) {
        ArrayList<String> res = null;
        if( i > 0 && i < result.size())
            res = result.get(i);
        return res;
    }

    /**
     * Ajoute une ligne de resultat
     * @param row La ligne de resultat a ajouter
     */
    public void addRow(ArrayList<String> row) {
        result.add(row);
    }

    /**
     * Retourne le nombre de ligne de resultat presente dans la structure de resultat
     * @return le nombre de ligne de resultat effective
     */
    public int nbResult() {
        return java.lang.Math.max(result.size() - 1, 0);
    }
}
