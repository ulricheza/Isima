/*
 * -------------------------------------------------------------------------------
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *-------------------------------------------------------------------------------"
 */
package databasemanagertest;

import databasemodeling.Attribut;
import databasemodeling.Table;
import databasemodeling.Database;
import databasemanager.OBDCAccessConnector;
import databasemodeling.Contrainte;
import databasemodeling.Operator;
import databasemodeling.requete.RequeteInterrogation;
import databasemodeling.Resultats;
import java.util.ArrayList;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 * Classe de test unitaire pour le connecteur OBDC
 * @author Maxime ESCOURBIAC - Jean-Christophe SEPTIER
 */
public class OBDCConnectorTest {

    /**
     * Constructeur du test unitaire
     */
    public OBDCConnectorTest() {
    }

    /**
     * Test de la methode de connection
     */
    @Test
    public void connecTest() {
        OBDCAccessConnector link1 = new OBDCAccessConnector();
        OBDCAccessConnector link2 = new OBDCAccessConnector();

        assertEquals(link1.connect("Try","OBDC", "Airline", "", ""), true);
        assertEquals(link1.getDatabase().getName(), "Try");
        link1.disconnect();

        assertEquals(link2.connect("Try","OBDC", "FAPAirline", "", ""), false);
        link2.disconnect();
    }
    
    /**
     * Test de la methode d'inspection du squelette
     */
    @Test
    public void inspectDatabaseTest() {
        Database base;

        OBDCAccessConnector link = new OBDCAccessConnector();
        link.connect("Try","OBDC", "Airline", "", "");
        link.inspectDatabase();
        base = link.getDatabase();

        assertEquals(base.getTables().size(), 7);

        Table tab0 = base.getTables().get(0);
        Table tab1 = base.getTables().get(1);
        Table tab2 = base.getTables().get(2);
        Table tab3 = base.getTables().get(3);
        Table tab4 = base.getTables().get(4);
        Table tab5 = base.getTables().get(5);
        Table tab6 = base.getTables().get(6);

        assertEquals(tab0.getName(), "~TMPCLP2661");
        assertEquals(tab1.getName(), "~TMPCLP314571");
        assertEquals(tab2.getName(), "APPAREL");
        assertEquals(tab3.getName(), "ASSIGNMENT");
        assertEquals(tab4.getName(), "FLIGHT");
        assertEquals(tab5.getName(), "PILOT");
        assertEquals(tab6.getName(), "PLANE");

        assertEquals(tab2.getAttributs().size(), 3);
        Attribut attr0 = tab2.getAttributs().get(0);
        Attribut attr1 = tab2.getAttributs().get(1);
        Attribut attr2 = tab2.getAttributs().get(2);

        assertEquals(attr0.getName(), "Code");
        assertEquals(attr0.getType(), "VARCHAR");
        assertEquals(attr1.getName(), "Capacity");
        assertEquals(attr1.getType(), "DOUBLE");
        assertEquals(attr2.getName(), "TradeName");
        assertEquals(attr2.getType(), "VARCHAR");
    }
    
    /**
     * Test de l'execution des requetes
     */
    @Test
    public void requestTest()
    {
        OBDCAccessConnector link = new OBDCAccessConnector();
        RequeteInterrogation req = new RequeteInterrogation();
        Attribut attr = new Attribut("Code", "VARCHAR");
        Attribut attrWhere = new Attribut("Capacity", "DOUBLE");
        Contrainte contr = new Contrainte();
        Resultats result;
        ArrayList<Attribut> listAttr = new ArrayList<Attribut>();
        ArrayList<Contrainte> listCont = new ArrayList<Contrainte>();
        
        Table table = new Table("APPAREL");
        listAttr.add(attr);
        contr.setAttribut(attrWhere);
        contr.setOperateur(Operator.SUPERIEUREGAL);
        contr.setValeur("10");
        listCont.add(contr);
        
        req.setAttributs(listAttr);
        req.setContraintes(listCont);
        req.setTable(table);
        
        link.connect("Try","OBDC", "Airline", "", "");
        result = link.request(req);
        
        assertEquals(5, result.nbResult());
        
        ArrayList<String> row0 = result.getColumnName();
        ArrayList<String> row1 = result.getRow(1);
        ArrayList<String> row2 = result.getRow(2);
        ArrayList<String> row3 = result.getRow(3);
        ArrayList<String> row4 = result.getRow(4);
        ArrayList<String> row5 = result.getRow(5);

        assertEquals(1, row0.size());
        assertEquals(1, row1.size());
        assertEquals(1, row2.size());
        assertEquals(1, row3.size());
        assertEquals(1, row4.size());
        assertEquals(1, row5.size());
        assertEquals("CODE", row0.get(0));
        assertEquals("74E", row1.get(0));
        assertEquals("AB3", row2.get(0));
        assertEquals("741", row3.get(0));
        assertEquals("SSC", row4.get(0));
        assertEquals("734", row5.get(0));
    }
}
