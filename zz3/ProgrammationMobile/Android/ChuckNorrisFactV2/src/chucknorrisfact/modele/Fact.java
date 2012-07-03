/*
 * -------------------------------------------------------------------------------
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *-------------------------------------------------------------------------------"
 */

package chucknorrisfact.modele;

import java.util.ArrayList;

/**
 * Classe modelisant un Chuck Norris Fact
 * @author Maxime ESCOURBIAC - Jean-Christophe SEPTIER
 *
 */
public class Fact implements Comparable<Fact> {

    private int mId;
    private String mText;
    ArrayList<String> mType;

    /**
     * Constructeur par defaut de la classe Fact
     */
    public Fact()
    {
        this.mId = -1;
        this.mText = "";
        this.mType = new ArrayList<String>();
    }
    /**
     * Constructeur de la classe Fact
     * @param id ID de la fact
     * @param text Plein texte de la fact
     */
    public Fact(int id, String text) {
        this.mId = id;
        this.mText = text;
        this.mType = new ArrayList<String>();
    }
    
    /**
     * Constructeur de la classe Fact
     * @param id
     * @param text
     * @param type
     */
    public Fact(int id, String text, ArrayList<String> type)
    {
        this.mId = id;
        this.mText = text;
        this.mType = type;
    }

    /**
     * Getter de l'id du fact
     * @return ID du fact
     */
    public int getId() {
        return mId;
    }

    /**
     * Setter de l'id du fact
     * @param id ID du fact
     */
    public void setId(int id) {
        this.mId = id;
    }

    /**
     * Getter du plein text de la fact
     * @return Le text du fact
     */
    public String getText() {
        return mText;
    }

    /**
     * Setter du plein text de la fact
     * @param text Text de la fact
     */
    public void setText(String text) {
        this.mText = text;
    }

    /**
     * Getter de la liste des types du fact
     * @return La liste des types du fact
     */
    public ArrayList<String> getType() {
        return mType;
    }

    /**
     * Setter de la liste des types du fact
     * @param type La liste des types du fact
     */
    public void setType(ArrayList<String> type) {
        this.mType = type;
    }
    

    /**
     * Permet de comparer les facts entre elles pour le tri
     */
	public int compareTo(Fact another) {
		if(mId == another.getId())
			return 0;
		else if(mId < another.getId())
			return -1;
		else return 1;
	}
}