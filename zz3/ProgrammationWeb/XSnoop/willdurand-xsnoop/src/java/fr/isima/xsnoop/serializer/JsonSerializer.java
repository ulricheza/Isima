package fr.isima.xsnoop.serializer;

import fr.isima.xsnoop.model.Column;
import java.util.List;
import java.util.Map;
import org.apache.commons.lang3.StringUtils;

/**
 * @author William Durand <william.durand1@gmail.com>
 */
public class JsonSerializer {

    public String serializeList(List<String> list) {
        StringBuilder sb = new StringBuilder("[");

        for (String s : list) {
            if (s == null) {
                sb.append("null");
            } else {
                sb.append("\"");
                sb.append(StringUtils.replace(s, "\"", "\\\""));
                sb.append("\"");
            }

            sb.append(",");
        }

        sb.delete(sb.length() - 1, sb.length());
        sb.append("]");

        return sb.toString();
    }

    /**
     * Serialize a result set.
     */
    public String serializeResultSet(List<Map<Column, String>> resultSet, List<Column> columns) {
        StringBuilder sb = new StringBuilder("[");

        for (Map<Column, String> row : resultSet) {
            sb.append("{");

            for (Column col : columns) {
                sb.append("\"");
                sb.append(col.getName());
                sb.append("\": ");

                if (row.get(col) == null) {
                    sb.append("null");
                } else {
                    sb.append("\"");
                    sb.append(row.get(col));
                    sb.append("\"");
                }

                sb.append(",");
            }

            sb.delete(sb.length() - 1, sb.length());
            sb.append("},");
        }

        if (!resultSet.isEmpty()) {
            sb.delete(sb.length() - 1, sb.length());
        }

        sb.append("]");

        return sb.toString();
    }
}
