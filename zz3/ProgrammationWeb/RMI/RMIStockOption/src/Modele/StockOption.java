/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package Modele;

import ContractProject.ClientContract;
import java.rmi.Remote;
import java.util.ArrayList;
import java.util.List;

/**
 * Classe qui représente un stock option
 * @author jcseptier
 */
public class StockOption implements Remote {
    
        private String title;       // Titre du stock option
        private String company;     // Nom de la companie du stock option
        private int quote;        // Quote du stock option
        
        // Liste des followers du stock option
        private List<ClientContract> followers = new ArrayList<ClientContract>();

        /**
         * Constructeur du stock option
         * @param tt Titre du stock option
         * @param co Nom de la companie du stock option
         * @param qt Quote du stock option
         */
        public StockOption(String tt, String co, int qt) {
          super();
          title = tt;
          company = co;
          quote = qt;
        }
        
        /**
         * Change le titre du stock option
         * @param title le titre du stock option
         */
        public void setTitle(String title) {
            this.title = title;
        }
        
        /**
         * Retourne le titre du stock option
         * @return le titre
         */
        public String getTitle() {
                return title;
        }
        
        /**
         * Retourne le nom de la companie du stock option
         * @return le nom de la companie
         */
        public String getCompany() {
                return company;
        }
        
        /**
         * Change le nom de la compagnie du stock option
         * @param value nom de la compagnie
         */
        public void setCompany(String value) {
            company = value;
        }
        
        /**
         * Retourne la quote du stock option
         * @return la quote
         */
        public int getQuote() {
                return quote;
        }
        
        /**
         * Change la quote
         * @param value la quote
         */
        public void setQuote(int value) {
                quote = value;
        }
        
        /**
         * Retourne la liste des followers
         * @return La liste des followers
         */
         public List<ClientContract> getFollowers() {
            return followers;
        }
         
        /**
          * Change la liste des Followers
          * @param followers La liste des followers
          */
        public void setFollowers(List<ClientContract> followers) {
            this.followers = followers;
        }
        
        /**
         * Ajoute un follower
         * @param follower le follower à ajouter
         */
        public boolean addFollower(ClientContract follower)
        {
            synchronized (follower)
            {
                followers.add(follower);
            }
            return true; // TODO
        }
        
        /**
         * Supprime un follower de la liste
         * @param follower le follower à supprimer
         * @return TRUE si le follower est supprimé, FALSE sinon
         */
        public boolean removeFollower(ClientContract follower)
        {
            synchronized (follower)
            {
                return followers.remove(follower);
            }
        }

        public void clearFollowers() 
        {
            synchronized (followers)
            {
                followers.clear();
            }
        }
        
}