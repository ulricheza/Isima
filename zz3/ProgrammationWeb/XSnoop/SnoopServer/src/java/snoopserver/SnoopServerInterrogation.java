/*
 * -------------------------------------------------------------------------------
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *-------------------------------------------------------------------------------"
 */
package snoopserver;

import databasemanager.JDBCConnector;
import databasemanager.MySQLConnector;
import databasemanager.OBDCAccessConnector;
import databasemodeling.Attribut;
import databasemodeling.Context;
import databasemodeling.Contrainte;
import databasemodeling.Database;
import databasemodeling.Operator;
import databasemodeling.requete.RequeteInterrogation;
import databasemodeling.Resultats;
import databasemodeling.Table;
import java.io.IOException;
import java.util.ArrayList;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

/**
 * Servlet d'execution de requete
 * @author Maxime ESCOURBIAC - Jean-Christophe SEPTIER
 */
@WebServlet(name = "SnoopServerInterrogation", urlPatterns = {"/SnoopServerInterrogation"})
public class SnoopServerInterrogation extends HttpServlet {

    /** 
     * Handles the HTTP <code>POST</code> method.
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        JDBCConnector connector = null;
        Resultats resultat = null;
        HttpSession session = request.getSession();
        Context contexte = (Context) session.getAttribute("contexte");

        //Recuperation des parametres de la page de connection.
        Database base = contexte.getBase();
        String adresse = base.getAdress();
        String type = base.getType();
        String name = base.getName();
        String login = contexte.getLogin();
        String password = contexte.getPassword();

        //Tentative de connection a la base de donnee
        if (type.compareTo("OBDC") == 0) {
            connector = new OBDCAccessConnector();
        } else {
            if (type.compareTo("MySQL") == 0) {
                connector = new MySQLConnector();
            }
        }

        if (connector != null) {
            if (connector.connect(name, type, adresse, login, password) == true) {

                ArrayList<Table> listTable = base.getTables();
                String table = request.getParameter("Tables");
                Table tab = null;
                Table temp;
                String value;
                int i = 0;
                //Recherche de la table
                while (tab == null && i < listTable.size()) {
                    temp = listTable.get(i++);
                    if (temp.getName().contains(table) == true) {
                        tab = temp;
                    }
                }

                if (tab != null) {
                    ArrayList<Attribut> attributs = tab.getAttributs();
                    ArrayList<Attribut> attrReq = new ArrayList<Attribut>();

                    //Construction des attributs
                    for (Attribut attr : attributs) {
                        if (request.getParameter(attr.getName()) != null) {
                            attrReq.add(attr);
                        }
                    }

                    //Construction des contraintes
                    String nbContrainteS = request.getParameter("nbContrainte");
                    int nbContrainte = Integer.parseInt(nbContrainteS);
                    Attribut attrCon = null;
                    Attribut attrtemp;
                    Operator operator;
                    String valeur;
                    String indice;
                    String tempC;
                    ArrayList<Attribut> attrA = tab.getAttributs();
                    ArrayList<Contrainte> contraintes = new ArrayList<Contrainte>();

                    for (i = 1; i <= nbContrainte; ++i) {
                        indice = String.valueOf(i);
                        tempC = request.getParameter("TableContrainte_" + i);
                        //recherche de l'attribut correspondant
                        int j = 0;
                        while (attrCon == null && j < attrA.size()) {
                            attrtemp = attrA.get(j++);
                            if (attrtemp.getName().contains(tempC) == true) {
                                attrCon = attrtemp;
                            }
                        }

                        tempC = request.getParameter("TableComp_" + i);
                        if (tempC.compareTo("CompSup") == 0) {
                            operator = Operator.SUPERIEUR;
                        } else {
                            if (tempC.compareTo("CompInf") == 0) {
                                operator = Operator.INFERIEUR;
                            } else {
                                if (tempC.compareTo("CompSupEg") == 0) {
                                    operator = Operator.SUPERIEUREGAL;
                                } else {
                                    if (tempC.compareTo("CompInfEg") == 0) {
                                        operator = Operator.INFERIEUREGAL;
                                    } else {
                                        if (tempC.compareTo("CompEg") == 0) {
                                            operator = Operator.EGAL;
                                        } else {
                                            operator = Operator.DIFFERENT;
                                        }
                                    }
                                }
                            }
                        }

                        valeur = request.getParameter("valeur_" + i);
                        contraintes.add(new Contrainte(attrCon, valeur, operator));
                    }

                    RequeteInterrogation requete = new RequeteInterrogation(attrReq, tab, contraintes);
                    resultat = connector.request(requete);
                    connector.disconnect();
                    if (resultat != null) {
                        contexte.setResultats(resultat);
                        session.setAttribute("contexte", contexte);
                        getServletContext().getRequestDispatcher("/resultattable.jsp").forward(request, response);
                    }
                }

            }
        }
        getServletContext().getRequestDispatcher("/errorrequete.jsp").forward(request, response);
    }
}
