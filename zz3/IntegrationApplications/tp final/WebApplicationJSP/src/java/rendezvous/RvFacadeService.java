/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package rendezvous;

import ejb.RvFacadeLocal;
import java.util.Date;
import java.util.List;
import javax.ejb.EJB;
import javax.jws.Oneway;
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
@WebService(serviceName = "RvFacadeService")
public class RvFacadeService {
    @EJB
    private RvFacadeLocal ejbRef;// Add business logic below. (Right-click in editor and choose
    // "Insert Code > Add Web Service Operation")

    @WebMethod(operationName = "create")
    @Oneway
    public void create(@WebParam(name = "rv") Rv rv) {
        ejbRef.create(rv);
    }
    
    // Insert un rendez vous avec l'id du client et l'id du créneau
   @WebMethod(operationName = "InsertRv")
    public void InsertRv(@WebParam(name = "idClient") long idClient ,
    @WebParam(name = "idCreneaux") long idCreneaux) {
         Date date = new Date();
        ejbRef.createWithParam(idClient, idCreneaux, date);
    }

   // Edit un Rv
    @WebMethod(operationName = "edit")
    @Oneway
    public void edit(@WebParam(name = "rv") Rv rv) {
        ejbRef.edit(rv);
    }

    @WebMethod(operationName = "remove")
    @Oneway
    public void remove(@WebParam(name = "rv") Rv rv) {
        ejbRef.remove(rv);
    }
    
    @WebMethod(operationName = "removeById")
    @Oneway
    public void removeById(@WebParam(name = "rv") long id) {
        ejbRef.removeById(id);
    }

    @WebMethod(operationName = "findAll")
    public List<Rv> findAll() {
        return ejbRef.findAll();
    }

    @WebMethod(operationName = "count")
    public int count() {
        return ejbRef.count();
    }
    
}
