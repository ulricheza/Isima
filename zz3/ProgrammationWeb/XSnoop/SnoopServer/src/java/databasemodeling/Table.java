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
 * Classe modelisant une table dans une base de donnee
 * @author Maxime ESCOURBIAC - Jean-Christophe SEPTIER
 */
public class Table {
    
    private String name;
    private ArrayList<Attribut> attributs;
    
    /**
     * Constucteur de la table
     * @param name
     */
    public Table(String name) {
        this.name = name;
        attributs = new ArrayList<Attribut>();
    }
    
    /**
     * Ajout d'un attribut dans la table
     * @param attribut Attribut a ajouter
     */
    public void addAttribut(Attribut attribut) {
        attributs.add(attribut);
    }
    
    /**
     * Getter du nom de la table
     * @return Le nom de la table
     */
    public String getName() {
        return name;
    }
    
    /**
     * Getter des attributs present dans la table
     * @return La liste des attributs present dans la table
     */
    public ArrayList<Attribut> getAttributs() {
        return attributs;
    }
}
