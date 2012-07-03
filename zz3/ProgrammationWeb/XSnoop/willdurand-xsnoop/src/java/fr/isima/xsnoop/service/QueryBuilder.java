package fr.isima.xsnoop.service;

import fr.isima.xsnoop.model.Column;
import java.util.Iterator;
import java.util.List;
import org.apache.commons.lang3.StringUtils;

/**
 * @author William Durand <william.durand1@gmail.com>
 */
public class QueryBuilder {

    public String createQuery(String table, List<Column> columns) {
        if (StringUtils.isBlank(table)) {
            throw new IllegalArgumentException("A table name is mandatory to create a SQL query");
        }

        StringBuilder sb = new StringBuilder();
        sb.append("SELECT ");

        if (columns.isEmpty()) {
            sb.append("*");
        } else {
            for (Column col : columns) {
                sb.append(col.getName());
                sb.append(", ");
            }

            // just delete the extra comma
            sb.delete(sb.length() - 2, sb.length());
        }

        sb.append(" FROM ");
        sb.append(table);

        return sb.toString();
    }

    public String createTableQuery(String table, List<Column> columns) {
        if (StringUtils.isBlank(table)) {
            throw new IllegalArgumentException("A table name is mandatory to create a new table.");
        }

        if (columns == null || columns.isEmpty()) {
            throw new IllegalArgumentException("You must define columns in order to create a new table.");
        }

        StringBuilder query = new StringBuilder("CREATE TABLE ");

        query.append(table);
        query.append(" ");
        query.append("(");

        for (Column c : columns) {
            query.append(c.getName());
            query.append(" ");
            query.append(c.getType());

            if (c.isPrimaryKey()) {
                query.append(" PRIMARY KEY");
            }

            if (c.isUnique()) {
                query.append(" UNIQUE");
            }

            query.append(", ");
        }

        query.delete(query.length() - 2, query.length());
        query.append(")");

        return query.toString();
    }

    public String createInsertQuery(String tableName, List<Column> columns, List<String> columnValues) {
        StringBuilder sb = new StringBuilder("INSERT INTO ");
        sb.append(tableName);
        sb.append(" (");

        StringBuilder sb2 = new StringBuilder("VALUES (");

        Iterator<String> it = columnValues.iterator();
        for (Column c : columns) {
            sb.append(c.getName());
            sb.append(", ");

            // Needs escaping?
            if (!c.isNumeric()) {
                sb2.append("\"");
                sb2.append(it.next());
                sb2.append("\"");
            } else {
                sb2.append(it.next());
            }

            sb2.append(", ");
        }

        sb.delete(sb.length() - 2, sb.length());
        sb.append(")");

        sb2.delete(sb2.length() - 2, sb2.length());
        sb2.append(")");

        return sb.append(sb2.toString()).toString();
    }
}
