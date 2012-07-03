/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ejb;

import java.util.Date;
import java.util.List;
import javax.ejb.Local;
import jpa.Clients;
import jpa.Creneaux;
import jpa.Rv;

/**
 *
 * @author JC
 */
@Local
public interface RvFacadeLocal {

    void create(Rv rv);
    
    void createWithParam(long idClient, long idCreneaux, Date jour);
    
    void edit(Rv rv);

    void remove(Rv rv);

    Rv find(Object id);

    List<Rv> findAll();

    List<Rv> findRange(int[] range);

    int count();
    
    void removeById(Long id);
    
}
