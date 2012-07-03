/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package fr.isima.entity;

import java.io.Serializable;
import javax.persistence.Basic;
import javax.persistence.Column;
import javax.persistence.Embeddable;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;

/**
 *
 * @author maxime
 */
@Embeddable
public class PersonnePK implements Serializable {
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 255)
    @Column(name = "prenom", nullable = false, length = 255)
    private String prenom;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 255)
    @Column(name = "nom", nullable = false, length = 255)
    private String nom;

    public PersonnePK() {
    }

    public PersonnePK(String prenom, String nom) {
        this.prenom = prenom;
        this.nom = nom;
    }

    public String getPrenom() {
        return prenom;
    }

    public void setPrenom(String prenom) {
        this.prenom = prenom;
    }

    public String getNom() {
        return nom;
    }

    public void setNom(String nom) {
        this.nom = nom;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (prenom != null ? prenom.hashCode() : 0);
        hash += (nom != null ? nom.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof PersonnePK)) {
            return false;
        }
        PersonnePK other = (PersonnePK) object;
        if ((this.prenom == null && other.prenom != null) || (this.prenom != null && !this.prenom.equals(other.prenom))) {
            return false;
        }
        if ((this.nom == null && other.nom != null) || (this.nom != null && !this.nom.equals(other.nom))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "fr.isima.entity.PersonnePK[ prenom=" + prenom + ", nom=" + nom + " ]";
    }
    
}
