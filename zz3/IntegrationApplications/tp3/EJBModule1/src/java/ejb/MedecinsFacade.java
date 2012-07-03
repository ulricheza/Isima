/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ejb;

import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import jpa.Medecins;

/**
 *
 * @author JC
 */
@Stateless
public class MedecinsFacade extends AbstractFacade<Medecins> implements MedecinsFacadeLocal {
    @PersistenceContext(unitName = "EJBModule1PU")
    private EntityManager em;

    protected EntityManager getEntityManager() {
        return em;
    }

    public MedecinsFacade() {
        super(Medecins.class);
    }
    
}
