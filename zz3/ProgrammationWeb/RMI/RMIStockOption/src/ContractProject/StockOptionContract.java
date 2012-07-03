/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ContractProject;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.List;

/**
 * Interface du contrat du stock option
 * @author Jean-Christophe SEPTIER Maxime ESCOURBIAC
 */
public interface StockOptionContract extends Remote{
        /**
         * Retourne le nom du stock option
         * @return le nom
         */
	public String getName()throws RemoteException;
       /**
         * Retourne le nom de la companie du stock option
         * @return le nom de la companie
         */
	public String getCompany()throws RemoteException;
        /**
         * Retourne la quote du stock option
         * @return la quote actuelle
         */
	public int getCurrentQuote()throws RemoteException;
         /**
         * Change la quote du stock option
         * @param currentQuote
         */
	public void setCurrentQuote(int currentQuote)throws RemoteException;
        /**
         * Retourne la liste des followers
         * @return la liste des followers
         */
	public List<ClientContract> getFollowers()throws RemoteException;
        /**
         * Ajoute un follower au stock option
         * @param follower contrat du follower
         */
	public void addFollower(ClientContract follower) throws RemoteException;
        /**
         * Supprime un follower
         * @param follower contrat du follower à supprimer
         * @return TRUE s'il est supprimé, FALSE sinon
         */
	public boolean removeFollower(ClientContract follower) throws RemoteException;
        /**
         * Supprime tout les followers
         */
	public void clearFollowers()throws RemoteException;
}
