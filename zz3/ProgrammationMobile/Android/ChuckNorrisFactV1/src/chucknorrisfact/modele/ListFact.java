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
import java.util.HashMap;
import java.util.Map;
import java.util.Random;


/**
 * Classe modelisant la liste des fact, utilise le design pattern singleton
 * @author Maxime ESCOURBIAC - Jean-Christophe SEPTIER
 *
 */
public class ListFact {

	private static ListFact mInstance;
    private Map<Integer, Fact> mListe;
    private Random mGenerator;

    /**
     * Constructeur par defaut de la classe ListFact
     */
    private ListFact() {
        mListe = new HashMap<Integer, Fact>();
        mGenerator = new Random();         
    }
    
    /**
     * Getter de l'instance du singleton
     * @return L'unique instance de ListFact
     * 
     */
    public static ListFact getInstance()
    {
    	if(mInstance == null)
    	{
    		mInstance = new ListFact();
    	}
    	return mInstance;
    }

    /**
     * Methode d'ajout d'une fact a la liste
     * @param fact Fact a ajouter a la liste
     * 
     */
    public void addFact(Fact fact) {
        mListe.put(fact.getId(), fact);
    }

    /**
     * Methode d'ajout d'une fact a la liste 
     * @param id Id de la fact
     * @param text Full-Text de la fact
     * @param type Type de la fact
     * 
     */
    public void addFact(int id, String text, ArrayList<String> type) {
        mListe.put(id, new Fact(id, text, type));
    }

    /**
     * Recherche d'une fact a l'aide de son index
     * @param index Index de la fact a rechercher
     * @return La fact d'indice id si elle existe sinon null
     */
    public Fact getAt(int index) {
        return mListe.get(index);
    }

    /**
     * Methode de recuperation d'une fact au hasard
     * @return Une fact tire au hasard
     */
    public Fact getHasard() {
    	Fact result = null;
    	ArrayList<Integer> listKey = new ArrayList<Integer>(mListe.keySet()); //On recupere la liste des cles presentes dans la map
    	result = mListe.get(listKey.get(mGenerator.nextInt(listKey.size()))); //on tire une fact aleatoire avec la liste des cles.
        return result;
    }
}


