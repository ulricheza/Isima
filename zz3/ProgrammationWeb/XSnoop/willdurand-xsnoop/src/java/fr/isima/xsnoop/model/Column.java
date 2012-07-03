package fr.isima.xsnoop.model;

import org.apache.commons.lang3.StringUtils;
import sun.swing.StringUIClientPropertyKey;

/**
 * POJO representing a Column
 *
 * @author William Durand <william.durand1@gmail.com>
 */
public class Column {

    private String name;

    private String type;

    private boolean isPrimaryKey;

    private boolean isUnique;

    public Column(String name) {
        this.name = name;

        // Set defaults
        isPrimaryKey = false;
        isUnique = false;
    }

    public Column(String name, String type, boolean isPrimaryKey) {
        this(name);
        this.type = type;
        this.isPrimaryKey = isPrimaryKey;
    }

    public Column(String name, String type, boolean isPrimaryKey, boolean isUnique) {
        this(name, type, isPrimaryKey);
        this.isUnique = isUnique;
    }

    public String getName() {
        return name;
    }

    public String getType() {
        return type;
    }

    public boolean isPrimaryKey() {
        return isPrimaryKey;
    }

    public boolean isUnique() {
        return isUnique;
    }

    public boolean isNumeric() {
        return StringUtils.startsWithIgnoreCase(type, "integer")
               || StringUtils.startsWithIgnoreCase(type, "numeric")
               || StringUtils.startsWithIgnoreCase(type, "int")
               || StringUtils.startsWithIgnoreCase(type, "bigint")
               || StringUtils.startsWithIgnoreCase(type, "float");
    }

    public boolean isText() {
        return StringUtils.startsWithIgnoreCase(type, "longtext")
               || StringUtils.startsWithIgnoreCase(type, "text");
    }

    public boolean isVarchar() {
        return StringUtils.startsWithIgnoreCase(type, "varchar")
               || StringUtils.startsWithIgnoreCase(type, "char");
    }

    public boolean isDateTime() {
        return StringUtils.startsWithIgnoreCase(type, "timestamp")
               || StringUtils.startsWithIgnoreCase(type, "date")
               || StringUtils.startsWithIgnoreCase(type, "datetime")
               || StringUtils.startsWithIgnoreCase(type, "time");
    }

    @Override
    public String toString() {
        return name;
    }
}
