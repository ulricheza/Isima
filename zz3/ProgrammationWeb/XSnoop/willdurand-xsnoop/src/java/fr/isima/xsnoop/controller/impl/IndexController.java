package fr.isima.xsnoop.controller.impl;

import fr.isima.xsnoop.controller.AbstractController;
import fr.isima.xsnoop.controller.ControllerInterface;
import fr.isima.xsnoop.exception.MethodNotAllowedException;
import fr.isima.xsnoop.exception.UnauthorizedException;
import fr.isima.xsnoop.model.Table;
import fr.isima.xsnoop.request.HttpServletRequest;
import fr.isima.xsnoop.service.Introspector;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import javax.servlet.http.HttpServletResponse;
import org.apache.commons.lang3.StringUtils;

/**
 * @author William Durand <william.durand1@gmail.com>
 */
public class IndexController extends AbstractController implements ControllerInterface {

    /**
     * Introspector
     */
    Introspector introspector;

    /**
     * Constructor
     */
    public IndexController() {
        try {
            introspector = new Introspector(new com.mysql.jdbc.Driver());
        } catch (SQLException e) {
            LOGGER.log(Level.SEVERE, "SQLException in constructor: {0}", e);
        }
    }

    /**
     * This action displays a form to fill in the database name
     */
    @Override
    public void indexAction(HttpServletRequest request, HttpServletResponse response)
    throws Exception {
        // Preset an attribute with an empty string
        request.setAttribute("selected_database_name", "");
    }

    /**
     * Once we get the database name, we can introspect it, and then to list
     * all table names. This action can be called by a `POST` request exclusively.
     */
    public void selectTableAction(HttpServletRequest request, HttpServletResponse response)
    throws MethodNotAllowedException, UnauthorizedException {
        if (request.isPost() || request.isGet()) {
            String databaseName = request.getParameter("database_name");

            if (StringUtils.isBlank(databaseName)) {
                request.addError("You have to select a database name.");
                // set the current view as there are errors
                setView("index");
            } else {
                List<Table> list = null;

                String username = "";
                String password = "";
                if (request.isAuthenticated()) {
                    username = request.getUser().getUsername();
                    password = request.getUser().getPassword();
                }

                try {
                    introspector.initConnection(databaseName, username, password);
                    list = introspector.getTables();
                } catch (SQLException e) {
                    LOGGER.log(Level.SEVERE, "SQLException in selectTableAction: {0}", e.getMessage());

                    request.addError(e.getMessage());
                }

                try {
                    introspector.closeConnection();
                } catch (SQLException e) {
                    LOGGER.log(Level.SEVERE, "SQLException in selectTableAction: {0}", e.getMessage());

                    request.addError(e.getMessage());
                }

                request.setAttribute("table_names", list);
                request.setAttribute("selected_database_name", databaseName);

                // Prevent null pointer exception
                request.setAttribute("selected_table_name", "");
            }
        } else {
            throw new MethodNotAllowedException();
        }
    }

    /**
     * We now can display a list of columns to use in our SQL query.
     * This action can be called by a `POST` request exclusively.
     */
    public void selectColumnsAction(HttpServletRequest request, HttpServletResponse response)
    throws MethodNotAllowedException, UnauthorizedException {
        if (request.isPost()) {
            String databaseName = request.getParameter("database_name");
            String tableName    = request.getParameter("table_name");

            List<Table> listTables = null;

            String username = "";
            String password = "";
            if (request.isAuthenticated()) {
                username = request.getUser().getUsername();
                password = request.getUser().getPassword();
            }

            try {
                introspector.initConnection(databaseName, username, password);
                listTables = introspector.getTables();
            } catch (SQLException e) {
                LOGGER.log(Level.SEVERE, "SQLException in selectColumnsAction: {0}", e.getMessage());

                request.addError(e.getMessage());
            }

            if (tableName.isEmpty()) {
                request.addError("You have to select a table name.");
                // set the current view as there are errors
                setView("selectTable");
            } else {
                request.setAttribute("selected_table_name", tableName);

                try {
                    // Get columns from the given table
                    request.setAttribute("column_names", introspector.getColumnsForTable(tableName, null));
                } catch (SQLException e) {
                    LOGGER.log(Level.SEVERE, "SQLException in selectColumnsAction: {0}", e.getMessage());

                    request.addError(e.getMessage());
                }

                // Prevent null pointer exception
                request.setAttribute("selected_column_names", new ArrayList<String>());
            }

            request.setAttribute("selected_database_name", databaseName);
            request.setAttribute("table_names", listTables);

            try {
                introspector.closeConnection();
            } catch (SQLException e) {
                LOGGER.log(Level.SEVERE, "SQLException in selectColumnsAction: {0}", e.getMessage());

                request.addError(e.getMessage());
            }
        } else {
            throw new MethodNotAllowedException();
        }
    }
}