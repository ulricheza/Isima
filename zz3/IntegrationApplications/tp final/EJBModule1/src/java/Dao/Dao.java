/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package Dao;



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
// Classe représentant notre DAO
@Stateless(mappedName = "Interface")
@TransactionAttribute(TransactionAttributeType.REQUIRED)
public class Dao implements DaoLocal {
    
    //Entity Manager
    @PersistenceContext(unitName = "EJBModule1PU")
    private EntityManager em;

    // Permet de retourner touts les clients
    public List<Clients> getAllClients() {
        return em.createNamedQuery("Clients.findAll").getResultList();
    }

    // Permet de retourner touts les médecins
    public List<Medecins> getAllMedecins() {
        return em.createNamedQuery("Medecins.findAll").getResultList();
    }

    // Permet de retourner touts les rendez-vous
    public List<Rv> getAllRv() {
        return em.createNamedQuery("Rv.findAll").getResultList();
    }

    // Permet de retourner touts les créneaux
    public List<Creneaux> getAllCreneaux() {
        return em.createNamedQuery("Creneaux.findAll").getResultList();
    }

    // Permet de retourner un client grâce à son id
    public List<Clients> getClientById(long id) {
        return em.createQuery("SELECT c FROM Clients c WHERE c.id =" + id).getResultList();
    }

    // Permet de retourner un Rv selon son id
    public List<Rv> getRvById(int id) {
        return em.createQuery("SELECT c FROM Rv c WHERE c.id =" + id).getResultList();
    }

    // Permet de retourner un Rv selon l'id du client
    public List<Rv> getRvByIdClient(int id) {
        return em.createQuery("SELECT c FROM Rv c WHERE c.id_client =" + id).getResultList();
    }

    // Permet de retourner un Rv selon l'id du medecin
    public List<Rv> getRvByIdMedecin(long id) {
        return em.createQuery("SELECT r FROM Medecins m "
                + "JOIN m.creneauxList c JOIN c.rvList r WHERE m.id = :idMedecin").setParameter("idMedecin", id).getResultList();
    }

    // Permet de retourner un créneau selon son id
    public List<Creneaux> getCreneauById(long id) {
        return em.createQuery("SELECT c FROM Creneaux c WHERE c.id =" + id).getResultList();
    }

    // Permet de retourner un médecin selon son id
    public List<Medecins> getMedecinById(int id) {
        return em.createQuery("SELECT c FROM Medecins c WHERE c.id =" + id).getResultList();
    }

    // Permet de retourner un médecin pour un client donnée
    public List<Medecins> getMedecinsByClient(long id) {
        return em.createQuery("SELECT DISTINCT m FROM Medecins m "
                + "JOIN m.creneauxList c JOIN c.rvList r WHERE r.idClient.id = :idClient").setParameter("idClient", id).getResultList();
    }
}
