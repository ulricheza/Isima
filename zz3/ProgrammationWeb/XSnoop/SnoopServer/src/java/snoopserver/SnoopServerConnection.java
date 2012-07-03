/*
 * -------------------------------------------------------------------------------
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *-------------------------------------------------------------------------------"
 */
package snoopserver;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import databasemanager.JDBCConnector;
import databasemanager.MySQLConnector;
import databasemanager.OBDCAccessConnector;
import databasemodeling.Context;
import databasemodeling.Database;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpSession;

/**
 * Servlet de connection 
 * @author Maxime ESCOURBIAC - Jean-Christophe SEPTIER
 */
@WebServlet(name = "SnoopServerConnection", urlPatterns = {"/SnoopServerConnection"})
public class SnoopServerConnection extends HttpServlet {

    /** 
     * Handles the HTTP <code>POST</code> method.
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

        JDBCConnector connector = null;
        Database base = null;
        Context contexte = null;
        HttpSession session = null;

        //Recuperation des parametres de la page de connection.
        String adresse = request.getParameter("adress");
        String type = request.getParameter("type");
        String login = request.getParameter("login");
        String password = request.getParameter("password");
        String name = request.getParameter("name");

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
                base = connector.inspectDatabase();
                connector.disconnect();
                if (base != null) {
                    contexte = new Context(login, password, base);
                    session = request.getSession(true);
                    session.setAttribute("contexte", contexte);
                    connector.disconnect();
                    getServletContext().getRequestDispatcher("/requetetable.jsp").forward(request, response);
                }
            }
        }

        getServletContext().getRequestDispatcher("/errorconnection.jsp").forward(request, response);
    }
}
