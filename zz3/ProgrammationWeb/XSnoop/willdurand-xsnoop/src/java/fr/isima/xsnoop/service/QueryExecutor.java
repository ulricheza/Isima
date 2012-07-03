package fr.isima.xsnoop.service;

import fr.isima.xsnoop.model.Column;
import java.sql.*;
import java.util.*;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * @author William Durand <william.durand1@gmail.com>
 */
public class QueryExecutor {

    /**
     * Logger
     */
    final static private Logger LOGGER = Logger.getLogger(QueryExecutor.class.getName());

    /**
     * Connection
     */
    private Connection connection = null;

    public QueryExecutor(Driver driver) {
        try {
            DriverManager.registerDriver(driver);
        } catch (SQLException e) {
             LOGGER.log(Level.SEVERE, "Cannot register the driver: {0}", driver);
        }
    }

    public void initConnection(String dsn, String username, String password)
    throws SQLException {
        if (connection != null) {
            closeConnection();
        }

        connection = DriverManager.getConnection(dsn, username, password);
    }

    public void closeConnection()
    throws SQLException {
        if (connection != null) {
            connection.close();
        }
    }

    public List<Map<Column, String>> execute(String query, List<Column> columns, boolean limit) {
        PreparedStatement stmt;
        List<Map<Column, String>> results = new ArrayList<Map<Column, String>>();

        if (limit) {
            // Limit results for the preview
            query += " LIMIT 0, 6";
        }

        try {
            stmt = connection.prepareStatement(query);
            ResultSet res = stmt.executeQuery();

            while (res.next()) {
                Map<Column, String> row = new HashMap<Column, String>();
                Iterator<Column> it = columns.iterator();
                while (it.hasNext()) {
                    Column c = (Column) it.next();
                    row.put(c, res.getString(c.getName()));
                }
                results.add(row);
            }
        } catch (SQLException e) {
            LOGGER.log(Level.SEVERE, "Exception catched while executing a query: {0}", e.getMessage());

            return results;
        }

        return results;
    }

    public void executeUpdate(String query)
    throws SQLException {
        PreparedStatement stmt;

        try {
            stmt = connection.prepareStatement(query);
            stmt.executeUpdate();
        } catch (SQLException e) {
            LOGGER.log(Level.SEVERE, "Exception catched while creating a new table: {0}", e.getMessage());

            throw e;
        }
    }

    public void deleteFromTable(String tableName, String pkName, String value)
    throws SQLException {
        PreparedStatement stmt = null;

        try {
            stmt = connection.prepareStatement("DELETE FROM " + tableName + " WHERE " + pkName + " = ?");
            stmt.setInt(1, Integer.parseInt(value));
            stmt.executeUpdate();
        } catch (SQLException e) {
            LOGGER.log(Level.SEVERE, "Exception catched while creating a new table: {0}", e.getMessage());

            throw e;
        }
    }

    public void deleteTable(String tableName)
    throws SQLException {
        PreparedStatement stmt = null;

        try {
            stmt = connection.prepareStatement("DROP TABLE " + tableName);
            stmt.executeUpdate();
        } catch (SQLException e) {
            LOGGER.log(Level.SEVERE, "Exception catched while deleting a table: {0}", e.getMessage());

            throw e;
        }
    }

    public void truncateTable(String tableName)
    throws SQLException {
       PreparedStatement stmt = null;

        try {
            stmt = connection.prepareStatement("TRUNCATE TABLE " + tableName);
            stmt.executeUpdate();
        } catch (SQLException e) {
            LOGGER.log(Level.SEVERE, "Exception catched while truncating a table: {0}", e.getMessage());

            throw e;
        }
    }
}