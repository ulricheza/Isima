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
import databasemodeling.Table;
import databasemodeling.requete.RequeteAjoutLigne;
import java.io.IOException;
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
@WebServlet(name = "SnoopServerAddRow", urlPatterns = {"/SnoopServerAddRow"})
public class SnoopServerAddRow extends HttpServlet {

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
        String table = request.getParameter("Tables");
        contexte = (Context) session.getAttribute("contexte");
        String adresse = contexte.getBase().getAdress();
        String name = contexte.getBase().getName();
        String login = contexte.getLogin();
        String password = contexte.getPassword();
        String type = contexte.getBase().getType();
        Database base = contexte.getBase();


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
                Table tab = null;
                Table temp;
                String value;
                int i = 0;
                while (tab == null && i < listTable.size()) {
                    temp = listTable.get(i++);
                    if (temp.getName().contains(table) == true) {
                        tab = temp;
                    }
                }

                if (tab != null) {
                    Ligne ligne = new Ligne();
                    ArrayList<Attribut> attributs = tab.getAttributs();

                    for (Attribut attr : attributs) {
                        value = request.getParameter(attr.getName());
                        ligne.addAttribut(new Attribut(attr.getName(), attr.getType(), value));
                    }
                    RequeteAjoutLigne requete = new RequeteAjoutLigne(tab, ligne);
                    if (connector.addRow(requete) == true) {
                        connector.inspectDatabase();
                        contexte.setBase(connector.getDatabase());
                        connector.disconnect();
                        getServletContext().getRequestDispatcher("/requetetable.jsp").forward(request, response);
                    }
                }
            }
        }
        getServletContext().getRequestDispatcher("/errorrequete.jsp").forward(request, response);
    }
}
