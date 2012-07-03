/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package Server;

import ContractProject.ClientContract;
import ContractProject.StockOptionContract;
import Modele.StockOption;
import java.net.MalformedURLException;
import java.rmi.AlreadyBoundException;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;


/**
 *  Squelette d'un stock option
 *  @author Jean-Christophe SEPTIER Maxime ESCOURBIAC
 */
public class StockOptionSkeleton extends UnicastRemoteObject implements StockOptionContract {

	private StockOption stockOption; // Stock option correspondant au squelette

        /**
         * Constructeur du squelette de stock option
         * @param name nom du stock option
         * @param company nom de la companie
         * @param qt valeur de la quote
         * @throws RemoteException 
         */
	public StockOptionSkeleton(String name, String company, int qt) throws RemoteException 
        {	
            super();
            // Créer le stock option
	    stockOption = new StockOption(name, company, qt);
            
            if (stockOption != null) {
			try {
                                // Bind le stock option
				Naming.bind(name, this);
			} catch (MalformedURLException e) {
				Logger.getLogger(StockOptionSkeleton.class.getName()).log(Level.SEVERE,"URL mal formée", e);
			} catch (AlreadyBoundException e) {
				Logger.getLogger(StockOptionSkeleton.class.getName()).log(Level.SEVERE, "Aready Bound", e);
			}
		}
	}

        /**
         * Retourne le nom du stock option
         * @return le nom
         */
	@Override
	public String getName() throws RemoteException {
		return stockOption.getTitle();
	}

        /**
         * Retourne le nom de la companie du stock option
         * @return le nom de la companie
         */
	@Override
	public String getCompany() throws RemoteException {
		return stockOption.getCompany();
	}

        /**
         * Retourne la quote du stock option
         * @return la quote actuelle
         */
	@Override
	public int getCurrentQuote() throws RemoteException {
		return stockOption.getQuote();
	}

        /**
         * Retourne la liste des followers
         * @return la liste des followers
         */
	@Override
	public List<ClientContract> getFollowers() {
		return stockOption.getFollowers();
	}

        /**
         * Ajoute un follower au stock option
         * @param follower contrat du follower
         */
	@Override
	public void addFollower(ClientContract follower) throws RemoteException {
		stockOption.addFollower(follower);
	}

        /**
         * Supprime un follower
         * @param follower contrat du follower à supprimer
         * @return TRUE s'il est supprimé, FALSE sinon
         */
	@Override
	public boolean removeFollower(ClientContract follower) throws RemoteException {
		return stockOption.removeFollower(follower);
	}

        /**
         * Supprime tout les followers
         */
	@Override
	synchronized public void clearFollowers() throws RemoteException 
        {   
            stockOption.clearFollowers();
	}

        /**
         * Change la quote du stock option
         * @param currentQuote
         */
         @Override
        public void setCurrentQuote(int currentQuote) throws RemoteException {
           stockOption.setQuote(currentQuote);
        }

}