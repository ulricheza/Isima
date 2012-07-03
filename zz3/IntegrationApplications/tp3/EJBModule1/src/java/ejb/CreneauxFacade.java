/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ejb;

import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import jpa.Creneaux;

/**
 *
 * @author JC
 */
@Stateless
public class CreneauxFacade extends AbstractFacade<Creneaux> implements CreneauxFacadeLocal {
    @PersistenceContext(unitName = "EJBModule1PU")
    private EntityManager em;

    protected EntityManager getEntityManager() {
        return em;
    }

    public CreneauxFacade() {
        super(Creneaux.class);
    }
    
}
