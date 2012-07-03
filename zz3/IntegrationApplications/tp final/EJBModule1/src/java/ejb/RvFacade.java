/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ejb;


import java.util.Date;
import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import jpa.Clients;
import jpa.Creneaux;
import jpa.Rv;

/**
 *
 * @author JC
 */

@Stateless
public class RvFacade extends AbstractFacade<Rv> implements RvFacadeLocal {
    @PersistenceContext(unitName = "EJBModule1PU")
    private EntityManager em;

    protected EntityManager getEntityManager() {
        return em;
    }

    public RvFacade() {
        super(Rv.class);
    }
    
    public void createWithParam(long idClient, long idCreneaux, Date jour)
    {   
        Clients cl = (Clients) em.createQuery("SELECT c FROM Clients c WHERE c.id =" + idClient).getResultList().get(0);
        Creneaux c = (Creneaux) em.createQuery("SELECT c FROM Creneaux c WHERE c.id =" + idCreneaux).getResultList().get(0);
        Rv rv= new Rv(jour, cl, c);
        create(rv);
    }

    public void removeById(Long id) {
        Rv rv = (Rv) em.createQuery("SELECT r FROM Rv r WHERE r.id =" + id).getResultList().get(0);
        remove(rv);
    }
    
}
