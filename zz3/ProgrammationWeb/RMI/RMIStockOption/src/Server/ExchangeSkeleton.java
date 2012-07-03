/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package Server;

import ContractProject.AdministrateurContract;
import ContractProject.ClientContract;
import ContractProject.ExchangeContract;
import ContractProject.StockOptionContract;
import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

import java.util.Random;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.concurrent.ConcurrentHashMap;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Squelette de l'échange. Représente les échanges entre le serveur et les clients
 * @author Jean-Christophe SEPTIER Maxime ESCOURBIAC
 */
class ExchangeSkeleton extends UnicastRemoteObject implements ExchangeContract, Runnable {
    
        private static int HEURE_DEBUT  = 9;    // Heure d'ouverture de la bourse
        private static int HEURE_FIN    = 18;   // Heure de fermeture de la bourse
        private static int VARIATION    = 2;    // Variation maximale de la quote
        private static int TEMPS_ATTENTE= 3;    // Temps d'attente en seconde
    
  	private Map<String, StockOptionContract> stockOptions; // Map avec les contrats de stocks options
	private Map<String, ClientContract> clients;           // Map avec les contrats des clients
        private Map<String, AdministrateurContract> admins;    // Map avec les contrats d'admins

        private int nbAdmin;
        
        private boolean end;        // Fin du serveur 
        
	private int heure;          // Heure de simulation
        private int jour;           // Jour
        
        private int variation;    // Variation de la journée
        
        private int limite;       // Limite sous laquelle le stock option est supprimé
        
        /**
         * Constructeur du squelette
         */
        public ExchangeSkeleton() throws RemoteException {
		super();
                
                stockOptions    = new ConcurrentHashMap<String, StockOptionContract>();
                clients         = new ConcurrentHashMap<String, ClientContract>();
                admins          = new ConcurrentHashMap<String, AdministrateurContract>();
                end             = false;
                limite          = 0;
                nbAdmin         = 0;
	}
	
        /**
         * Démarre un thread du serveur
         */
        public void start() {
		new Thread(this).start();
	}
	
        /**
         * Connection d'un client au serveur
         * @param nm nom du client
         * @return TRUE si le client est connecté, FALSE sinon
         */
        @Override
        public boolean connect(String nm) throws RemoteException {
                boolean connected = false;
                
		try {
                        // Vérifie si le nom est déjà présent ou non
                        if ( !clients.containsKey(nm))
                        {
                            // Ajoute le client avec le nom correspondant
                            ClientContract cc = (ClientContract) Naming.lookup(nm);
                            cc.setConnected(true);
                            synchronized(clients) {
                                    clients.put(nm,cc);
                            }
                            
                            connected = true;
                        }
                        
		} catch(Exception e) {
                  System.err.println(e);
            }
                return connected;
	}
        
         /**
         * Connection d'un administrateur
         * @param admin de l'administrateur
         * @return Nom réservé pour l'administrateur
         */
        @Override
        public String connectAdmin(AdministrateurContract admin) throws RemoteException {
                
                String name = "admin" + nbAdmin;
                nbAdmin++;
                
		try {
                        // Vérifie si le nom est déjà présent ou non
                        if ( !admins.containsKey(name))
                        {
                            // Ajoute le client avec le nom correspondant
                            Naming.bind(name, admin);

                            synchronized(admins) 
                            {
                                    admins.put(name,admin);
                            }

                        }
                        
		} catch(Exception e) {
                  System.err.println(e);
            }
                return name;
	}
        
         /**
         * Deconnection d'un client
         * @param name nom du client a deconnecter
         */
        @Override
        public void disconnect(String name) throws RemoteException
        {
            try 
            {
                // Récupère le client correspondant au nom donné
                ClientContract user = (ClientContract) Naming.lookup(name);
                if (user != null) 
                {
                        // Deconnecter le client
                        clients.remove(name);
			user.setConnected(false);
                        
                        // Supprimer les subscriptions
                        for (Entry<String, StockOptionContract> entry : stockOptions.entrySet()) 
                        {
                            List<ClientContract> cl = entry.getValue().getFollowers();
                            cl.remove(user);
                        }
                        
		} 
                else 
                {
			throw new RemoteException("User " + name + " not found in the registry");
		}
            } catch (NotBoundException ex) {
                Logger.getLogger(ExchangeSkeleton.class.getName()).log(Level.SEVERE, "Probleme", ex);
            } catch (MalformedURLException ex) {
                Logger.getLogger(ExchangeSkeleton.class.getName()).log(Level.SEVERE, "Probleme", ex);
            } catch (RemoteException ex) {
                Logger.getLogger(ExchangeSkeleton.class.getName()).log(Level.SEVERE, "Probleme", ex);
            }
        }
        
        /**
         * Deconnection d'un administrateur
         * @param name nom du client a deconnecter
         */
        @Override
        public void disconnectedAdmin(String name) throws RemoteException
        {
                admins.remove(name);
        }
        
        /**
         * Simule la bourse
         */
        @Override
        public void run() {
            
            heure       = ExchangeSkeleton.HEURE_DEBUT;  // Heure de la bourse
            jour        = 1;                             // Jour de la bourse
            variation   = 0;                             // Variation de la journée
            
            // Début de simulation
            while (!end) {
            try {
                // Temps d'attente
                try {
                        Thread.sleep(ExchangeSkeleton.TEMPS_ATTENTE*1000);
                } catch(InterruptedException e) {
                        System.out.println("Shutdown...");
                        end = true;
                }
                
                // Si la bourse ferme
                if ( heure == ExchangeSkeleton.HEURE_FIN )
                {
                    // On change de jour
                    heure = ExchangeSkeleton.HEURE_DEBUT;
                    jour++;
                    
                    // Envoie l'information à tout le monde
                    List<ClientContract> allUsers = new ArrayList<ClientContract>();
                    for (Entry<String, ClientContract> current : clients.entrySet()) {
                        allUsers.add(current.getValue());
                    }
                    
                    // Envoyer la variation du jour
                    envoyerMessage("\nVariation du jour : " + variation, allUsers);
                    variation = 0;
                    
                    // Envoyer le jour
                    envoyerMessage("\n\n Jour " + jour, allUsers);
                }
                
                // Envoyer à tout le monde
                List<ClientContract> allUsers = new ArrayList<ClientContract>();
                for (Entry<String, ClientContract> current : clients.entrySet()) {
                    allUsers.add(current.getValue());
                }
                
                // Envoyer l'heure
                envoyerMessage( "\nHeure : " + heure , allUsers);
                
                // Simuler le stock option
                synchronized(stockOptions)
                {
                    for (Entry<String, StockOptionContract> entry : stockOptions.entrySet()) 
                    {
                        SimulateStockOption(entry.getValue());
                        
                    }
                }
                
                // Incrémente l'heure
                heure ++;

                } catch (RemoteException ex) {
                    Logger.getLogger(ExchangeSkeleton.class.getName()).log(Level.SEVERE, null, ex);
                }
       	}
    }

    /**
    *   Simulation d'un stock option 
    *   @param stockOption stock option à simuler
    */
    private void SimulateStockOption(StockOptionContract stockOption) 
    {                            
        try {
            // Liste des followers
            List<ClientContract> listClient = stockOption.getFollowers();
            
            // Nombre aléatoire entre VARIATION et - VARIATION
            Random rnd = new Random();
            int var = rnd.nextInt(ExchangeSkeleton.VARIATION*2) - ExchangeSkeleton.VARIATION*2;
            
            // Mise à jour de la quote et de la variation
            stockOption.setCurrentQuote(stockOption.getCurrentQuote() + var);
            this.variation += var;
            
            // Test de la limite
            if ( stockOption.getCurrentQuote() > limite)
            {
                // Envoie le message au followers
                envoyerMessage("\nStock option " + stockOption.getName()
                    + " ( " + stockOption.getCompany() + " ) : Nouvelle cote => " +
                    stockOption.getCurrentQuote(), listClient);
            }
            else
            {
                // Avertie les followers
                envoyerMessage("\nLe Stock option " + stockOption.getName()
                    + " est passé sous la limite autorisée", listClient);
                // Supprime le stock option
                removeStockOtion(stockOption.getName());
            }
            
        } catch (RemoteException ex) {
            Logger.getLogger(ExchangeSkeleton.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    /**
     * Retourne la liste des stocks options
     * @return une map avec le nom des stocks options et le contrat des stocks options
     */
    @Override
    public Map<String, StockOptionContract> getStockOption() throws RemoteException {
        return stockOptions;
    }

    /**
     * Permet de créer un stock option
     * @param name nom de l'action
     * @param company nom de la companie
     * @param quote valeur de la quote
     * @throws RemoteException 
     */
    @Override
    public void addStockOption(String name, String company, int quote) throws RemoteException 
    {
        if ( !stockOptions.containsKey(name))
        {
            // Créér les stocks options
            StockOptionSkeleton newStockOption = new StockOptionSkeleton(name, company, quote);
            stockOptions.put(name,newStockOption);
            
            // Envoyer à tout le monde
            List<ClientContract> allUsers = new ArrayList<ClientContract>();
               for (Entry<String, ClientContract> current : clients.entrySet()) {
                   // Rend disponible le stock option au client déjà connecté
                   current.getValue().ajouterStockOption(newStockOption);
                   allUsers.add(current.getValue());
            }
            // Envoie un message d'information
            envoyerMessage("\nNouveau stock option : " + name, allUsers);     
            
            // Préviens les administrateurs
            prevenirAdmin();
        }
    }

    /**
     * Supprimer un stock option
     * @param name nom du stock option
     */
    @Override
    public void removeStockOtion(String name) throws RemoteException 
    {
        synchronized (stockOptions)
        {
            try {
            // Envoie l'information à tout le monde
            List<ClientContract> allUsers = new ArrayList<ClientContract>();
            for (Entry<String, ClientContract> current : clients.entrySet()) {
                    // Supprimer le stock option au client déjà connecté
                    current.getValue().supprimerStockOption(name);
                    allUsers.add(current.getValue());
            }
            
            // Envoie un message d'information
            envoyerMessage("\nStock option supprimée : " + name, allUsers); 
            
            // Supprime les followers
            StockOptionContract stock = stockOptions.get(name);
            stock.clearFollowers();
            // Unbind le stock option
            Naming.unbind(name);
            stockOptions.remove(name);
            
            // Préviens les admins
            prevenirAdmin();
            
            } catch (NotBoundException ex) {
                Logger.getLogger(ExchangeSkeleton.class.getName()).log(Level.SEVERE, null, ex);
            } catch (MalformedURLException ex) {
                Logger.getLogger(ExchangeSkeleton.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        
    }
    
    /**
     * Permet d'envoyer un message à envoyer au client
     * @param message message a envoyer
     * @param users utilisateur qui vont recevoir le message
     * @throws RemoteException Exception d'envoie
     */
    private void envoyerMessage(String message, List<ClientContract> users) throws RemoteException {
        
	synchronized (users) {
            for (ClientContract user : users) {
		user.warn(message);
            }
	}

    }
    
    /**
     * Previens les administrateurs du changement
     */
    private void prevenirAdmin()
    {
        for (Entry<String, AdministrateurContract> current : admins.entrySet())
        {
            try {
                current.getValue().miseAJour();
            } catch (RemoteException ex) {
                Logger.getLogger(ExchangeSkeleton.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }

    /**
     * Retourne la limite
     * @return la limite
     */
    @Override
    public int getLimite() throws RemoteException {
        return limite;
    }

    /**
     * Change la limite
     * @param limite la limite
     */
    @Override
    public void setLimite(int limite) throws RemoteException {
        this.limite = limite;
        prevenirAdmin();
    }
}

