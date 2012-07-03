/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package Dao;

import ejb.ClientsFacade;
import java.util.List;
import javax.ejb.Local;
import jpa.Clients;

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

    public java.util.List<jpa.Clients> getClientById(int id);

    public java.util.List<jpa.Clients> getMedecinById(int id);

    public java.util.List<jpa.Clients> getCreneauById(int id);

    public java.util.List<jpa.Clients> getRvById(int id);

}
