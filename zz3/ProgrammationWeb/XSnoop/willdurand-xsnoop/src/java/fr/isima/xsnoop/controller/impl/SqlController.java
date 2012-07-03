package fr.isima.xsnoop.controller.impl;

import fr.isima.xsnoop.controller.AbstractController;
import fr.isima.xsnoop.controller.ControllerInterface;
import fr.isima.xsnoop.exception.MethodNotAllowedException;
import fr.isima.xsnoop.exception.PageNotFoundException;
import fr.isima.xsnoop.exception.UnauthorizedException;
import fr.isima.xsnoop.exception.UnsupportedFormatException;
import fr.isima.xsnoop.model.Column;
import fr.isima.xsnoop.model.Table;
import fr.isima.xsnoop.request.HttpServletRequest;
import fr.isima.xsnoop.serializer.JsonSerializer;
import fr.isima.xsnoop.service.Introspector;
import fr.isima.xsnoop.service.QueryBuilder;
import fr.isima.xsnoop.service.QueryExecutor;
import fr.isima.xsnoop.view.utils.Inflector;
import java.sql.SQLException;
import java.text.MessageFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Map;
import java.util.logging.Level;
import javax.servlet.http.HttpServletResponse;
import org.apache.commons.lang3.StringUtils;

/**
 * @author William Durand <william.durand1@gmail.com>
 */
public class SqlController extends AbstractController implements ControllerInterface {

    /**
     * Introspector
     */
    Introspector introspector;

    public SqlController()
    {
        try {
            introspector = new Introspector(new com.mysql.jdbc.Driver());
        } catch (SQLException e) {
            LOGGER.log(Level.SEVERE, "SQLException in constructor: {0}", e);
        }
    }

    /**
     * Nothing to do...
     */
    @Override
    public void indexAction(HttpServletRequest request, HttpServletResponse response)
    throws Exception {
        throw new PageNotFoundException();
    }

    /**
     * Once we get all SQL parts, we can create a complete SQL query.
     * This action can be called by a `POST` request exclusively.
     */
    public void createQueryAction(HttpServletRequest request, HttpServletResponse response)
    throws MethodNotAllowedException, UnauthorizedException {
        if (request.isPost()) {
            String databaseName   = request.getParameter("database_name");
            String tableName      = request.getParameter("table_name");
            String [] columnNames = request.getParameterValues("column_names[]");

            // Selected data
            request.setAttribute("selected_table_name", tableName);
            request.setAttribute("selected_database_name", databaseName);

            List<Table> listTables = null;
            List<Column> listColumns = null;
            List<Column> listSelectedColumns = null;

            String username = "";
            String password = "";
            if (request.isAuthenticated()) {
                username = request.getUser().getUsername();
                password = request.getUser().getPassword();
            }

            try {
                introspector.initConnection(databaseName, username, password);
                listTables = introspector.getTables();
                listColumns = introspector.getColumnsForTable(tableName, null);
                listSelectedColumns = introspector.getColumnsForTable(tableName, Arrays.asList(columnNames));
            } catch (SQLException e) {
                LOGGER.log(Level.SEVERE, "SQLException in createQueryAction: {0}", e.getMessage());

                request.addError(e.getMessage());
            }

            try {
                introspector.closeConnection();
            } catch (SQLException e) {
                LOGGER.log(Level.SEVERE, "SQLException in createQueryAction: {0}", e.getMessage());

                request.addError(e.getMessage());
            }

            request.setAttribute("table_names", listTables);
            request.setAttribute("column_names", listColumns);

            if (columnNames != null) {
                request.setAttribute("selected_column_names", Arrays.asList(columnNames));
            } else {
                request.setAttribute("selected_column_names", new ArrayList<String>());
            }

            if (!listSelectedColumns.isEmpty()) {
                // Handle * special case
                if (listSelectedColumns.size() == listColumns.size()) {
                    listSelectedColumns.clear();
                    listSelectedColumns.add(new Column("*"));
                }

                // Create SQL query
                QueryBuilder builder = new QueryBuilder();
                String query = builder.createQuery(tableName, listSelectedColumns);

                request.setAttribute("query", query);

            } else {
                request.addError("You have to select at least one column.");
                // set the current view as there are errors
                setView("index/selectColumns");
            }
        } else {
            throw new MethodNotAllowedException();
        }
    }

    /**
     * This action executes the SQL query with a limit of 10 result rows, and returns
     * a JSON representation of results.
     * This action can be called by a `POST` request and a `JSON` format exclusively.
     */
    public void previewAction(HttpServletRequest request, HttpServletResponse response)
    throws MethodNotAllowedException, UnsupportedFormatException, UnauthorizedException {
        if (!request.isPost()) {
            throw new MethodNotAllowedException();
        }

        if (!request.getFormat().equals(fr.isima.xsnoop.request.HttpServletRequest.FORMAT_JSON)) {
            throw new UnsupportedFormatException(request.getFormat());
        }

        String databaseName   = request.getParameter("database_name");
        String tableName      = request.getParameter("table_name");
        String [] columnNames = request.getParameterValues("column_names[]");

        String username = "";
        String password = "";
        if (request.isAuthenticated()) {
            username = request.getUser().getUsername();
            password = request.getUser().getPassword();
        }

        List<Column> columns = null;
        try {
            introspector.initConnection(databaseName, username, password);
            columns = introspector.getColumnsForTable(tableName, Arrays.asList(columnNames));
            introspector.closeConnection();
        } catch (SQLException e) {
            LOGGER.log(Level.SEVERE, "SQLException in createQuery: {0}", e.getMessage());

            request.addError(e.getMessage());
        }

        if (!columns.isEmpty()) {
            List<Map<Column, String>> results = createQuery(request, databaseName, tableName, columns, true);

            JsonSerializer serializer = new JsonSerializer();
            List<String> humanizedColumns = new ArrayList<String>();

            for (String col : columnNames) {
                humanizedColumns.add(Inflector.humanize(col));
            }

            request.setAttribute("humanized_columns", serializer.serializeList(humanizedColumns));
            request.setAttribute("results", serializer.serializeResultSet(results, columns));
        } else {
            request.setAttribute("error", "You should select at least one column.");
        }
    }

    /**
     * This action executes the SQL query and displays results.
     */
    public void executeAction(HttpServletRequest request, HttpServletResponse response)
    throws UnauthorizedException {
        String databaseName   = request.getParameter("database_name");
        String tableName      = request.getParameter("table_name");
        String [] columnNames = request.getParameterValues("column_names[]");

        request.setAttribute("selected_database_name", databaseName);
        request.setAttribute("selected_table_name", tableName);

        String username = "";
        String password = "";
        if (request.isAuthenticated()) {
            username = request.getUser().getUsername();
            password = request.getUser().getPassword();
        }

        List<Column> columns = null;
        try {
            introspector.initConnection(databaseName, username, password);
            columns = introspector.getColumnsForTable(tableName, Arrays.asList(columnNames));
            introspector.closeConnection();
        } catch (SQLException e) {
            LOGGER.log(Level.SEVERE, "SQLException in createQuery: {0}", e.getMessage());

            request.addError(e.getMessage());
        }

        if (columnNames != null) {
            List<Map<Column, String>> results = createQuery(request, databaseName, tableName, columns, false);
            request.setAttribute("results", results);
        } else {
            request.addError("You have to select at least one column.");
            // set the current view as there are errors
            setView("sql/createQuery");
        }
    }

    /**
     * Create a new table in a given database.
     * You cannot acccess this action if you're not authenticated.
     */
    public void createTableAction(HttpServletRequest request, HttpServletResponse response)
    throws UnauthorizedException {
        if (!request.isAuthenticated()) {
            throw new UnauthorizedException();
        }

        String databaseName = request.getParameter("database_name");

        if (StringUtils.isBlank(databaseName)) {
            request.addError("The database name has to be defined in order to create a new table.");

            redirectTo("/xsnoop/pages/index");
        }

        request.setAttribute("database_name", databaseName);
    }

    /**
     * This action is useful in the table creation process. It allows to add columns
     * to a almost-created table.
     * You cannot acccess this action if you're not authenticated.
     */
    public void addColumnsAction(HttpServletRequest request, HttpServletResponse response)
    throws UnauthorizedException, MethodNotAllowedException {
        if (!request.isAuthenticated()) {
            throw new UnauthorizedException();
        }

        if (request.isPost()) {
            String tableName = request.getParameter("table_name");
            String databaseName = request.getParameter("database_name");

            if (StringUtils.isBlank(tableName)) {
                request.addError("The table name cannot be left blank.");
            } else if (StringUtils.isBlank(databaseName)) {
                request.addError("The database name cannot be left blank.");
            }

            request.setAttribute("table_name", tableName);
            request.setAttribute("database_name", databaseName);

            String [] columns_name = request.getParameterValues("columns_name[]");
            String [] columns_type = request.getParameterValues("columns_type[]");
            String [] columns_pk   = request.getParameterValues("columns_pk[]");

            if (columns_name != null) {
                request.setAttribute("columns_names", columns_name);

                if (columns_type.length != columns_name.length) {
                    request.addError("You should define a type per column.");
                } else {
                    request.setAttribute("columns_type", columns_type);

                    List<Column> cols = new ArrayList<Column>();
                    for (int i = 0; i < columns_name.length; i++) {
                        boolean isPk = Arrays.asList(columns_pk).contains(String.valueOf(i));

                        cols.add(new Column(columns_name[i], columns_type[i], isPk));
                    }

                    QueryBuilder builder = new QueryBuilder();
                    QueryExecutor executor = null;
                    String sql = null;

                    try {
                        sql = builder.createTableQuery(tableName, cols);
                    } catch (IllegalArgumentException e) {
                        LOGGER.log(Level.SEVERE, "Exception catched while creating SQL for table creation: {0}", e.getMessage());

                        request.addError(e.getMessage());
                    }

                    if (sql != null) {
                        try {
                            executor = new QueryExecutor(new com.mysql.jdbc.Driver());
                            executor.initConnection(databaseName, request.getUser().getUsername(), request.getUser().getPassword());
                            LOGGER.log(Level.INFO, "Generated the following SQL: {0}", sql);

                            executor.executeUpdate(sql);
                        } catch (Exception e) {
                            LOGGER.log(Level.SEVERE, "Exception catched while creating a new table: {0}", e.getMessage());

                            StringBuilder sb = new StringBuilder(e.getMessage());
                            sb.append("<br />Generated SQL: <code>");
                            sb.append(sql);
                            sb.append("</code>");

                            request.addError(sb.toString());
                        }

                        try {
                            executor.closeConnection();
                        } catch (Exception e) {
                            LOGGER.log(Level.SEVERE, "Exception catched while closing executor connection: {0}", e.getMessage());
                        }
                    }

                    if (request.getErrors().isEmpty()) {
                        request.addInfo(MessageFormat.format("The table <strong>{0}</strong> has been successfully created! You may be able to retrieve it in the list below.", tableName));
                        redirectTo("/xsnoop/pages/index/selectTable?database_name=" + databaseName);
                    }
                }
            } else {
                request.addError("You should add some columns to your table.");
            }

            setView("sql/createTable");
        } else {
            throw new MethodNotAllowedException();
        }
    }

    /**
     * This action is designed to delete a row, in a given database, and for a given table.
     * You cannot acccess this action if you're not authenticated.
     */
    public void deleteRowAction(HttpServletRequest request, HttpServletResponse response)
    throws UnauthorizedException {
        if (!request.isAuthenticated()) {
            throw new UnauthorizedException();
        }

        String databaseName = request.getParameter("database");
        String tableName = request.getParameter("table");
        String pk = request.getParameter("pk");
        String val = request.getParameter(pk);

        try {
            QueryExecutor executor = new QueryExecutor(new com.mysql.jdbc.Driver());

            executor.initConnection(databaseName, request.getUser().getUsername(), request.getUser().getPassword());
            executor.deleteFromTable(tableName, pk, val);
            executor.closeConnection();

            request.addInfo("Row successfully deleted.");
        } catch (Exception e) {
            LOGGER.log(Level.SEVERE, "Exception catched in deleteRowAction: {0}", e.getMessage());

            StringBuilder sb = new StringBuilder("Can't delete row from table ");
            sb.append(tableName);
            sb.append(" with ");
            sb.append(pk);
            sb.append(" = ");
            sb.append(val);

            request.addError(sb.toString());
        }

        redirectTo("/xsnoop/pages/index/selectTable?database_name=" + databaseName);
    }

    /**
     * List all tables for a given database, and provides actions for each of them.
     * You cannot acccess this action if you're not authenticated.
     */
    public void manageTablesAction(HttpServletRequest request, HttpServletResponse response)
    throws MethodNotAllowedException, PageNotFoundException, UnauthorizedException {
        if (!request.isAuthenticated()) {
            throw new UnauthorizedException();
        }

        String databaseName = request.getParameter("database_name");

        if (StringUtils.isBlank(databaseName)) {
            throw new PageNotFoundException();
        }

        if (request.isGet()) {
            request.setAttribute("database_name", databaseName);

            List<Table> tables = null;

            try {
                introspector.initConnection(databaseName, request.getUser().getUsername(), request.getUser().getPassword());
                tables = introspector.getTables();
            } catch (SQLException e) {
                LOGGER.log(Level.SEVERE, "SQLException in manageTablesAction: {0}", e.getMessage());

                request.addError(e.getMessage());
            }

            try {
                introspector.closeConnection();
            } catch (SQLException e) {
                LOGGER.log(Level.SEVERE, "SQLException in manageTablesAction: {0}", e.getMessage());

                request.addError(e.getMessage());
            }

            request.setAttribute("tables", tables);
        } else {
            throw new MethodNotAllowedException();
        }
    }

    /**
     * This action is designed to insert a new row. It dynamically create a
     * form based on columns types. This is not perfect but it works.
     * You cannot acccess this action if you're not authenticated.
     */
    public void insertRowAction(HttpServletRequest request, HttpServletResponse response)
    throws MethodNotAllowedException, PageNotFoundException, UnauthorizedException {
        if (!request.isAuthenticated()) {
            throw new UnauthorizedException();
        }

        String databaseName = request.getParameter("database_name");
        String tableName = request.getParameter("table_name");

        if (StringUtils.isBlank(databaseName)) {
            throw new PageNotFoundException();
        }

        if (request.isGet() || request.isPost()) {
            if (StringUtils.isBlank(tableName)) {
                request.addError("Select a table in order to insert a new row.");
            } else {
                List<Column> columns = null;

                try {
                    introspector.initConnection(databaseName, request.getUser().getUsername(), request.getUser().getPassword());
                    columns = introspector.getColumnsForTable(tableName, null);
                } catch (Exception e) {
                    LOGGER.log(Level.SEVERE, "Exception catched in insertRowAction: {0}", e.getMessage());

                    request.addError(e.getMessage());
                }

                try {
                    introspector.closeConnection();
                } catch (Exception e) {
                    LOGGER.log(Level.SEVERE, "Exception catched in insertRowAction: {0}", e.getMessage());

                    request.addError(e.getMessage());
                }

                if (request.isGet()) {
                    request.setAttribute("columns", columns);
                    request.setAttribute("table_name", tableName);
                } else {
                    List<Column> colToInsert = new ArrayList<Column>();
                    List<String> colValues = new ArrayList<String>();

                    for (Column c : columns) {
                        String v = request.getParameter(c.getName());

                        if (v != null) {
                            colToInsert.add(c);
                            colValues.add(v);
                        }
                    }

                    QueryExecutor executor = null;
                    String sql = "";

                    try {
                        executor = new QueryExecutor(new com.mysql.jdbc.Driver());
                        executor.initConnection(databaseName, request.getUser().getUsername(), request.getUser().getPassword());
                        sql = new QueryBuilder().createInsertQuery(tableName, colToInsert, colValues);

                        executor.executeUpdate(sql);

                        request.addInfo(MessageFormat.format("New row for table <strong>{0}</strong> successfully inserted.", tableName));
                    } catch (Exception e) {
                        LOGGER.log(Level.SEVERE, "Exception catched in insertRowAction: {0}", e.getMessage());

                        request.addError(MessageFormat.format("{0}<br />SQL generated: {1}", e.getMessage(), sql));
                    }

                    try {
                        if (executor != null) {
                            executor.closeConnection();
                        }
                    } catch (Exception e) {
                        LOGGER.log(Level.SEVERE, "Exception catched in insertRowAction: {0}", e.getMessage());

                        request.addError(e.getMessage());
                    }

                    redirectTo("/xsnoop/pages/index/selectTable?database_name=" + databaseName);
                }
            }
        } else {
            throw new MethodNotAllowedException();
        }
    }

    /**
     * Delete a table in a given database.
     * You cannot acccess this action if you're not authenticated.
     */
    public void deleteTableAction(HttpServletRequest request, HttpServletResponse response)
    throws MethodNotAllowedException, PageNotFoundException, UnauthorizedException {
        if (!request.isAuthenticated()) {
            throw new UnauthorizedException();
        }

        String databaseName = request.getParameter("database_name");

        if (StringUtils.isBlank(databaseName)) {
            throw new PageNotFoundException();
        }

        if (request.isGet()) {
            String tableName = request.getParameter("table_name");

            if (StringUtils.isBlank(tableName)) {
                request.addError("Select a table to delete");
            } else {
                QueryExecutor executor = null;

                try {
                    executor = new QueryExecutor(new com.mysql.jdbc.Driver());
                    executor.initConnection(databaseName, request.getUser().getUsername(), request.getUser().getPassword());
                    executor.deleteTable(tableName);

                    request.addInfo(MessageFormat.format("Table <strong>{0}</strong> successfully deleted.", tableName));
                } catch (Exception e) {
                    LOGGER.log(Level.SEVERE, "Exception catched in deleteTableAction: {0}", e.getMessage());

                    request.addError(e.getMessage());
                }

                try {
                    if (executor != null) {
                        executor.closeConnection();
                    }
                } catch (Exception e) {
                    LOGGER.log(Level.SEVERE, "Exception catched in deleteTableAction: {0}", e.getMessage());

                    request.addError(e.getMessage());
                }

                redirectTo("/xsnoop/pages/index/selectTable?database_name=" + databaseName);
            }
        } else {
            throw new MethodNotAllowedException();
        }
    }

    /**
     * Truncate a given table in a given database. Really close to the delete table action.
     * You cannot acccess this action if you're not authenticated.
     */
    public void truncateTableAction(HttpServletRequest request, HttpServletResponse response)
    throws MethodNotAllowedException, PageNotFoundException, UnauthorizedException {
        if (!request.isAuthenticated()) {
            throw new UnauthorizedException();
        }

        String databaseName = request.getParameter("database_name");

        if (StringUtils.isBlank(databaseName)) {
            throw new PageNotFoundException();
        }

        if (request.isGet()) {
            String tableName = request.getParameter("table_name");

            if (StringUtils.isBlank(tableName)) {
                request.addError("Select a table to truncate");
            } else {
                QueryExecutor executor = null;

                try {
                    executor = new QueryExecutor(new com.mysql.jdbc.Driver());
                    executor.initConnection(databaseName, request.getUser().getUsername(), request.getUser().getPassword());
                    executor.truncateTable(tableName);

                    request.addInfo(MessageFormat.format("Table <strong>{0}</strong> successfully truncated.", tableName));
                } catch (Exception e) {
                    LOGGER.log(Level.SEVERE, "Exception catched in truncateTableAction: {0}", e.getMessage());

                    request.addError(e.getMessage());
                }

                try {
                    if (executor != null) {
                        executor.closeConnection();
                    }
                } catch (Exception e) {
                    LOGGER.log(Level.SEVERE, "Exception catched in truncateTableAction: {0}", e.getMessage());

                    request.addError(e.getMessage());
                }

                redirectTo("/xsnoop/pages/index/selectTable?database_name=" + databaseName);
            }
        } else {
            throw new MethodNotAllowedException();
        }
    }

    /**
     * This action is designed to execute RAW SQL.
     * You cannot acccess this action if you're not authenticated.
     */
    public void rawSqlAction(HttpServletRequest request, HttpServletResponse response)
    throws UnauthorizedException, PageNotFoundException {
        if (!request.isAuthenticated()) {
            throw new UnauthorizedException();
        }

        String databaseName = request.getParameter("database_name");

        if (StringUtils.isBlank(databaseName)) {
            throw new PageNotFoundException();
        }

        request.setAttribute("database_name", databaseName);

        if (request.isPost()) {
            String rawSql = request.getParameter("sql");

            if (StringUtils.isBlank(rawSql)) {
                request.addError("You cannot execute empty SQL statements.");
            } else {
                QueryExecutor executor = null;

                try {
                    executor = new QueryExecutor(new com.mysql.jdbc.Driver());
                    executor.initConnection(databaseName, request.getUser().getUsername(), request.getUser().getPassword());
                    executor.executeUpdate(rawSql);

                    request.addInfo(MessageFormat.format("The following SQL: <code>{0}</code> has been executed.", rawSql));
                } catch (Exception e) {
                    LOGGER.log(Level.SEVERE, "Exception catched in rawSqlAction: {0}", e.getMessage());

                    request.addError(e.getMessage());
                }

                try {
                    if (executor != null) {
                        executor.closeConnection();
                    }
                } catch (Exception e) {
                    LOGGER.log(Level.SEVERE, "Exception catched in rawSqlAction: {0}", e.getMessage());

                    request.addError(e.getMessage());
                }

                request.setAttribute("sql", rawSql);

                if (request.getErrors().isEmpty()) {
                    redirectTo("/xsnoop/pages/index/selectTable?database_name=" + databaseName);
                }
            }
        }
    }

    /**
     * Private method to create a query. Both actions execute and preview do the same
     * work, that's why this method exist. It handles the common logic for these actions.
     */
    private List<Map<Column, String>> createQuery(HttpServletRequest request, String databaseName, String tableName, List<Column> columns, boolean limitResults) {
        // Create SQL query
        QueryBuilder builder = new QueryBuilder();
        String query = builder.createQuery(tableName, columns);

        QueryExecutor executor = null;
        List<Map<Column, String>> results = null;

        String username = "";
        String password = "";
        if (request.isAuthenticated()) {
            username = request.getUser().getUsername();
            password = request.getUser().getPassword();
        }

        try {
            executor = new QueryExecutor(new com.mysql.jdbc.Driver());

            executor.initConnection(databaseName, username, password);
            results = executor.execute(query, columns, limitResults);
        } catch (SQLException e) {
            LOGGER.log(Level.SEVERE, "SQLException in createQuery: {0}", e.getMessage());

            request.addError(e.getMessage());
        }

        try {
            executor.closeConnection();
        } catch (SQLException e) {
            LOGGER.log(Level.SEVERE, "SQLException in createQuery: {0}", e.getMessage());

            request.addError(e.getMessage());
        }

        request.setAttribute("query", query);
        request.setAttribute("columns", columns);

        return results;
    }
}