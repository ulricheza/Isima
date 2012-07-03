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
 * Classe modelisant une base dans une base de donnee
 * @author Maxime ESCOURBIAC - Jean-Christophe SEPTIER
 */
public class Database {

    private String adress;
    private String name;
    private String type;
    private ArrayList<Table> tables;
    private ArrayList<String> typesSupportes;

    /**
     * Constructeur par defaut de la base
     */
    public Database() {
        tables = new ArrayList<Table>();
    }

    /**
     * Ajout d'une table dans la base
     * @param table Table a ajouter
     */
    public void addTable(Table table) {
        tables.add(table);
    }
    
    public void reInitTable()
    {
        tables.clear();
    }

    /**
     * Getter du nom de la base
     * @return Le nom de la base
     */
    public String getName() {
        return name;
    }

    /**
     * Setter du nom de la base
     * @param name Nom de la base
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * Getter des tables presentes dans la base
     * @return Les tables de la base
     */
    public ArrayList<Table> getTables() {
        return tables;
    }

    /**
     * getter du type
     * @return type de la base de donnee (ex : MySQL etc)
     */
    public String getType() {
        return type;
    }

    /**
     * setter du type
     * @param type Le type de la BDD (ex : MySQL)
     */
    public void setType(String type) {
        this.type = type;
    }

    /**
     * Getter de l'adresse
     * @return L'adresse de la BDD
     */
    public String getAdress() {
        return adress;
    }

    /**
     * Setter de l'adress 
     * @param adress L'adresse de la BDD
     */
    public void setAdress(String adress) {
        this.adress = adress;
    }

    public void setTypesSupportes(ArrayList<String> typesSupportes) {
        this.typesSupportes = typesSupportes;
    }

    public ArrayList<String> getTypesSupportes() {
        return typesSupportes;
    }
}
