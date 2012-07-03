/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package rendezvous;

import Dao.DaoLocal;
import java.util.Date;
import java.util.List;
import javax.ejb.EJB;
import javax.jws.WebMethod;
import javax.jws.WebParam;
import javax.jws.WebService;
import jpa.Clients;
import jpa.Creneaux;
import jpa.Medecins;
import jpa.Rv;

/**
 *
 * @author JC
 */
@WebService(serviceName = "WSDaoJpa")
public class WSDaoJpa {
    @EJB
    private DaoLocal ejbRef;

    @WebMethod(operationName = "getAllClients")
    public List<Clients> getAllClients() {
        return ejbRef.getAllClients();
    }

    @WebMethod(operationName = "getAllMedecins")
    public List<Medecins> getAllMedecins() {
        return ejbRef.getAllMedecins();
    }

    @WebMethod(operationName = "getAllRv")
    public List<Rv> getAllRv() {
        return ejbRef.getAllRv();
    }

    @WebMethod(operationName = "getAllCreneaux")
    public List<Creneaux> getAllCreneaux() {
        return ejbRef.getAllCreneaux();
    }

    @WebMethod(operationName = "getClientById")
    public List<Clients> getClientById(@WebParam(name = "id") int id) {
        return ejbRef.getClientById(id);
    }
    
        @WebMethod(operationName = "getClientByIdTest")
    public Clients getClientByIdTest(@WebParam(name = "id") int id) {
        return ejbRef.getClientById(id).get(0);
    }

    @WebMethod(operationName = "getMedecinById")
    public List<Medecins> getMedecinById(@WebParam(name = "id") int id) {
        return ejbRef.getMedecinById(id);
    }

    @WebMethod(operationName = "getCreneauById")
    public List<Creneaux> getCreneauById(@WebParam(name = "id") int id) {
        return ejbRef.getCreneauById(id);
    }

    @WebMethod(operationName = "getRvById")
    public List<Rv> getRvById(@WebParam(name = "id") int id) {
        return ejbRef.getRvById(id);
    }
    
    @WebMethod(operationName = "getRvByIdClient")
    public List<Rv> getRvByIdClient(@WebParam(name = "id") int id) {
        return ejbRef.getRvByIdClient(id);
    }
    
    @WebMethod(operationName = "getRvByIdMedecin")
    public List<Rv> getRvByIdMedecin(@WebParam(name = "id") long id) {
        return ejbRef.getRvByIdMedecin(id);
    }
    
        @WebMethod(operationName = "getMedecinsByClient")
    public List<Medecins> getMedecinsByClient(@WebParam(name = "id") long id) {
        return ejbRef.getMedecinsByClient(id);
    }
   
   @WebMethod(operationName = "getDate")
    public Date getDate()
   {
         Date date = new Date();
         return date;
   }
   
         
}
