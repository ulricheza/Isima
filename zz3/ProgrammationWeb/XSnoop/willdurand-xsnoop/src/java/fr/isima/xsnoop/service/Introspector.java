package fr.isima.xsnoop.service;

import fr.isima.xsnoop.model.Column;
import fr.isima.xsnoop.model.Table;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Logger;

/**
 * @author William Durand <william.durand1@gmail.com>
 */
public class Introspector {

    /**
     * Logger
     */
    final static protected Logger LOGGER = Logger.getLogger(Introspector.class.getName());

    /**
     */
    Connection connection = null;

    public Introspector(Driver driver)
    throws SQLException {
        DriverManager.registerDriver(driver);
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

    public List<Table> getTables()
    throws SQLException {
        List<Table> list = new ArrayList<Table>();

        ResultSet res = connection.getMetaData().getTables(connection.getCatalog(), null, null, new String[] { "TABLE" });

        while (res.next()) {
            list.add(new Table(res.getString("TABLE_NAME")));
        }

        res.close();

        return list;
    }

    public List<Column> getColumnsForTable(String tableName, List<String> filterColumns)
    throws SQLException {
        List<String> pks = new ArrayList<String>();
        List<Column> list = new ArrayList<Column>();

        boolean filter = filterColumns != null && !filterColumns.isEmpty();

        ResultSet res = connection.getMetaData()
                .getPrimaryKeys(connection.getCatalog(), null, tableName);

        while (res.next()) {
            pks.add(res.getString("COLUMN_NAME"));
        }

        res = connection.getMetaData()
                .getColumns(connection.getCatalog(), null, tableName, null);

        while (res.next()) {
            if (filter && !filterColumns.contains(res.getString("COLUMN_NAME"))) {
                continue;
            }

            list.add(new Column(
                res.getString("COLUMN_NAME"), res.getString("TYPE_NAME"), pks.contains(res.getString("COLUMN_NAME"))
            ));
        }

        res.close();

        return list;
    }
}
