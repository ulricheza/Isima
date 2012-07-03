/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package ContractProject;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.Map;

/**
 *
 * @author jcseptier
 */
public interface ClientContract extends Remote 
{
        /**
        * Méthode qui permet d'envoyer un message à afficher dans le textArea  
        * @param mess message à afficher
        */
	public void warn(String mess) throws RemoteException;

	void ajouterStockOption(StockOptionContract stock) throws RemoteException;

	void supprimerStockOption(String name) throws RemoteException;

	public void setConnected(boolean connected) throws RemoteException;
}
