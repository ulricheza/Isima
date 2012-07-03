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
import java.util.Collections;
import java.util.Random;


/**
 * Classe modelisant la liste des fact, utilise le design pattern singleton
 * @author Maxime ESCOURBIAC - Jean-Christophe SEPTIER
 *
 */
public class ListFact {

	private static ListFact mInstance; 
    private ArrayList<Fact> mListe;		// Liste de fact
    private Random mGenerator;			// Générateur de nombre aléatoire

    /**
     * Constructeur par defaut de la classe ListFact
     */
    private ListFact() {
        mListe = new ArrayList<Fact>();
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
        mListe.add(fact);
    }

    /**
     * Methode d'ajout d'une fact a la liste 
     * @param id Id de la fact
     * @param text Full-Text de la fact
     * @param type Type de la fact
     * 
     */
    public void addFact(int id, String text, ArrayList<String> type) {
        mListe.add(new Fact(id, text, type));
    }

    /**
     * Recherche d'une fact a l'aide de sa position
     * @param position Position de la fact a rechercher
     * @return La fact d'indice id si elle existe sinon null
     */
    public Fact getAt(int position) 
    {
        return mListe.get(position);
    }
      
    /**
     * Methode de recuperation d'une fact au hasard
     * @return Une fact tire au hasard
     */
    public Fact getHasard() 
    {
       	Fact result = null;
    	result = mListe.get( mGenerator.nextInt(mListe.size() ) ); //on tire une fact aleatoire avec la liste des cles.
    	
        return result;
    }
    
    /**
     * Methode de recuperation d'une position au hasard
     * @return Une fact tire au hasard
     */
    public int getHasardPosition() 
    {
       	return mGenerator.nextInt(mListe.size() ); //on tire une fact aleatoire avec la liste des cles.
    }
    
    /**
     * Donne la taille de la liste
     * @return
     */
    public int getSize()
    {
    	return mListe.size();
    }
    
    /**
     * Permet de trier la liste
     */
    public void sort()
    {
    	Collections.sort(mListe);
    }
    
	/**
	 * Getter de la liste
	 * @return la liste
	 */
	public ArrayList<Fact> getListe() {
		return mListe;
	}

	/**
	 * Setter de liste
	 * @param Liste Liste
	 */
	public void setListe(ArrayList<Fact> Liste) {
		this.mListe = Liste;
	}
}


