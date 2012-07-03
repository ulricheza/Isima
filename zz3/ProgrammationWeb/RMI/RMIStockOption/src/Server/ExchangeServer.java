/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package Server;

import ContractProject.ExchangeContract;
import java.rmi.Naming;
import java.rmi.Remote;

/**
 * Méthode permettant de démarrer le serveur de simulation de la bourse
 * @author Jean-Christophe SEPTIER Maxime ESCOURBIAC
 */
class ExchangeServer 
{
        /**
         * Démarre notre serveur
         * @param arg arguments en ligne de commande
         */
	public static void main(String[] arg) {
		try {
			ExchangeSkeleton esk = new ExchangeSkeleton();
			Naming.bind(ExchangeContract.EXCHANGE_IDENTITY, (Remote) esk);
			System.out.println("Exchange server is running...");
                        
                        // Création de quelques actions
                        esk.addStockOption( "BNP" , "BNP Paribas" , 1000 );
                        esk.addStockOption( "CreditA", "Crédit Agricol", 2300);
                        esk.addStockOption( "ALCATEL", "ALCATEL-LUCENT", 5);
                        
                        // Démarre le serveur et la simulation
			esk.start();          
                        
		} catch(Exception e) {
			System.err.println(e);
			System.exit(1);
		}
	}
}
