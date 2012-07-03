/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package firstcup.entity;

import java.io.Serializable;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import javax.persistence.*;

/**
 *
 * @author maxime
 */
@Entity
@NamedQueries({
    @NamedQuery(name = "findOldestFirstcupuser", query = "SELECT MIN(u.birthday) FROM FirstcupUser u"),
    @NamedQuery(name = "findYoungestFirstcupuser", query = "SELECT MAX(u.birthday) FROM FirstcupUser u")
})
public class FirstcupUser implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;

    public FirstcupUser() {
    }

    public FirstcupUser(Date date) {
        Calendar cal = new GregorianCalendar();
        cal.setTime(date);
        this.birthday = cal;

    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }
    @Temporal(javax.persistence.TemporalType.DATE)
    private Calendar birthday;

    /**
     * Get the value of birthday
     *
     * @return the value of birthday
     */
    public Calendar getBirthday() {
        return birthday;
    }

    /**
     * Set the value of birthday
     *
     * @param birthday new value of birthday
     */
    public void setBirthday(Calendar birthday) {
        this.birthday = birthday;
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
        if (!(object instanceof FirstcupUser)) {
            return false;
        }
        FirstcupUser other = (FirstcupUser) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "firstcup.entity.FirstCupUser[ id=" + id + " ]";
    }
}
