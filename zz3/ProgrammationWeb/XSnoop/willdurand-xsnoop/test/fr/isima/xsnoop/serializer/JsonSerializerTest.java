package fr.isima.xsnoop.serializer;

import fr.isima.xsnoop.model.Column;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import static org.junit.Assert.assertEquals;
import org.junit.Before;
import org.junit.Test;

/**
 * @author William Durand <william.durand1@gmail.com>
 */
public class JsonSerializerTest {

    private JsonSerializer serializer;

    @Before
    public void setUp() {
        serializer = new JsonSerializer();
    }

    @Test
    public void testSerializeList() {
        String expected = "[\"foo\",\"bar\",\"baz\"]";
        List<String> list = new ArrayList<String>();
        list.add("foo");
        list.add("bar");
        list.add("baz");

        assertEquals(expected, serializer.serializeList(list));
    }

    @Test
    public void testSerializeListWithNullValue() {
        String expected = "[\"foo\",\"bar\",null]";
        List<String> list = new ArrayList<String>();
        list.add("foo");
        list.add("bar");
        list.add(null);

        assertEquals(expected, serializer.serializeList(list));
    }

    @Test
    public void testSerializeListWithEmptyValue() {
        String expected = "[\"foo\",\"bar\",\"\"]";
        List<String> list = new ArrayList<String>();
        list.add("foo");
        list.add("bar");
        list.add("");

        assertEquals(expected, serializer.serializeList(list));
    }

    @Test
    public void testSerializeListEscapesDoubleQuotes() {
        String expected = "[\"\\\"fooooo\\\"\",\"bar\"]";
        List<String> list = new ArrayList<String>();
        list.add("\"fooooo\"");
        list.add("bar");

        assertEquals(expected, serializer.serializeList(list));
    }

    @Test
    public void testSerializeResultSet() {
        final Column col1 = new Column("col1", "varchar", false);
        final Column col2 = new Column("col2", "varchar", false);

        List<Column> columns = new ArrayList<Column>() {{
            add(col1);
            add(col2);
        }};
        List<Map<Column, String>> resultSet = new ArrayList<Map<Column, String>>();
        resultSet.add(new HashMap<Column, String>() {{
            put(col1, "val1");
            put(col2, "val2");
        }});

        String expected  = "[{\"col1\": \"val1\",\"col2\": \"val2\"}]";

        assertEquals(expected, serializer.serializeResultSet(resultSet, columns));
    }

    @Test
    public void testSerializeResultSetWithNoResult() {
        final Column col1 = new Column("col1", "varchar", false);
        final Column col2 = new Column("col2", "varchar", false);

        List<Column> columns = new ArrayList<Column>() {{
            add(col1);
            add(col2);
        }};
        List<Map<Column, String>> resultSet = new ArrayList<Map<Column, String>>();

        String expected  = "[]";

        assertEquals(expected, serializer.serializeResultSet(resultSet, columns));
    }

    @Test
    public void testSerializeResultSetWithNullValue() {
        final Column col1 = new Column("col1", "varchar", false);
        final Column col2 = new Column("col2", "varchar", false);

        List<Column> columns = new ArrayList<Column>() {{
            add(col1);
            add(col2);
        }};
        List<Map<Column, String>> resultSet = new ArrayList<Map<Column, String>>();
        resultSet.add(new HashMap<Column, String>() {{
            put(col1, "val1");
            put(col2, null);
        }});

        String expected  = "[{\"col1\": \"val1\",\"col2\": null}]";

        assertEquals(expected, serializer.serializeResultSet(resultSet, columns));
    }

    @Test
    public void testSerializeResultSetWithEmptyValue() {
        final Column col1 = new Column("col1", "varchar", false);
        final Column col2 = new Column("col2", "varchar", false);

        List<Column> columns = new ArrayList<Column>() {{
            add(col1);
            add(col2);
        }};
        List<Map<Column, String>> resultSet = new ArrayList<Map<Column, String>>();
        resultSet.add(new HashMap<Column, String>() {{
            put(col1, "val1");
            put(col2, "");
        }});

        String expected  = "[{\"col1\": \"val1\",\"col2\": \"\"}]";

        assertEquals(expected, serializer.serializeResultSet(resultSet, columns));
    }

    @Test
    public void testSerializeResultSetWithMultipleRows() {
        final Column col1 = new Column("col1", "varchar", false);
        final Column col2 = new Column("col2", "varchar", false);

        List<Column> columns = new ArrayList<Column>() {{
            add(col1);
            add(col2);
        }};
        List<Map<Column, String>> resultSet = new ArrayList<Map<Column, String>>();
        resultSet.add(new HashMap<Column, String>() {{
            put(col1, "val1");
            put(col2, "");
        }});
        resultSet.add(new HashMap<Column, String>() {{
            put(col1, "foo");
            put(col2, "bar");
        }});

        String expected  = "[{\"col1\": \"val1\",\"col2\": \"\"},{\"col1\": \"foo\",\"col2\": \"bar\"}]";

        assertEquals(expected, serializer.serializeResultSet(resultSet, columns));
    }
}
