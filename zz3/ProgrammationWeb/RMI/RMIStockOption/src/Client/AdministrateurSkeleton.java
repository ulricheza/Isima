/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package Client;

import ContractProject.AdministrateurContract;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

/**
 * Squelette de l'administrateur
 * @author Jean-Christophe SEPTIER Maxime ESCOURBIAC
 */
public class AdministrateurSkeleton extends UnicastRemoteObject implements AdministrateurContract{


    private AdministrateurControlleur controlleur; // Controleur de l'administrateur
    
    /**
     * Constructeur du squelette
     * @param control controlleur
     */
    public AdministrateurSkeleton(AdministrateurControlleur control) throws RemoteException
    {
        this.controlleur = control;
    }
       
    /**
     * Permet de mettre à jour la vue
     */
    @Override
    public void miseAJour() throws RemoteException {
        controlleur.majListStockOption();
    }
    
}
