/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package bean;

import java.util.ArrayList;
import java.util.List;
import rendezvous.DaoJpaService;
import rendezvous.Clients;

public class IndexClient {



    private List<Clients> clients;

    public void setClients(List<Clients> clients) {
        this.clients = clients;
    }

    public List<Clients> getClients()
    {
       DaoJpaService  ws = new DaoJpaService ();
       System.out.println("--- affichage liste des clients ---");
       List<Clients> myArr = new ArrayList<Clients>();
       myArr = ws.getDaoJpaPort().getAllClients();
       return myArr;
    }
}
