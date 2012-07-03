/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package fr.isima.entity;

import java.io.Serializable;
import javax.persistence.*;
import javax.validation.constraints.Size;
import javax.xml.bind.annotation.XmlRootElement;

/**
 *
 * @author maxime
 */
@Entity
@Table(name = "personne", catalog = "agenda", schema = "")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Personne.findAll", query = "SELECT p FROM Personne p"),
    @NamedQuery(name = "Personne.findByMail", query = "SELECT p FROM Personne p WHERE p.mail = :mail"),
    @NamedQuery(name = "Personne.findByTelephone", query = "SELECT p FROM Personne p WHERE p.telephone = :telephone"),
    @NamedQuery(name = "Personne.findByPrenom", query = "SELECT p FROM Personne p WHERE p.personnePK.prenom = :prenom"),
    @NamedQuery(name = "Personne.findByNom", query = "SELECT p FROM Personne p WHERE p.personnePK.nom = :nom")})
public class Personne implements Serializable {
    private static final long serialVersionUID = 1L;
    @EmbeddedId
    protected PersonnePK personnePK;
    @Size(max = 255)
    @Column(name = "mail", length = 255)
    private String mail;
    @Size(max = 255)
    @Column(name = "telephone", length = 255)
    private String telephone;

    public Personne() {
    }

    public Personne(PersonnePK personnePK) {
        this.personnePK = personnePK;
    }

    public Personne(String prenom, String nom) {
        this.personnePK = new PersonnePK(prenom, nom);
    }

    public PersonnePK getPersonnePK() {
        return personnePK;
    }

    public void setPersonnePK(PersonnePK personnePK) {
        this.personnePK = personnePK;
    }

    public String getMail() {
        return mail;
    }

    public void setMail(String mail) {
        this.mail = mail;
    }

    public String getTelephone() {
        return telephone;
    }

    public void setTelephone(String telephone) {
        this.telephone = telephone;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (personnePK != null ? personnePK.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Personne)) {
            return false;
        }
        Personne other = (Personne) object;
        if ((this.personnePK == null && other.personnePK != null) || (this.personnePK != null && !this.personnePK.equals(other.personnePK))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "fr.isima.entity.Personne[ personnePK=" + personnePK + " ]";
    }
    
}
