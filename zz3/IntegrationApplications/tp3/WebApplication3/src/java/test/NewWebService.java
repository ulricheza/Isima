/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package test;

import Dao.DaoLocal;
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
@WebService(serviceName = "NewWebService")
public class NewWebService {
    @EJB
    private DaoLocal ejbRef;// Add business logic below. (Right-click in editor and choose
    // "Insert Code > Add Web Service Operation")

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

    @WebMethod(operationName = "getMedecinById")
    public List<Clients> getMedecinById(@WebParam(name = "id") int id) {
        return ejbRef.getMedecinById(id);
    }

    @WebMethod(operationName = "getCreneauById")
    public List<Clients> getCreneauById(@WebParam(name = "id") int id) {
        return ejbRef.getCreneauById(id);
    }

    @WebMethod(operationName = "getRvById")
    public List<Clients> getRvById(@WebParam(name = "id") int id) {
        return ejbRef.getRvById(id);
    }
    
}
