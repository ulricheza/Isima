/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package beanJsp;

import java.util.List;

/**
 *
 * @author JC
 */
import java.util.ArrayList;
import rendezvous_service2.Clients; 
import rendezvous_service2.WSDaoJpa_Service;
import rendezvous_service2.Medecins;
import rendezvous_service2.Rv;

public class IndexClient {
    
    private List<Clients> clients;
    
    public void setClients(List<Clients> clients)
    {
        this.clients = clients;
    }
    
    public int getTest()
    {
        return 5;
    }
    
    public List<Clients> getClients()
    {
        rendezvous_service2.WSDaoJpa_Service ws = new WSDaoJpa_Service();
        
        List<Clients> myArr = new ArrayList<Clients>();
        myArr = ws.getWSDaoJpaPort().getAllClients();
 
        return myArr;        
    }
    
    public List<Medecins> getMedecins()
    {
        rendezvous_service2.WSDaoJpa_Service ws = new WSDaoJpa_Service();
        
        List<Medecins> myArr = new ArrayList<Medecins>();
        myArr = ws.getWSDaoJpaPort().getAllMedecins();
 
        return myArr;        
    }

    public List<rendezvous_service2.Medecins> getMedecinByIdClient(long id)
    {
        rendezvous_service2.WSDaoJpa_Service ws = new rendezvous_service2.WSDaoJpa_Service();
        
        List<rendezvous_service2.Medecins> myArr = new ArrayList<rendezvous_service2.Medecins>();
        myArr = ws.getWSDaoJpaPort().getMedecinsByClient(id);
 
        return myArr;        
    }
    
    
}