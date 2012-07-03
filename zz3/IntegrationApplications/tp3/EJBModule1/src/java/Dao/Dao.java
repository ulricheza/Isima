/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package Dao;

import ejb.ClientsFacade;
import java.util.List;
import javax.ejb.Stateless;
import javax.ejb.TransactionAttribute;
import javax.ejb.TransactionAttributeType;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import jpa.Clients;
import jpa.Creneaux;
import jpa.Medecins;
import jpa.Rv;

/**
 *
 * @author JC
 */
@Stateless(mappedName="Interface")
@TransactionAttribute(TransactionAttributeType.REQUIRED)
public class Dao implements DaoLocal {
    @PersistenceContext(unitName ="EJBModule1PU")
    private EntityManager em;
    
        public List<Clients> getAllClients()
    {
        return em.createNamedQuery("Clients.findAll").getResultList();

    }
        
        public List<Medecins> getAllMedecins()
        {
            return em.createNamedQuery("Medecins.findAll").getResultList();
        }
        
        public List<Rv> getAllRv()
        {
            return em.createNamedQuery("Rv.findAll").getResultList();
        }
        
        public List<Creneaux> getAllCreneaux()
        {
            return em.createNamedQuery("Creneaux.findAll").getResultList();
        }
        
        public List<Clients> getClientById(int id)
        {
            return em.createQuery("SELECT c FROM Clients c WHERE c.id =" + id).getResultList();
        }
        
        public List<Clients> getRvById(int id)
        {
            return em.createQuery("SELECT c FROM Rv c WHERE c.id =" + id).getResultList();
        }
        
        public List<Clients> getCreneauById(int id)
        {
            return em.createQuery("SELECT c FROM Creneaux c WHERE c.id =" + id).getResultList();
        }
        
        public List<Clients> getMedecinById(int id)
        {
            return em.createQuery("SELECT c FROM Medecins c WHERE c.id =" + id).getResultList();
        }
    
    
}
