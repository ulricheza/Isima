/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package guess;

import java.util.Calendar;
import java.util.Random;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;

/**
 *
 * @author maxime
 */
@ManagedBean
@SessionScoped
public class LoicBean {

    private String phrase;
    private String utilisateur;
    private int nombreCache;
    private Random random;
    private int essai;

    /**
     * Creates a new instance of LoicBean
     */
    public LoicBean() {
        phrase = "Je pense &agrave; un nombre entre <strong>1</strong> et <strong>100</strong>. Pouvez-vous le trouver ?";
        utilisateur = "Nb";
        random = new Random(Calendar.getInstance().get(Calendar.SECOND));
        nombreCache = (int) (random.nextFloat() * 100.0);
        essai = 0;
    }

    public void comparer() {
        ++essai;
        try {
            int user = Integer.parseInt(utilisateur);
            if (user == nombreCache) {
                phrase = "Bravo :" + essai + " coup(s)";
            } else {
                if (user > nombreCache) {
                    phrase = "trop grand";
                } else {
                    phrase = "trop petit";
                }
            }
        } catch (NumberFormatException ex) {
            phrase = "On a dit un nombre";
        }
    }

    public String getPhrase() {
        return phrase;
    }

    public String getUtilisateur() {
        return utilisateur;
    }

    public void setUtilisateur(String utilisateur) {
        this.utilisateur = utilisateur;
    }
}
