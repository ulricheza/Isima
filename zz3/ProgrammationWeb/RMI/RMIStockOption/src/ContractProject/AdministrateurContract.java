/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ContractProject;

import java.rmi.Remote;
import java.rmi.RemoteException;

/**
 *
 * @author JC
 */
public interface AdministrateurContract extends Remote 
{
    public void miseAJour() throws RemoteException;
}
