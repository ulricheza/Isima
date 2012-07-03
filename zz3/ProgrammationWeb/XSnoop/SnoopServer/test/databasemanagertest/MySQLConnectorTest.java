/*
 * -------------------------------------------------------------------------------
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *-------------------------------------------------------------------------------"
 */
package databasemanagertest;

import databasemodeling.Operator;
import java.util.ArrayList;
import databasemodeling.Resultats;
import databasemodeling.Contrainte;
import databasemodeling.requete.RequeteInterrogation;
import databasemodeling.Attribut;
import databasemodeling.Table;
import databasemodeling.Database;
import databasemanager.MySQLConnector;
import databasemanager.JDBCConnector;
import databasemodeling.Ligne;
import databasemodeling.requete.RequeteAjoutLigne;
import databasemodeling.requete.RequeteAjoutTable;
import databasemodeling.requete.RequeteSupprLigne;
import databasemodeling.requete.RequeteSupprTable;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 * Classe de test unitaire pour le connecteur MySQL
 * @author Maxime ESCOURBIAC - Jean-Christophe SEPTIER
 */
public class MySQLConnectorTest {

    /**
     * Constructeur du test unitaire
     */
    public MySQLConnectorTest() {
    }

    /**
     * Test de la methode de connection
     */
    @Test
    public void connectTest() {
        JDBCConnector link1 = new MySQLConnector();
        JDBCConnector link2 = new MySQLConnector();

        assertEquals(link1.connect("test", "MySQL", "127.0.0.1", "", ""), true);
        assertEquals(link1.getDatabase().getName(), "test");
        link1.disconnect();

        assertEquals(link2.connect("Try", "MySQL", "FAPAirline", "", ""), false);
        link2.disconnect();
    }

    /**
     * Test de la methode d'inspection du squelette
     */
    @Test
    public void inspectDatabaseTest() {
        Database base;

        JDBCConnector link = new MySQLConnector();
        link.connect("test", "MySQL", "127.0.0.1", "", "");
        link.inspectDatabase();
        base = link.getDatabase();

        assertEquals(base.getTables().size(), 2);
        Table tab0 = base.getTables().get(0);
        assertEquals(tab0.getName(), "dummy");


        assertEquals(tab0.getAttributs().size(), 3);
        Attribut attr0 = tab0.getAttributs().get(0);
        Attribut attr1 = tab0.getAttributs().get(1);
        Attribut attr2 = tab0.getAttributs().get(2);

        assertEquals(attr0.getName(), "first_name");
        assertEquals(attr0.getType(), "CHAR");
        assertEquals(attr1.getName(), "last_name");
        assertEquals(attr1.getType(), "CHAR");
        assertEquals(attr2.getName(), "age");
        assertEquals(attr2.getType(), "INT");
    }

    /**
     * Test des executions de requetes
     */
    @Test
    public void requestTest() {
        JDBCConnector link = new MySQLConnector();
        RequeteInterrogation req = new RequeteInterrogation();
        Attribut attr1 = new Attribut("first_name", "CHAR");
        Attribut attr2 = new Attribut("last_name", "CHAR");
        Attribut attrWhere = new Attribut("age", "INT");
        Contrainte contr = new Contrainte();
        Table table = new Table("dummy");
        Resultats result;
        ArrayList<Attribut> listAttr = new ArrayList<Attribut>();
        ArrayList<Contrainte> listCont = new ArrayList<Contrainte>();

        listAttr.add(attr1);
        listAttr.add(attr2);
        contr.setAttribut(attrWhere);
        contr.setOperateur(Operator.INFERIEUR);
        contr.setValeur("20");
        listCont.add(contr);

        req.setAttributs(listAttr);
        req.setContraintes(listCont);
        req.setTable(table);

        link.connect("test", "MySQL", "127.0.0.1", "", "");
        result = link.request(req);

        assertEquals(1, result.nbResult());

        ArrayList<String> row0 = result.getColumnName();
        ArrayList<String> row1 = result.getRow(1);

        assertEquals(2, row0.size());
        assertEquals(2, row1.size());

        assertEquals("FIRST_NAME", row0.get(0));
        assertEquals("LAST_NAME", row0.get(1));
        assertEquals("Curly", row1.get(0));
        assertEquals("Carlin", row1.get(1));
    }

    @Test
    public void addDropTableTest() {

        JDBCConnector link = new MySQLConnector();
        RequeteAjoutTable requeteAjout = new RequeteAjoutTable();
        RequeteSupprTable requeteSuppr = new RequeteSupprTable();
        Database base;
        Attribut attr1 = new Attribut("ID", "INTEGER", true);
        Attribut attr2 = new Attribut("VALUE", "CHAR");
        Table table = new Table("addTest");
        Table tableInspect;

        table.addAttribut(attr1);
        table.addAttribut(attr2);
        requeteAjout.setTable(table);
        requeteSuppr.setTable(table);

        link.connect("test", "MySQL", "127.0.0.1", "", "");
        assertEquals(true, link.addTable(requeteAjout));
        link.inspectDatabase();
        base = link.getDatabase();

        assertEquals(3, base.getTables().size());
        tableInspect = base.getTables().get(0);
        assertEquals(tableInspect.getName(), "addtest");

        assertEquals(true, link.dropTable(requeteSuppr));
        link.inspectDatabase();
        base = link.getDatabase();
        assertEquals(2, base.getTables().size());
    }

    @Test
    public void addDropRowTest() {
        
        JDBCConnector link = new MySQLConnector();
        RequeteAjoutLigne requeteAjout = new RequeteAjoutLigne();
        RequeteSupprLigne requeteSuppr = new RequeteSupprLigne();
        Ligne ligne = new Ligne();
        Table table = new Table("dummy");
        Attribut first = new Attribut("FIRST_NAME", "CHAR", "Jess");
        Attribut last = new Attribut("LAST_NAME", "CHAR", "Minou");
        Attribut age = new Attribut("AGE", "INT", "22");
        
        ligne.addAttribut(first);
        ligne.addAttribut(last);
        ligne.addAttribut(age);
        requeteAjout.setLigne(ligne);
        requeteAjout.setTable(table);
        link.connect("test", "MySQL", "127.0.0.1", "", "");
        assertEquals(true, link.addRow(requeteAjout));
        link.inspectDatabase();
        Database base = link.getDatabase();
        
        requeteSuppr.setTable(table);
        requeteSuppr.setLigne(ligne);
        assertEquals(true, link.dropRow(requeteSuppr));

    }
}
