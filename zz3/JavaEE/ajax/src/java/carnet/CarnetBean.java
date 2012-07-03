/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package carnet;

import java.util.ArrayList;
import java.util.List;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;

/**
 *
 * @author maxime
 */
@ManagedBean
@SessionScoped
public class CarnetBean {

    private List<Personne> personnes;
    private Personne personneDetail;

    /**
     * Creates a new instance of CarnetBean
     */
    public CarnetBean() {
        personnes = new ArrayList<Personne>();
        Personne pers = new Personne();
        pers.setPrenom("Maxime");
        pers.setNom("Escourbiac");
        pers.setMail("maxime.escourbiac@gmail.com");
        pers.setTelephone("0626246789");
        personnes.add(pers);
        pers = new Personne();
        pers.setPrenom("Alex");
        pers.setNom("Escourbiac");
        pers.setMail("alex.escourbiac@gmail.com");
        pers.setTelephone("0626246789");
        personnes.add(pers);
        pers = new Personne();
        pers.setPrenom("Nanard");
        pers.setNom("Escourbiac");
        pers.setMail("nanard.escourbiac@gmail.com");
        pers.setTelephone("0626246789");
        personnes.add(pers);
        pers = new Personne();
        pers.setPrenom("Bribri");
        pers.setNom("Escourbiac");
        pers.setMail("bribri.escourbiac@gmail.com");
        pers.setTelephone("0626246789");
        personnes.add(pers);
    }

    public int getSize() {
        return personnes.size();
    }

    public String getDescriptifCourt(int index) {
        Personne pers = personnes.get(index);
        return pers.getPrenom() + " " + pers.getNom();
    }

    public String getNom(int index) {
        return personnes.get(index).getNom();
    }

    public String getPrenom(int index) {
        return personnes.get(index).getPrenom();
    }

    public String getMail(int index) {
        return personnes.get(index).getMail();
    }

    public String getTelephone(int index) {
        return personnes.get(index).getTelephone();
    }
    
        public String getNomDetail() {
        return personneDetail.getNom();
    }

    public String getPrenomDetail() {
        return personneDetail.getPrenom();
    }

    public String getMailDetail() {
        return personneDetail.getMail();
    }

    public String getTelephoneDetail() {
        return personneDetail.getTelephone();
    }
    
    public String getDetail(int index){
        personneDetail = personnes.get(index);
        return "detail";
    }
    
}
