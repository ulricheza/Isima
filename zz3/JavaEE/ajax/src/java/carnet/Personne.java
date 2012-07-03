/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package carnet;

/**
 *
 * @author maxime
 */
public class Personne {

    private String nom;
    private String prenom;
    private String mail;
    private String telephone;

    public Personne() {
    }

    public String getMail() {
        return mail;
    }

    public void setMail(String mail) {
        this.mail = mail;
    }

    public String getNom() {
        return nom;
    }

    public void setNom(String nom) {
        this.nom = nom;
    }

    public String getPrenom() {
        return prenom;
    }

    public void setPrenom(String prenom) {
        this.prenom = prenom;
    }

    public String getTelephone() {
        return telephone;
    }

    public void setTelephone(String telephone) {
        this.telephone = telephone;
    }
}
