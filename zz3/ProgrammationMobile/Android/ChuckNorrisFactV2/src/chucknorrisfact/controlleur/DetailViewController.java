/*
 * -------------------------------------------------------------------------------
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *-------------------------------------------------------------------------------"
 */

package chucknorrisfact.controlleur;

import android.content.Intent;
import android.os.Bundle;
import chucknorrisfact.modele.Fact;
import chucknorrisfact.modele.ListFact;
import chucknorrisfact.vue.DetailView;

/**
 * Controlleur associe l'affichage d'une fact
 * @author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 * 
 */
public class DetailViewController {

	private DetailView mDetailView; // DetailView associe au controlleur
	private ListFact mListFact; // Liste des facts

	/**
	 * Constructeur de la classe DetailViewController
	 * @param view Vue detaillant un fact
	 * 
	 */
	public DetailViewController(DetailView view) {
		this.mDetailView = view;
		this.mListFact = ListFact.getInstance();
	}

	/**
	 * Retourne le texte du fact correspondant à la position dans la liste
	 * @param position Position du fact
	 * @return le texte du fact
	 */
	public String recupererFact(int position) {
		Fact maFact = mListFact.getAt(position);
		return maFact.getText();
	}

	/**
	 * Retourne l'id du fact correspondant à la position dans la liste
	 * @param position Position du fact
	 * @return id du fact
	 */
	public int recupererId(int position) {
		return mListFact.getAt(position).getId();
	}

	/**
	 * Permet d'afficher le fact suivant
	 * @param position Position du fact actuel
	 * 
	 */
	public void afficherFactSuivant(int position) {
		int newPosition = position + 1;
		// Si dernier fact, on revient au début
		if (newPosition == mListFact.getSize()) {
			newPosition = 0;
		}
		traitementAffichageFact(newPosition);
	}

	/**
	 * Permet d'afficher le fact précédent
	 * @param position Position du fact
	 * 
	 */
	public void afficherTractPrecedent(int position) {
		int newPosition = position - 1;
		// Si premier fact, on revient à la fin
		if (newPosition == -1) {
			newPosition = mListFact.getSize() - 1;
		}
		traitementAffichageFact(newPosition);
	}

	/**
	 * Traitement de l'affichage d'une fact
	 * @param fact Fact a afficher
	 * 
	 */
	private void traitementAffichageFact(int position) {

		Intent i = new Intent(mDetailView, DetailView.class);

		// Passer la position
		Bundle objetbunble = new Bundle();
		objetbunble.putInt("Position", position);
		i.putExtras(objetbunble);

		// Demarrer l'Activity
		mDetailView.startActivity(i);

	}

	/**
	 * Afficher une fact au hasard
	 * 
	 */
	public void afficherRandomFact() {
		traitementAffichageFact(mListFact.getHasardPosition());
	}
}
