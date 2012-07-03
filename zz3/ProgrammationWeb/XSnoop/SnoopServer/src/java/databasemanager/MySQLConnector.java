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
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Connecteur pour les bases de donnees de type MySQL
 * @author Maxime ESCOURBIAC - Jean-Christophe SEPTIER
 */
public class MySQLConnector extends JDBCConnector {

    /**
     * Constructeur du connecteur pour la base MySQL
     */
    public MySQLConnector() {
        super();
        //Construction de liste des types supportes
        ArrayList<String> typesSupportes = new ArrayList<String>();
        typesSupportes.add("INT");
        typesSupportes.add("FLOAT");
        typesSupportes.add("DOUBLE");
        typesSupportes.add("VARCHAR");
        database.setTypesSupportes(typesSupportes);
    }

    /**
     * Methode abstraite de connection a la base de donnee.
     * @param name Nom de la base de donnée.
     * @param type Type de la base de donnnee
     * @param adress Adresse de la base de donnee.
     * @param login Login d'accees.
     * @param password Mot de passe.
     * @return true si la connection a reussi sinon false.
     */
    @Override
    public boolean connect(String name, String type, String adress, String login, String password) {

        boolean connectionSuccess = false;
        try {
            database.setName(name);
            database.setType(type);
            database.setAdress(adress);

            DriverManager.registerDriver(new com.mysql.jdbc.Driver());
            if ((adress.trim()).compareTo("") != 0) {
                link = DriverManager.getConnection("jdbc:mysql://" + adress + "/" + name, login, password);
                connectionSuccess = true;
            }
        } catch (SQLException ex) {
            Logger.getLogger(OBDCAccessConnector.class.getName()).log(Level.WARNING, null, ex);
        }
        return connectionSuccess;
    }

    @Override
    public Resultats request(RequeteInterrogation requete) {

        ArrayList<String> liste = null;
        Resultats resultat = null;
        Object resTemp;

        try {
            //Execution de la requete
            Statement state = (Statement) link.createStatement();
            ResultSet result = state.executeQuery(adaptRequeteInterrogation(requete));
            ResultSetMetaData resultMeta = (ResultSetMetaData) result.getMetaData();
            resultat = new Resultats(requete.getTable().getName());
            //On affiche le nom des colonnes
            liste = new ArrayList<String>();
            for (int i = 1; i <= resultMeta.getColumnCount(); i++) {
                liste.add(resultMeta.getColumnName(i).toUpperCase());
            }
            resultat.setColumName(liste);

            //On recupere les resultats pour les encapsuler dans la classe Resultats
            while (result.next()) {
                liste = new ArrayList<String>();
                for (int i = 1; i <= resultMeta.getColumnCount(); i++) {
                    resTemp = result.getObject(i);
                    //Correction du bug en cas de champs egale a null
                    liste.add((resTemp == null) ? "null" : resTemp.toString());
                }
                resultat.addRow(liste);
            }
            result.close();
            state.close();
        } catch (SQLException ex) {
            Logger.getLogger(MySQLConnector.class.getName()).log(Level.SEVERE, null, ex);
        }
        return resultat;
    }

    /**
     * Methode qui adapte la modelisation de la requete en chaine de
     * caractere pour le moteur de la base de donnee
     * @param requete RequeteInterrogation a adapter.
     * @return La chaine utilisable par le GDBD pour lancer la requete.
     */
    private String adaptRequeteInterrogation(RequeteInterrogation requete) {
        StringBuilder req = new StringBuilder();
        ArrayList<Attribut> attr = requete.getAttributs();
        ArrayList<Contrainte> contr = requete.getContraintes();

        //Comportement par defaut : si aucune clause SELECT => SELECT *
        if (attr.isEmpty() == false) {
            req = req.append("SELECT ").append(attr.get(0).getName());
            for (int i = 1; i < attr.size(); ++i) {
                req = req.append(",").append(attr.get(i).getName());
            }
        } else {
            req = req.append("SELECT * ");
        }

        //Ajout de la clause FROM
        req = req.append(" FROM ").append(requete.getTable().getName());

        //Ajout des contraintes
        if (contr.size() > 0) {
            req = req.append(" WHERE ").append(adaptContrainte(contr.get(0)));
            for (int i = 1; i < contr.size(); ++i) {
                req = req.append(" AND ").append(adaptContrainte(contr.get(i)));
            }
        }
        return req.append(";").toString();
    }

    /**
     * Methode qui adapte la modelisation d'une contrainte en chaine de caractere.
     * @param contrainte Contrainte a adapter.
     * @return La chaine de caractere representant la contrainte.
     */
    private String adaptContrainte(Contrainte contrainte) {
        Attribut attr = contrainte.getAttribut();

        String operateur = "";
        String valeur = "";
        // Le choix pour MySQL a ete fait de ne pas utiliser les operateurs de comparaison
        // LIKE et NOT LIKE car on a choisit que la comparaison devrait pas etre sensible
        // a la casse.
        switch (contrainte.getOperateur()) {
            case EGAL:
                operateur = " = ";
                break;
            case DIFFERENT:
                operateur = " != ";
                break;
            case INFERIEUR:
                operateur = " < ";
                break;
            case INFERIEUREGAL:
                operateur = " <= ";
                break;
            case SUPERIEUR:
                operateur = " > ";
                break;
            case SUPERIEUREGAL:
                operateur = " >= ";
                break;
        }

        if (contrainte.getAttribut().getType().contains("CHAR") == true) {
            valeur = "\"" + contrainte.getValeur() + "\"";
        } else {
            valeur = contrainte.getValeur();
        }

        return (attr.getName() + operateur + valeur);
    }

    @Override
    public boolean addTable(RequeteAjoutTable requete) {

        boolean valid = false;
        try {
            Statement state = (Statement) link.createStatement();
            state.executeUpdate(adaptRequeteAjoutTable(requete));
            valid = true;
        } catch (SQLException ex) {
            Logger.getLogger(MySQLConnector.class.getName()).log(Level.SEVERE, null, ex);
        }
        return valid;
    }

    private String adaptRequeteAjoutTable(RequeteAjoutTable requete) {
        String mysql = "";
        Table table = requete.getTable();
        ArrayList<Attribut> attributs = table.getAttributs();
        ArrayList<Attribut> primary = new ArrayList<Attribut>();
        Attribut attr = null;

        if (attributs.size() > 0) {
            mysql = "CREATE TABLE " + table.getName() + "( ";
            
            //ajout du premier element
            attr = attributs.get(0);
            mysql += attr.getName() + " " + attr.getType();
            if (attr.isPrimaryKey()) {
                primary.add(attr);
            }

            //ajout des autres elements
            for (int i = 1; i < attributs.size(); ++i) {
                attr = attributs.get(i);
                mysql += "," + attr.getName() + " " + attr.getType();
                if (attr.isPrimaryKey()) {
                    primary.add(attr);
                }
            }

            //gestion de l'insertion des cles primaires
            for (Attribut at : primary) {
                mysql += ", PRIMARY KEY (" + at.getName() + ")";
            }
            mysql += ");";
        }
        return mysql;
    }

    @Override
    public boolean addRow(RequeteAjoutLigne requete) {
        boolean valid = false;
        try {
            Statement state = (Statement) link.createStatement();
            String query = adaptRequeteAjoutLigne(requete);
            state.executeUpdate(query);
            valid = true;
        } catch (SQLException ex) {
            Logger.getLogger(MySQLConnector.class.getName()).log(Level.SEVERE, null, ex);
        }
        return valid;
    }

    private String adaptRequeteAjoutLigne(RequeteAjoutLigne requete) {
        String mysql = "";
        Table table = requete.getTable();
        ArrayList<Attribut> attributs = requete.getLigne().getAttributs();
        Attribut attr;

        if (attributs.size() > 0) {
            mysql = "INSERT INTO " + table.getName() + "( ";
            
            //Ajout du premier nom
            attr = attributs.get(0);
            mysql += attr.getName();

            //ajout des autres nom
            for (int i = 1; i < attributs.size(); ++i) {
                attr = attributs.get(i);
                mysql += "," + attr.getName();
            }
            mysql += ") VALUES(";
            
            //ajout de la premiere valeur
            attr = attributs.get(0);
            if (attr.getType().contains("CHAR") == true) {
                mysql += "\"" + attr.getValeur() + "\"";
            } else {
                mysql += attr.getValeur();
            }
            
            //ajout des autres valeurs
            for (int i = 1; i < attributs.size(); ++i) {
                attr = attributs.get(i);
                mysql += ",";
                if (attr.getType().contains("CHAR") == true) {
                    mysql += "\"" + attr.getValeur() + "\"";
                } else {
                    mysql += attr.getValeur();
                }
            }
            mysql += ");";
        }
        return mysql;
    }

    @Override
    public boolean dropTable(RequeteSupprTable requete) {
        boolean valid = false;
        try {
            Statement state = (Statement) link.createStatement();
            state.executeUpdate("DROP TABLE " + requete.getTable().getName() + ";");
            valid = true;
        } catch (SQLException ex) {
            Logger.getLogger(MySQLConnector.class.getName()).log(Level.SEVERE, null, ex);
        }
        return valid;
    }

    @Override
    public boolean dropRow(RequeteSupprLigne requete) {
        boolean valid = false;
        try {
            Statement state = (Statement) link.createStatement();
            state.executeUpdate(adaptRequeteSupprLigne(requete));
            valid = true;
        } catch (SQLException ex) {
            Logger.getLogger(MySQLConnector.class.getName()).log(Level.SEVERE, null, ex);
        }
        return valid;
    }

    private String adaptRequeteSupprLigne(RequeteSupprLigne requete) {
        String mysql = "";
        String valeur;
        Table table = requete.getTable();
        ArrayList<Attribut> attributs = requete.getLigne().getAttributs();
        Attribut attr;

        if (attributs.size() > 0) {
            mysql = "DELETE FROM " + table.getName() + " WHERE ";
           
            //premier attribut
            attr = attributs.get(0);
            if (attr.getType().contains("CHAR") == true) {
                valeur = "\"" + attr.getValeur() + "\"";
            } else {
                valeur = attr.getValeur();
            }
            mysql += attr.getName() + " = " + valeur;

            //autres attributs
            for (int i = 1; i < attributs.size(); ++i) {
                attr = attributs.get(i);
                if (attr.getType().contains("CHAR") == true) {
                    valeur = "\"" + attr.getValeur() + "\"";
                } else {
                    valeur = attr.getValeur();
                }
                mysql += " AND " + attr.getName() + " = " + valeur;
            }
            mysql += ";";
        }
        System.out.println(mysql);
        return mysql;
    }
}
