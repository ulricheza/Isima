/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package Client;

import ContractProject.ExchangeContract;
import ContractProject.StockOptionContract;
import java.net.MalformedURLException;
import java.rmi.AlreadyBoundException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.util.Map;
import java.util.Map.Entry;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Controlleur du client
 * @author Jean-Christophe SEPTIER Maxime ESCOURBIAC
 */
public class ClientControlleur {
    
    private ClientView clientView;              // Vue du client
    private ClientSkeleton exchangeClient;      // Squelette du client
    private ExchangeContract exchangeContract;  // Contract du serveur
    
    private Boolean connected;                  // Si le client est connecté
    
    private String name;                        // Nom du client
    
    Map<String, StockOptionContract> stockOptions; // Map de contract des stocksOptions 
    
    /**
     * Constructeur du controlleur
     * @param cl vue du client
     */
    public ClientControlleur(ClientView cl)
    {
        connected = false;
        
        try {
            this.clientView = cl;
            exchangeClient = new ClientSkeleton(this);
        } catch (RemoteException ex) {
            Logger.getLogger(ClientControlleur.class.getName()).log(Level.SEVERE, "Problème de connexion", ex);
        }
    }
    
    /**
     * Retourne la liste des stocks options
     * @return la liste
     */
    public Map<String, StockOptionContract> getStockOption() 
    {
        Map<String, StockOptionContract> map = null;
        
        try 
        {
            map = exchangeContract.getStockOption();
        
        } catch (RemoteException ex) 
        {
            Logger.getLogger(ClientControlleur.class.getName())
                    .log(Level.SEVERE, "Probleme pour la méhode getStockOption" , ex);
        }
        
        return map;
    }

    /**
     * Méthode appelée par le bouton de connexion.
     * Permet de se connecter au server et de récupérer la liste des stock options et l'ajoute
     * dans la liste disponible.
     * @param name Nom de connexion
     */
    public void connexion(String name) 
    {
        this.name = name;
        if ( ! connected)
        try {
            System.out.println("Client "+ name + " is running...");
            
            try {
		Naming.bind(name,exchangeClient);
            } catch(AlreadyBoundException e) {
                Logger.getLogger(ClientControlleur.class.getName()).log(Level.SEVERE, null, e);
	    }
            
            exchangeContract = (ExchangeContract) Naming.lookup(ExchangeContract.host + ExchangeContract.EXCHANGE_IDENTITY);
            if (exchangeContract.connect(name))
            {

                stockOptions = exchangeContract.getStockOption();

                for (Entry<String, StockOptionContract> entry : stockOptions.entrySet()) 
                {
                    clientView.addStockOption(entry.getKey());
                }

                connected = true;
            }
            else
            {
                clientView.afficherAlert("Nom déjà utilisé", "Attention");
            }
            
        } catch (NotBoundException ex) {
            Logger.getLogger(ClientControlleur.class.getName()).log(Level.SEVERE, null, ex);
        } catch (MalformedURLException ex) {
            Logger.getLogger(ClientControlleur.class.getName()).log(Level.SEVERE, null, ex);
        } catch (RemoteException ex) {
            Logger.getLogger(ClientControlleur.class.getName()).log(Level.SEVERE, null, ex);
        }
        
    }
    
    /**
     * Deconnexion du client
     */
    public void deconnexion()
    {
        if ( connected )
        try {
            exchangeContract.disconnect(name);
            connected = false;
        } catch (RemoteException ex) {
            Logger.getLogger(ClientControlleur.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    /**
     * Ajoute un stock option followed
     * @param ligne ligne selectionner
     * @param name nom du stock option
     */
    public void addFollowedStockOption(int ligne, String name)
    {
        
        try {
            
            clientView.addStockOptionFollowed(name, ligne);
            StockOptionContract contract = stockOptions.get(name);
            contract.addFollower(exchangeClient);
            
        } catch (RemoteException ex) {
            Logger.getLogger(ClientControlleur.class.getName()).log(Level.SEVERE, null, ex);
        }
        
    }
    
    /**
     * Méthode appelé quand le serveur confirme la connexion ou la déconnexion
     * @param connected TRUE si le client se connecte, FALSE sinon
     */
    public void setConnected(boolean connected)
    {
        this.connected = true;
        clientView.changeAfficheConnection(connected);
        if (connected)
            afficherMessage("\nLe client " + name + " s'est connecté");
        else 
        {
            try {
                Naming.unbind(name);
                afficherMessage("\nLe client " + name + " s'est déconnecté");
                
            } catch (RemoteException ex) {
                Logger.getLogger(ClientControlleur.class.getName()).log(Level.SEVERE, null, ex);
            } catch (NotBoundException ex) {
                Logger.getLogger(ClientControlleur.class.getName()).log(Level.SEVERE, null, ex);
            } catch (MalformedURLException ex) {
                Logger.getLogger(ClientControlleur.class.getName()).log(Level.SEVERE, null, ex);
            }
            
        }
    }
            
    /**
     * Permet de ne plus suivre un stock option
     * @param ligne ligne à supprimer dans la liste Stock option suivie
     * @param name Nom du stock option
     */
    public void removeFollowedStockOption(int ligne, String name)
    {
        try 
        {
            clientView.addStockOptionDisponible(name, ligne);
            StockOptionContract contract = stockOptions.get(name);
            contract.removeFollower(exchangeClient);
        } catch (RemoteException ex) {
            Logger.getLogger(ClientControlleur.class.getName()).log(Level.SEVERE, null, ex);
        }
        
    }
    
    /**
     * Permet d'afficher un message dans le textArea
     * @param message message à afficher
     */
    public void afficherMessage(String message)
    {
        clientView.addMessage(message);
    }

    /**
     * Supprimer les stocks options
     * @param name nom dus stock options
     */
    public void supprimerStockOption(String name) 
    {
        clientView.supprimerStockOption(name);
        stockOptions.remove(name);
    }

    /**
     * Permet d'afficher les infos du stocks options
     * @param stock nom du stock option
     */
    void demandeInfo(String stock) 
    {
        try {
            // Récupère les infos
            StockOptionContract stockOption = stockOptions.get(stock);
            String nameStock = stock;
            String companie = stockOption.getCompany();
            int quote = (int) stockOption.getCurrentQuote();
            
            // Affiche les infos
            clientView.afficherAlert("Nom : " + nameStock + " \nCompanie : " + companie +
                    "Quote actuelle : " + quote  , "Information sur le stock option" + nameStock);
            
        } catch (RemoteException ex) {
            Logger.getLogger(ClientControlleur.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    /**
     * Ajoute un stock option
     * @param stock contract du stock option
     */
    void addStockOption(StockOptionContract stock) 
    {
        try {
            String nameStock = stock.getName();
            stockOptions.put(nameStock, stock);
            clientView.addStockOption(nameStock);
        } catch (RemoteException ex) {
            Logger.getLogger(ClientControlleur.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
