/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package Client;

import ContractProject.StockOptionContract;
import java.io.IOException;
import java.rmi.AlreadyBoundException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import ContractProject.ClientContract;
import ContractProject.ExchangeContract;
import java.util.Map;

/**
 * Squelette du client
 * @author Jean-Christophe SEPTIER Maxime ESCOURBIAC
 */

class ClientSkeleton extends UnicastRemoteObject implements ClientContract {
	
    ClientControlleur clientControlleur;  // Controlleur du client
    
    /**
    * Constructeur du squelette du client
    * @param controlleur controlleur du client
    */
    public ClientSkeleton(ClientControlleur controlleur) throws RemoteException{
	super();
        this.clientControlleur = controlleur;
    }
       
    /**
     * Permet d'afficher un message
     * @param mess message à afficher
     */
    @Override
    public void warn(String mess) throws RemoteException {
        clientControlleur.afficherMessage(mess);
    }

    /**
     * Permet d'ajouter un stock option
     * @param stock Contract du stock option
     */
    @Override
    public void ajouterStockOption(StockOptionContract stock) throws RemoteException 
    {
        clientControlleur.addStockOption(stock);
    }

    /**
     * Supprimer le stock option
     * @param name nom du stock option
     */
    @Override
    public void supprimerStockOption(String name) throws RemoteException {
        clientControlleur.supprimerStockOption(name);
    }

    /**
     * Dit si le client est connecté ou non
     * @param connected TRUE s'il est connecté, FALSE s'il est déconnecté
     */
    @Override
    public void setConnected(boolean connected) throws RemoteException {
        clientControlleur.setConnected(connected);
    }

}