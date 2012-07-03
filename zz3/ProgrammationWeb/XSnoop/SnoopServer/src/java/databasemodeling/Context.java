/*
 * -------------------------------------------------------------------------------
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *-------------------------------------------------------------------------------"
 */
package databasemodeling;

/**
 * Classe modelisant le contrexte de travail pour la communication entre servlet
 * @author Maxime ESCOURBIQC - Jean-Christophe SEPTIER
 */
public class Context {

    private String login;
    private String password;
    private Database base;
    private Resultats resultats;


    /**
     * Constructeur de la classe Context
     * @param login Login utilise pour la connexion
     * @param password Password utilise pour la connexion
     */
    public Context(String login, String password) {
        this.login = login;
        this.password = password;
    }

    /**
     * Constructeur de la classe Context
     * @param login Login utilise pour la connexion
     * @param password Password utilise pour la connexion
     * @param base Squelette de la base recupere lors de la connection
     */
    public Context(String login, String password, Database base) {
        this.login = login;
        this.password = password;
        this.base = base;
    }

    /**
     * Getter de la base de donnee
     * @return Le squelette de la BDD
     */
    public Database getBase() {
        return base;
    }

    /**
     * Setter de la base de donnee
     * @param base Le squelette de la BDD
     */
    public void setBase(Database base) {
        this.base = base;
    }

    /**
     * getter du login
     * @return Le login utilise lors de la connection
     */
    public String getLogin() {
        return login;
    }

    /**
     * setter du login
     * @param login Le login utilise pour la connection
     */
    public void setLogin(String login) {
        this.login = login;
    }

    /**
     * getter du password
     * @return Le password utilise pour la connection
     */
    public String getPassword() {
        return password;
    }

    /**
     * setter du password
     * @param password Password utilise pour la connection
     */
    public void setPassword(String password) {
        this.password = password;
    }

    /**
     * Getter des resultats
     * @return Le resultats retournes par le SGBD
     */
    public Resultats getResultats() {
        return resultats;
    }

    /**
     * Setter des resultats
     * @param resultats Les resultats retournes par le SGBD
     */
    public void setResultats(Resultats resultats) {
        this.resultats = resultats;
    }
}
