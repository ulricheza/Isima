/*
 * -------------------------------------------------------------------------------
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *-------------------------------------------------------------------------------"
 */
package databasemanager;

import databasemodeling.*;
import databasemodeling.requete.*;
import java.sql.Connection;
import java.sql.DatabaseMetaData;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Classe abstraite regroupant tous les connecteurs des bases de donnees
 * @author Maxime ESCOURBIAC - Jean-Christophe SEPTIER
 */
public abstract class JDBCConnector {

    /**
     * Element de connection du connector
     */
    protected Connection link;
    /**
     * Squellette de la base de donnee
     */
    protected Database database;

    /**
     * Constructeur de la classe JDBCConnector
     */
    public JDBCConnector() {
        database = new Database();
    }

    /**
     * Methode abstraite de connection a la base de donnee.
     * @param name Nom de la base de donnée.
     * @param type Type de la base de donnee (ex: MySQL, OBDC etc...)
     * @param adress Adresse de la base de donnee.
     * @param login Login d'accees.
     * @param password Mot de passe.
     * @return true si la connection a reussi sinon false.
     */
    public abstract boolean connect(String name, String type, String adress, String login, String password);

    /**
     * Methode d'execution de la requete par la base de donnee
     * @param requete RequeteInterrogation a executer par la base de donnee
     * @return Le resultat de la requete
     */
    public abstract Resultats request(RequeteInterrogation requete);

    /**
     * Methode d'ajout d'une table
     * @param requete Requete a executer
     * @return true si la requete a ete bien execute
     */
    public abstract boolean addTable(RequeteAjoutTable requete);

    /**
     * Methode d'ajout d'une valeur
     * @param requete Requete a executer
     * @return true si la requete a ete bien execute
     */
    public abstract boolean addRow(RequeteAjoutLigne requete);

    /**
     * Methode de suppression d'une ligne de resultat
     * @param requete Requete a executer
     * @return true si la requete a ete bien execute
     */
    public abstract boolean dropRow(RequeteSupprLigne requete);

    /**
     * Methode de suppression d'une table
     * @param requete Requete a executer
     * @return true si la rquete a ete bien execute
     */
    public abstract boolean dropTable(RequeteSupprTable requete);

    /**
     * Methode d'inspection des metadonnees de la base.
     * @return Le squelette de la base de donnee
     */
    public Database inspectDatabase() {

        ResultSet answerTable, answerAttribut;
        DatabaseMetaData patrol;
        Table table;
        String[] filterUser = {"TABLE"};

        database.reInitTable();

        try {
            patrol = link.getMetaData();
            //Recuperation des tables USER
            answerTable = patrol.getTables(null, null, null, filterUser);
            while (answerTable.next()) {
                if (answerTable.wasNull() == false) {
                    table = new Table(answerTable.getString("TABLE_NAME"));
                    //Recuperation de la liste des attributs de la table
                    answerAttribut = patrol.getColumns(null, null, table.getName(), null);
                    while (answerAttribut.next()) {
                        if (answerAttribut.wasNull() == false) {
                            table.addAttribut(new Attribut(answerAttribut.getString("COLUMN_NAME"), answerAttribut.getString("TYPE_NAME")));
                        }
                    }
                    answerAttribut.close();
                    database.addTable(table);
                }
            }
            answerTable.close();
        } catch (SQLException ex) {
            database = null;
            Logger.getLogger(JDBCConnector.class.getName()).log(Level.SEVERE, null, ex);
        }
        return database;
    }

    /**
     * Methode de deconnection propre de la base
     */
    public void disconnect() {
        try {
            if (link != null) {
                link.close();
            }
        } catch (SQLException ex) {
            Logger.getLogger(JDBCConnector.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    /**
     * Getter de la structure de la BDD observe
     * @return le squellete base de donnee
     */
    public Database getDatabase() {
        return database;
    }
}
