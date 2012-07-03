package fr.isima.xsnoop.service;

import fr.isima.xsnoop.model.Column;
import java.util.ArrayList;
import java.util.List;
import static org.junit.Assert.assertEquals;
import org.junit.Before;
import org.junit.Test;

/**
 * @author William Durand <william.durand1@gmail.com>
 */
public class QueryBuilderTest {

    private QueryBuilder builder;

    @Before
    public void setUp() {
        builder = new QueryBuilder();
    }

    @Test
    public void testCreateQuery() {
        String table = "foo";
        List<Column> columns = new ArrayList<Column>();
        columns.add(new Column("col1"));
        columns.add(new Column("col2"));

        String expResult = "SELECT col1, col2 FROM foo";

        assertEquals(expResult, builder.createQuery(table, columns));
    }

    @Test
    public void testCreateQueryIsCaseSensitive() {
        String table = "Foo";
        List<Column> columns = new ArrayList<Column>();
        columns.add(new Column("Col1"));
        columns.add(new Column("col2"));

        String expResult = "SELECT Col1, col2 FROM Foo";

        assertEquals(expResult, builder.createQuery(table, columns));
    }

    @Test
    public void testCreateQueryReturnsAllColumnsIfNoOneSpecified() {
        String table = "foo";
        List<Column> columns = new ArrayList<Column>();

        String expResult = "SELECT * FROM foo";

        assertEquals(expResult, builder.createQuery(table, columns));
    }

    @Test(expected=IllegalArgumentException.class)
    public void testCreateQueryThrowsAnExceptionIfInvalidTable() {
        String table = "";
        List<Column> columns = new ArrayList<Column>();
        columns.add(new Column("Col1"));

        builder.createQuery(table, columns);
    }

    @Test
    public void testCreateTableQuery() {
        String table = "a_new_table";
        List<Column> columns = new ArrayList<Column>();
        columns.add(new Column("id", "INTEGER", true));
        columns.add(new Column("title", "VARCHAR", false));
        columns.add(new Column("label", "VARCHAR", false, true));

        String expResult = "CREATE TABLE a_new_table (id INTEGER PRIMARY KEY, title VARCHAR, label VARCHAR UNIQUE)";

        assertEquals(expResult, builder.createTableQuery(table, columns));
    }

    @Test(expected=IllegalArgumentException.class)
    public void testCreateTableQueryThrowsAnExceptionIfInvalidTable() {
        String table = "";
        List<Column> columns = new ArrayList<Column>();
        columns.add(new Column("Col1"));

        builder.createTableQuery(table, columns);
    }

    @Test(expected=IllegalArgumentException.class)
    public void testCreateTableQueryThrowsAnExceptionIfNoColumnGiven() {
        String table = "hello";

        builder.createTableQuery(table, new ArrayList<Column>());
    }
}