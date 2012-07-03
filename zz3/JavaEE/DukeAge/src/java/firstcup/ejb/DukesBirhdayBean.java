/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package firstcup.ejb;

import firstcup.entity.FirstcupUser;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.logging.Logger;
import javax.ejb.Stateless;
import javax.ejb.LocalBean;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;

/**
 *
 * @author maxime
 */
@Stateless
@LocalBean
public class DukesBirhdayBean {

    private static final Logger logger = Logger.getLogger("firstcup.ejb.DukesBirthdayBean");
    @PersistenceContext(unitName = "DukeAgePU")
    private EntityManager em;

    public int getAgeDifference(Date date) {
        int ageDifference;
        Calendar theirBirthday = new GregorianCalendar();
        Calendar dukesBirthday = new GregorianCalendar(1995, Calendar.MAY, 23);
        // Set the Calendar object to the passed in Date
        theirBirthday.setTime(date);
        // Subtract the user’s age from Duke’s age
        ageDifference = dukesBirthday.get(Calendar.YEAR)
                - theirBirthday.get(Calendar.YEAR);
        logger.info("Raw ageDifference is: " + ageDifference);
        // Check to see if Duke’s birthday occurs before the user’s. If so,
        // subtract one from the age difference
        if (dukesBirthday.before(theirBirthday) && (ageDifference > 0)) {
            ageDifference--;
        }
        // create and store the user’s birthday in the database
        FirstcupUser user = new FirstcupUser(date);
        em.persist(user);
        logger.info("Final ageDifference is: " + ageDifference);
        return ageDifference;
    }
    
    public Calendar getOldest
}
