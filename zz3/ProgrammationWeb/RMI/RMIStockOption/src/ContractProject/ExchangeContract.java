package ContractProject;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.Map;


/**
 *  Contrat correspondant au échange avec le serveur
 * @author jcseptier
 */
public interface ExchangeContract extends Remote {
	
        public final static String host = "rmi://localhost/";
        
	public static final String EXCHANGE_IDENTITY = "SE_Service";
	
        public boolean connect(String nom) throws RemoteException;
        
        public void disconnect(String name) throws RemoteException;
        
        public Map<String, StockOptionContract> getStockOption() throws RemoteException;

	public void addStockOption(String name, String company, int quote) throws RemoteException;

	public void removeStockOtion(String name)throws RemoteException;
        
        public String connectAdmin(AdministrateurContract admin) throws RemoteException;
        
        public void disconnectedAdmin(String name) throws RemoteException;
        
        public int getLimite() throws RemoteException;
        
        public void setLimite(int limite) throws RemoteException;
}
