/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package snoopserver;

import databasemanager.JDBCConnector;
import databasemanager.MySQLConnector;
import databasemanager.OBDCAccessConnector;
import databasemodeling.Attribut;
import databasemodeling.Context;
import databasemodeling.Database;
import databasemodeling.Ligne;
import databasemodeling.Resultats;
import databasemodeling.Table;
import databasemodeling.requete.RequeteSupprLigne;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

/**
 *
 * @author Maxime
 */
@WebServlet(name = "SnoopServerDropRow", urlPatterns = {"/SnoopServerDropRow"})
public class SnoopServerDropRow extends HttpServlet {

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
        HttpSession session = request.getSession();
        Context contexte;

        //On recupere les valeurs envoye par la page et par la session
        contexte = (Context) session.getAttribute("contexte");
        String adresse = contexte.getBase().getAdress();
        String name = contexte.getBase().getName();
        String login = contexte.getLogin();
        String password = contexte.getPassword();
        String type = contexte.getBase().getType();
        Database base = contexte.getBase();
        Resultats resultat = contexte.getResultats();
        String table = resultat.getTable();
        ArrayList<String> column;
        ArrayList<String> row;
        ArrayList<Table> listeTable = base.getTables();

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
                int nbresult = resultat.nbResult();
                column = resultat.getColumnName();
                Table tableRequete = null;
                //Creation de la table
                int i = 0;
                while (tableRequete == null && i < listeTable.size()) {
                    if (table.compareTo(listeTable.get(i).getName()) == 0) {
                        tableRequete = listeTable.get(i);
                    }
                    ++i;
                }

                if (tableRequete != null) {

                    String nameC;
                    String typeA;
                    String valeurA;
                    ArrayList<Attribut> listeAttribut = tableRequete.getAttributs();

                    for (i = 1; i <= nbresult; ++i) {
                        if (request.getParameter("sup_" + i) != null) {
                            row = resultat.getRow(i);
                            typeA = null;
                            Ligne ligne = new Ligne();
                            for (int j = 0; j < row.size(); ++j) {
                                nameC = column.get(j).toLowerCase();
                                valeurA = row.get(j);
                                int k = 0;
                                while (typeA == null && k < listeAttribut.size()) {
                                    if (nameC.compareTo(listeAttribut.get(k).getName()) == 0) {
                                        typeA = listeAttribut.get(k).getType();
                                    }
                                    ++k;
                                }

                                if (typeA != null) {
                                    ligne.addAttribut(new Attribut(nameC, typeA, valeurA));
                                }
                            }
                            RequeteSupprLigne requete = new RequeteSupprLigne(tableRequete, ligne);
                            connector.dropRow(requete);
                        }
                    }
                    connector.disconnect();
                    getServletContext().getRequestDispatcher("/requetetable.jsp").forward(request, response);
                }
            }
        }
        getServletContext().getRequestDispatcher("/errorrequete.jsp").forward(request, response);
    }
}
