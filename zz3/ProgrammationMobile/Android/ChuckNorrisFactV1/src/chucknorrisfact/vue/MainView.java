/*
 * -------------------------------------------------------------------------------
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *-------------------------------------------------------------------------------"
 */

package chucknorrisfact.vue;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;

import chucknorrisfact.controlleur.MainViewController;
import chucknorrisfact.pro.R;


/**
 * Vue principale de l'application ChuckNorrisFact
 * @author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 *
 */
public class MainView extends Activity implements OnClickListener{
	
	private MainViewController mMainController;
	private Button mButtonRecherche;
	private Button mButtonHasard;
	private EditText mTextIdFact;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        //Recuperation des composants de la fenetre.
        mButtonRecherche	= (Button) findViewById(R.id.ButtonRecherche);
        mButtonHasard		= (Button) findViewById(R.id.ButtonHasard);
        mTextIdFact			= (EditText) findViewById(R.id.EditTextId);

        //Affectation des evenements pour les composants de l'activite
        mButtonHasard.setOnClickListener(this);
        mButtonRecherche.setOnClickListener(this);
        
        mMainController = new MainViewController(this, getApplicationContext());
    }

	public void onClick(View v) {
		if (mButtonHasard == v ){ //Clic sur le bouton afficher un fact au hasard
			mMainController.afficherRandomFact();
		}
		else if (mButtonRecherche == v ){ //Recherche de la fact par un ID
			if(mTextIdFact.getText().toString().compareTo("") != 0){
				int id = Integer.parseInt(mTextIdFact.getText().toString());
				mMainController.afficherFact(id);
			}
		}
	}
	
	/**
	 * Envoie de message d'alerte en pop-up
	 * @param message message a envoyer
	 */
	public void messageAlerte(String message)
	{
		AlertDialog.Builder builder = new AlertDialog.Builder(this);
		builder.setMessage(message);
		builder.setCancelable(false);
		builder.setNegativeButton("Ok", new DialogInterface.OnClickListener() {
					public void onClick(DialogInterface dialog, int id) {
					dialog.cancel();
				}
		});
		
		AlertDialog alert = builder.create();
		alert.show();
	}
}