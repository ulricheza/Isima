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

import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;

import chucknorrisfact.controlleur.DetailViewController;
import chucknorrisfact.pro.R;

/**
 * Vue affichant les details d'une fact 
 * @author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 *
 */
public class DetailView extends Activity implements OnClickListener{

	private DetailViewController mDetailViewController;
	private EditText mEditId;
	private EditText mEditFact;
	
	Button mButtonHasard;
	Button mButtonPrecedent;
	Button mButtonSuivant;

	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        
    	super.onCreate(savedInstanceState);
        setContentView(R.layout.detailview);
        
        //Recuperation des elements de la vue
        mEditId			= (EditText) findViewById(R.id.EditId);
        mEditFact		= (EditText) findViewById(R.id.EditFact);
        
        mButtonHasard = (Button)findViewById(R.id.ButtonHasard);
        mButtonPrecedent = (Button)findViewById(R.id.Precedent);
        mButtonSuivant = (Button)findViewById(R.id.Suivant);
        
        mButtonHasard.setOnClickListener(this);
        mButtonPrecedent.setOnClickListener(this);
        mButtonSuivant.setOnClickListener(this);
        
        mDetailViewController = new DetailViewController(this);
        
        //recuperation des parametres de l'activite precedente
        Bundle objetbunble  = this.getIntent().getExtras(); 
        int position = objetbunble.getInt("Position");
        
        //Affichage de la fact full-text
        String textFact = mDetailViewController.recupererFact(position);
    
        //Affichage du numero de l'id
        mEditId.setText((CharSequence)String.valueOf(mDetailViewController.recupererId(position)));
        mEditFact.setText( (CharSequence) textFact );
    }


	public void onClick(View v) {
		if (mButtonHasard == v ){ //Clic sur le bouton hasard
			mDetailViewController.afficherRandomFact();
		}
		else if (mButtonSuivant == v ){ //Clic sur le bouton suivant
	        //recuperation des parametres de l'activite precedente
	        Bundle objetbunble  = this.getIntent().getExtras(); 
	        int position = objetbunble.getInt("Position");
	        
	        mDetailViewController.afficherFactSuivant(position);
		}
		else if (mButtonPrecedent == v) // Clic sur le bouton précédent
		{
	        //recuperation des parametres de l'activite precedente
	        Bundle objetbunble  = this.getIntent().getExtras(); 
	        int position = objetbunble.getInt("Position");
	        
	        mDetailViewController.afficherTractPrecedent(position);
		}
	}

}
