/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package Dao;

import javax.ejb.Local;

/**
 *
 * @author JC
 */
@Local
public interface DaoLocal {

    public java.util.List<jpa.Clients> getAllClients();

    public java.util.List<jpa.Medecins> getAllMedecins();

    public java.util.List<jpa.Rv> getAllRv();

    public java.util.List<jpa.Creneaux> getAllCreneaux();

    public java.util.List<jpa.Clients> getClientById(long id);

    public java.util.List<jpa.Medecins> getMedecinById(int id);

    public java.util.List<jpa.Creneaux> getCreneauById(long id);

    public java.util.List<jpa.Rv> getRvById(int id);

    public java.util.List<jpa.Rv> getRvByIdClient(int id);

    public java.util.List<jpa.Rv> getRvByIdMedecin(long id);

    public java.util.List<jpa.Medecins> getMedecinsByClient(long id);
}
