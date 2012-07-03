/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package guess;

import java.util.Calendar;
import java.util.Locale;
import java.util.Random;
import java.util.ResourceBundle;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import javax.faces.context.FacesContext;

/**
 *
 * @author maxime
 */
@ManagedBean
@SessionScoped
public class LoicBean {

    private String phrase;
    private int typePhrase; //0 Je pense, 1 : petit, 2 : grand , 3 :fin, 4 : erreur
    private String utilisateur;
    private int nombreCache;
    private Random random;
    private int essai;
    private ResourceBundle bundle;
    private String localisation;

    /**
     * Creates a new instance of LoicBean
     */
    public LoicBean() {

        typePhrase = 0;
        utilisateur = "Nb";
        random = new Random(Calendar.getInstance().get(Calendar.SECOND));
        nombreCache = (int) (random.nextFloat() * 100.0);
        essai = 0;
        localisation = FacesContext.getCurrentInstance().getViewRoot().getLocale().toLanguageTag();
        bundle = ResourceBundle.getBundle("messages",
                FacesContext.getCurrentInstance().getViewRoot().getLocale());
        phrase = bundle.getString("phrase.bienvenue");
    }

    public void comparer() {
        ++essai;
        try {
            int user = Integer.parseInt(utilisateur);
            if (user == nombreCache) {
                phrase = bundle.getString("phrase.fin");
                typePhrase = 3;
            } else {
                if (user > nombreCache) {
                    phrase = bundle.getString("phrase.grand");
                    typePhrase = 2;
                } else {
                    phrase = bundle.getString("phrase.petit");
                    typePhrase = 1;
                }
            }
        } catch (NumberFormatException ex) {
            phrase = bundle.getString("erreur");
            typePhrase = 4;
        }
    }

    public String getPhrase() {
        String result = "";
        switch (typePhrase) {
            case 0:
                result = bundle.getString("phrase.bienvenue");
                break;
            case 1:
                result = bundle.getString("phrase.petit");
                break;
            case 2:
                result = bundle.getString("phrase.grand");
                break;
            case 3:
                result = bundle.getString("phrase.fin");
                break;
            case 4:
                result = bundle.getString("erreur");
                break;
        }
        return result;
    }

    public String getUtilisateur() {
        return utilisateur;
    }

    public void setUtilisateur(String utilisateur) {
        this.utilisateur = utilisateur;
    }

    public String getLocalisation() {
        return localisation;
    }

    public void setLocale(String locale) {
        switch (locale) {
            case "FR":
                bundle = ResourceBundle.getBundle("messages", Locale.FRENCH);
                localisation = Locale.FRENCH.toLanguageTag();
                break;
            case "EN":
                bundle = ResourceBundle.getBundle("messages", Locale.ENGLISH);
                localisation = Locale.ENGLISH.toLanguageTag();
        }
    }
}
