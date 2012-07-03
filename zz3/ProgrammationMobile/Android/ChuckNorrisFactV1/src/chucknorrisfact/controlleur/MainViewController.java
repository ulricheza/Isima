/*
 * -------------------------------------------------------------------------------
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *-------------------------------------------------------------------------------"
 */

package chucknorrisfact.controlleur;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;

import java.io.FileNotFoundException;
import java.io.IOException;

import chucknorrisfact.modele.Fact;
import chucknorrisfact.modele.ListFact;
import chucknorrisfact.pro.R;
import chucknorrisfact.vue.DetailView;
import chucknorrisfact.vue.MainView;

/**
 * Controlleur associe la vue principale
 * @author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 * 
 */
public class MainViewController {
	private ListFact mListFact;
	private MainView mMainView;
	private Context mContextApplication;

	/**
	 * Constructeur du controlleur
	 * @param mainView Vue principale
	 * @param context Contexte de l'application
	 * 
	 */
	public MainViewController(MainView mainView, Context context) {
		this.mContextApplication = context;
		this.mMainView = mainView;
		parser();
	}

	/**
	 * Permet d'appeler la fenetre de fact
	 * @param id id de la fact
	 * 
	 */
	public void afficherFact(int id) {
		Fact fact = mListFact.getAt(id);
		traitementAffichageFact(fact);
	}

	/**
	 * Afficher une fact au hasard
	 * 
	 */
	public void afficherRandomFact() {
		Fact fact = mListFact.getHasard();
		traitementAffichageFact(fact);
	}

	/**
	 * Traitement de l'affichage d'une fact
	 * @param fact Fact a afficher
	 * 
	 */
	private void traitementAffichageFact(Fact fact) {
		Intent i = new Intent(mMainView, DetailView.class);
		// Verifie si la fact existe
		if (fact == null){
			mMainView.messageAlerte(mContextApplication.getString(R.string.fact_manquante));
		}
		else {
			// Enregistrer l'id pour l'activite suivante
			Bundle objetbunble = new Bundle();
			objetbunble.putInt("Id", fact.getId());
			i.putExtras(objetbunble);

			// Demarrer l'Activity
			mMainView.startActivity(i);
		}
	}

	/**
	 * Permet de parser le fichier csv et remplie la liste de fact
	 */
	private void parser() {
		try {
			mListFact = ParserCSV.readFacts(mContextApplication);
		} catch (FileNotFoundException e) {
			mMainView.messageAlerte(mContextApplication.getString(R.string.ressource_manquante));
		} catch (IOException e) {
			mMainView.messageAlerte(mContextApplication.getString(R.string.ressource_illisible));
		}
	}
}
