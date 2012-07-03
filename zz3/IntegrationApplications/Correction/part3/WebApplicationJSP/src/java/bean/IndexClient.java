/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package bean;

import java.util.ArrayList;
import java.util.List;
//import jpa.Clients;
import RendezVous.WSDaoJpaPort;
//import jpa.Clients;
import RendezVous_client.WSDaoJpaService;
import RendezVous_client.Clients;

public class IndexClient {


 
    private List<Clients> clients;

    public void setClients(List<Clients> clients) {
        this.clients = clients;
    }

    public List<Clients> getClients()
    {
       WSDaoJpaService  ws = new WSDaoJpaService ();
       System.out.println("--- affichage liste des clients ---");
       List<Clients> myArr = new ArrayList<Clients>();
       myArr = ws.getWSDaoJpaPort().getAllClients();
       return myArr;
    }
}

