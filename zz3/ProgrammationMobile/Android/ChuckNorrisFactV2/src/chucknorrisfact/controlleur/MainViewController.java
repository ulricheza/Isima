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

import chucknorrisfact.vue.DetailView;
import chucknorrisfact.vue.MainView;

/**
 * Controlleur associe la vue principale
 * @author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 * 
 */
public class MainViewController {

	private MainView mMainView; // Vue principale

	/**
	 * Constructeur du controlleur
	 * @param mainView Vue principale
	 * 
	 */
	public MainViewController(MainView mainView) {
		this.mMainView = mainView;
	}

	/**
	 * Permet d'appeler la fenetre de fact
	 * @param position position de la fact
	 * 
	 */
	public void afficherFact(int position) {
		traitementAffichageFact(position);
	}

	
	
	/**
	 * Traitement de l'affichage d'une fact
	 * @param position position de la fact
	 */
	private void traitementAffichageFact(int position) {
		Intent i = new Intent(mMainView, DetailView.class);
	
		Bundle objetbunble = new Bundle();
		objetbunble.putInt("Position", position);
		i.putExtras(objetbunble);

		// Demarrer l'Activity
		mMainView.startActivity(i);
		
	}

}
