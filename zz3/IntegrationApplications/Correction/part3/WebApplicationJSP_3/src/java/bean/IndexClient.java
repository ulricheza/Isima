package bean;


import java.util.ArrayList;
import java.util.List;
import dao.DaoJpa;
import jpa.Clients;

public class IndexClient {

    private DaoJpa dao;


    private List<Clients> clients;

    public void setClients(List<Clients> clients) {
        this.clients = clients;
    }


    public List<Clients> getClients()
    {


      dao  = new DaoJpa ();

      dao.init(); //On initialise la couche de persistence

       System.out.println("--- affichage liste des clients ---");
       List<Clients> myArr = new ArrayList<Clients>();
       myArr = dao.getAllClients();

       dao.close();
       return myArr;
    }
}

