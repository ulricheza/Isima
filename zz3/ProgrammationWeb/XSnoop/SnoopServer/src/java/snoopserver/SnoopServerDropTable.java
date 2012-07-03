/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package snoopserver;

import databasemanager.JDBCConnector;
import databasemanager.MySQLConnector;
import databasemanager.OBDCAccessConnector;
import databasemodeling.Context;
import databasemodeling.Table;
import databasemodeling.requete.RequeteSupprTable;
import java.io.IOException;
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
@WebServlet(name = "SnoopServerDropTable", urlPatterns = {"/SnoopServerDropTable"})
public class SnoopServerDropTable extends HttpServlet {

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
        

        //Tentative de connection a la base de donnee
        if (type.compareTo("OBDC") == 0) {
            connector = new OBDCAccessConnector();
        } else {
            if (type.compareTo("MySQL") == 0) {
                connector = new MySQLConnector();
            }
        }

         if (connector != null) {
            if (connector.connect(name,type, adresse, login, password) == true) {
                RequeteSupprTable requete = new RequeteSupprTable(new Table(table));
                connector.dropTable(requete);
                contexte.setBase(connector.inspectDatabase());
                connector.disconnect();
                getServletContext().getRequestDispatcher("/requetetable.jsp").forward(request, response);
            }
         }
         getServletContext().getRequestDispatcher("/errorrequete.jsp").forward(request, response);
    }
}
