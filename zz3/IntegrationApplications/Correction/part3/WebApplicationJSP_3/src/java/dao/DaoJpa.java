/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package dao;

import java.text.SimpleDateFormat;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.EntityTransaction;
import javax.persistence.Persistence;
import jpa.Clients;
import jpa.Creneaux;
import jpa.Medecins;
import jpa.Rv;

/**
 *
 * @author lacomme
 */
public class DaoJpa {
 private EntityManager em;

    private EntityManagerFactory emf;

    private EntityTransaction tx ;

    public void init()
    {
        emf = Persistence.createEntityManagerFactory("WebApplicationJSP_3PU");

        em = emf.createEntityManager();

        tx = em.getTransaction();

        tx.begin();
    }

    public void close()
    {

        em.close();

        emf.close();
    }

    // liste des clients
    public List<Clients> getAllClients() {
        try {
            return em.createQuery("select c from Clients c").getResultList();
        } catch (Exception e) {
         e.printStackTrace();
         return null;
        }
    }

    // liste des mÃ©decins
    public List<Medecins> getAllMedecins() {
        try {
            return em.createQuery("select m from Medecins m").getResultList();
        } catch (Exception e) {
         e.printStackTrace();
         return null;
        }



    }

    // liste des crÃ©neaux horaires d'un mÃ©decin donnÃ©
    // medecin : le mÃ©decin
    public List<Creneaux> getAllCreneaux(Medecins medecin) {
        try {
            return em.createQuery("select c from Creneaux c join c.medecin m where m.id=:idMedecin").setParameter("idMedecin", medecin.getId()).getResultList();
        } catch (Exception e) {
         e.printStackTrace();
         return null;
        }
    }

    // liste des Rv d'un mÃ©decin donnÃ©, un jour donnÃ©
    // medecin : le mÃ©decin
    // jour : le jour
    public List<Rv> getRvMedecinJour(Medecins medecin, String jour) {
        try {
            return em.createQuery("select rv from Rv rv join rv.creneau c join c.medecin m where m.id=:idMedecin and rv.jour=:jour").setParameter("idMedecin", medecin.getId()).setParameter("jour", new SimpleDateFormat("yyyy:MM:dd").parse(jour)).getResultList();
        }catch (Exception e) {
         e.printStackTrace();
         return null;
        }
    }

    // ajout d'un Rv
    // jour : jour du Rv
    // creneau : crÃ©neau horaire du Rv
    // client : client pour lequel est pris le Rv
    public Rv ajouterRv(String jour, Creneaux creneau, Clients client) {
        try {
            Rv rv = new Rv(new SimpleDateFormat("yyyy:MM:dd").parse(jour), client, creneau);
            em.persist(rv);
            return rv;
        } catch (Exception e) {
         e.printStackTrace();
         return null;
        }
    }

    // suppression d'un Rv
    // rv : le Rv supprimÃ©
    public void supprimerRv(Rv rv) {
        try {
            em.remove(em.merge(rv));
        }catch (Exception e) {
         e.printStackTrace();

        }
    }

    // rÃ©cupÃ©rer un client donnÃ©
    public Clients getClientById(Long id) {
        try {
            return (Clients) em.find(Clients.class, id);
        } catch (Exception e) {
         e.printStackTrace();
         return null;
        }
    }

    // rÃ©cupÃ©rer un mÃ©decin donnÃ©
    public Medecins getMedecinById(Long id) {
        try {
            return (Medecins) em.find(Medecins.class, id);
        } catch (Exception e) {
         e.printStackTrace();
         return null;
        }
    }

    // rÃ©cupÃ©rer un Rv donnÃ©
    public Rv getRvById(Long id) {
        try {
            return (Rv) em.find(Rv.class, id);
        } catch (Exception e) {
         e.printStackTrace();
         return null;
        }
    }

    // rÃ©cupÃ©rer un crÃ©neau donnÃ©
    public Creneaux getCreneauById(Long id) {
        try {
            return (Creneaux) em.find(Creneaux.class, id);
        } catch (Exception e) {
         e.printStackTrace();
         return null;
        }
    }
}
