/*
 * -------------------------------------------------------------------------------
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *-------------------------------------------------------------------------------"
 */

package chucknorrisfact.controlleur;

import chucknorrisfact.modele.Fact;
import chucknorrisfact.modele.ListFact;
import chucknorrisfact.vue.DetailView;

/**
 * Controlleur associe l'affichage d'une fact
 * @author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 *
 */
public class DetailViewController {
	
	@SuppressWarnings("unused") //Pour les regles de l'art du MVC et sera utilise dans la version V2
	private DetailView mDetailView;
	private ListFact mListFact;
	
	/**
	 * Constructeur de la classe DetailViewController
	 * @param view Vue dettaillant un fact
	 */
	public DetailViewController( DetailView view)
	{
		this.mDetailView = view;
		this.mListFact = ListFact.getInstance();
	}
	
	/**
	 * Retourne le texte du fact correspondant l'id
	 * @param id du fact
	 * @return le texte du fact
	 */
	public String recupererFact(int id)
	{
		Fact maFact = mListFact.getAt(id);
		return maFact.getText();
	}
}
