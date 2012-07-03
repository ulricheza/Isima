package fr.isima.xsnoop.model;

/**
 * POJO representing a Table
 *
 * @author William Durand <william.durand1@gmail.com>
 */
public class Table {

    private String name;

    public Table(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    @Override
    public String toString() {
        return name;
    }
}
