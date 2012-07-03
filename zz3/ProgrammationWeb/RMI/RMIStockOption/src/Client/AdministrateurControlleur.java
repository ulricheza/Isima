/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package Client;

import ContractProject.AdministrateurContract;
import ContractProject.ExchangeContract;
import ContractProject.StockOptionContract;
import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.util.Map;
import java.util.Map.Entry;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Controlleur de l'administrateur
 * @author Jean-Christophe SEPTIER Maxime ESCOURBIAC
 */
public class AdministrateurControlleur 
{   
    private String name; // Nom de l'administrateur
    
    private AdministrateurView  administrateurView; // Vue de l'administrateur
    private ExchangeContract    exchangeContract;   // Contrat vers le serveur 
    
    private AdministrateurContract adminContract;   // Contrat de l'administrateur
    
    private Map<String,StockOptionContract> stockOptions;   // Map de stock option
    
    
    /**
     * Constructeur du controlleur
     * @param administrateur vue de l'administrateur
     */
    public AdministrateurControlleur(AdministrateurView administrateur)
    {
        try {
            
            this.administrateurView = administrateur;
            
            exchangeContract = (ExchangeContract) Naming.lookup(ExchangeContract.host 
                    + ExchangeContract.EXCHANGE_IDENTITY);

            adminContract = new AdministrateurSkeleton(this);
            
            // Connecte l'admin
            name = exchangeContract.connectAdmin(adminContract);
            
            // Mise à jour de la vue
            majListStockOption();
            
        }
        catch (NotBoundException ex) {
            Logger.getLogger(AdministrateurControlleur.class.getName()).log(Level.SEVERE, null, ex);
        } catch (MalformedURLException ex) {
            Logger.getLogger(AdministrateurControlleur.class.getName()).log(Level.SEVERE, null, ex);
        } catch (RemoteException ex) {
            Logger.getLogger(AdministrateurControlleur.class.getName()).log(Level.SEVERE, null, ex);
        }        
    }
    
    /**
     * Mise à jour de la vue
     */
    public void majListStockOption()
    {
        try 
        {
            // Récupère la liste de stock option
            stockOptions = exchangeContract.getStockOption();
            int limite = exchangeContract.getLimite();
            administrateurView.clearList();
             
            // Ajoute les stocks option
            for (Entry<String, StockOptionContract> entry : stockOptions.entrySet()) 
            {
                administrateurView.addStockOption(entry.getKey());
                administrateurView.changeLimite(limite);
            }
            
            
        } catch (RemoteException ex) {
            Logger.getLogger(AdministrateurControlleur.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    /**
     * Permet de supprimer un stock option
     * @param selectedItem nom du stock option
     */
    void supressionStockOption(String selectedItem) 
    {
        try 
        {
            // Supprime le stock option
            exchangeContract.removeStockOtion(selectedItem);
            // Met à jour la vue
            majListStockOption();
            
        } catch (RemoteException ex) {
            Logger.getLogger(AdministrateurControlleur.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    /**
     * Permet d'ajouter un stock option
     * @param name nom
     * @param companie Compagnie
     * @param qte cote
     */
    void addStockOption(String name, String companie, int qte) {
        try {
            exchangeContract.addStockOption(name, companie, qte);
            majListStockOption();
        } catch (RemoteException ex) {
            Logger.getLogger(AdministrateurControlleur.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    /**
     * Deconnexion de l'administrateur
     */
    void deconnexion()
    {
        try {
            exchangeContract.disconnectedAdmin(name);
            Naming.unbind(name);
        } catch (NotBoundException ex) {
            Logger.getLogger(AdministrateurControlleur.class.getName()).log(Level.SEVERE, null, ex);
        } catch (MalformedURLException ex) {
            Logger.getLogger(AdministrateurControlleur.class.getName()).log(Level.SEVERE, null, ex);
        } catch (RemoteException ex) {
            Logger.getLogger(AdministrateurControlleur.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    /**
     * Permet de changer la limite
     * @param q limite
     */
    void changeLimite(int q) 
    {
        try 
        {
            exchangeContract.setLimite(q);
        } catch (RemoteException ex) {
            Logger.getLogger(AdministrateurControlleur.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
