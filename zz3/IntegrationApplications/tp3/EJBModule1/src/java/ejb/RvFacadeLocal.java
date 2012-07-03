/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ejb;

import java.util.List;
import javax.ejb.Local;
import jpa.Rv;

/**
 *
 * @author JC
 */
@Local
public interface RvFacadeLocal {

    void create(Rv rv);

    void edit(Rv rv);

    void remove(Rv rv);

    Rv find(Object id);

    List<Rv> findAll();

    List<Rv> findRange(int[] range);

    int count();
    
}
