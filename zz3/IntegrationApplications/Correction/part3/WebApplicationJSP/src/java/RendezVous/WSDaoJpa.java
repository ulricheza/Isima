/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package RendezVous;

import javax.ejb.EJB;
import javax.jws.*;
import jpa.*;
import dao.*;
import dao.IdaoLocal;
import java.util.*;

@WebService()
public class WSDaoJpa implements Idao {
    @EJB
    private IdaoLocal dao;

   // web service numero 1
  // liste des clients
  @WebMethod
  public List<Clients> getAllClients() {
     return dao.getAllClients();
  }

  // web service numero 2
  // liste des clients
  @WebMethod
  public List<Medecins> getAllMedecins() {
    return dao.getAllMedecins();
 }

 // liste des créneaux horaires d'un médecin donné
 // medecin : le médecin
 @WebMethod
 public List<Creneaux> getAllCreneaux(Medecins medecin) {
   return dao.getAllCreneaux(medecin);
 }

 // liste des Rv d'un médecin donné, un jour donné
 // medecin : le médecin,  jour : le jour
 @WebMethod
 public List<Rv> getRvMedecinJour(Medecins medecin, String jour) {
    return dao.getRvMedecinJour(medecin, jour);
 }

 // ajout d'un Rv,  jour : jour du Rv
 // creneau : créneau horaire du Rv, client : client pour lequel est pris le Rv
 @WebMethod
 public Rv ajouterRv(String jour, Creneaux creneau, Clients client) {
    return dao.ajouterRv(jour, creneau, client);
}

// suppression d'un Rv, rv : le Rv supprimé
@WebMethod
public void supprimerRv(Rv rv) {
 dao.supprimerRv(rv);
}

// récupérer un client donné
@WebMethod
public Clients getClientById(Long id) {
 return dao.getClientById(id);
}

// récupérer un médecin donné
@WebMethod
 public Medecins getMedecinById(Long id) {
   return dao.getMedecinById(id);
}

// récupérer un Rv donné
@WebMethod
public Rv getRvById(Long id) {
 return dao.getRvById(id);
}

// récupérer un créneau donné
@WebMethod
public Creneaux getCreneauById(Long id) {
 return dao.getCreneauById(id);
}
    }
