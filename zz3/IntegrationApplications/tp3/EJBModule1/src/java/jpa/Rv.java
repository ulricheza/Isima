/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package jpa;

import java.io.Serializable;
import java.util.Date;
import javax.persistence.Basic;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.Table;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;
import javax.validation.constraints.NotNull;
import javax.xml.bind.annotation.XmlRootElement;

/**
 *
 * @author JC
 */
@Entity
@Table(name = "rv")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Rv.findAll", query = "SELECT r FROM Rv r"),
    @NamedQuery(name = "Rv.findById", query = "SELECT r FROM Rv r WHERE r.id = :id"),
    @NamedQuery(name = "Rv.findByJour", query = "SELECT r FROM Rv r WHERE r.jour = :jour")})
public class Rv implements Serializable {
    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Basic(optional = false)
    @NotNull
    @Column(name = "ID")
    private Long id;
    @Basic(optional = false)
    @NotNull
    @Column(name = "JOUR")
    @Temporal(TemporalType.DATE)
    private Date jour;
    @JoinColumn(name = "ID_CLIENT", referencedColumnName = "ID")
    @ManyToOne(optional = false)
    private Clients idClient;
    @JoinColumn(name = "ID_CRENEAU", referencedColumnName = "ID")
    @ManyToOne(optional = false)
    private Creneaux idCreneau;

    public Rv() {
    }

    public Rv(Long id) {
        this.id = id;
    }

    public Rv(Long id, Date jour) {
        this.id = id;
        this.jour = jour;
    }
    
    public Rv(Long id,Date jour, Clients idClient, Creneaux idCreneau)
    {
        this.id         = id;
        this.jour       = jour;
        this.idClient   = idClient;
        this.idCreneau  = idCreneau;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public Date getJour() {
        return jour;
    }

    public void setJour(Date jour) {
        this.jour = jour;
    }

    public Clients getIdClient() {
        return idClient;
    }

    public void setIdClient(Clients idClient) {
        this.idClient = idClient;
    }

    public Creneaux getIdCreneau() {
        return idCreneau;
    }

    public void setIdCreneau(Creneaux idCreneau) {
        this.idCreneau = idCreneau;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (id != null ? id.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Rv)) {
            return false;
        }
        Rv other = (Rv) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "jpa.Rv[ id=" + id + " ]";
    }
    
}
