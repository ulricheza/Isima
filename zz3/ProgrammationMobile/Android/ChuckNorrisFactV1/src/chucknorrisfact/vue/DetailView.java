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
import android.widget.EditText;

import chucknorrisfact.controlleur.DetailViewController;
import chucknorrisfact.pro.R;

/**
 * Vue affichant les details d'une fact 
 * @author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 *
 */
public class DetailView extends Activity {

	private DetailViewController mDetailViewController;
	private EditText mEditId;
	private EditText mEditFact;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        
    	super.onCreate(savedInstanceState);
        setContentView(R.layout.detailview);
        
        //Recuperation des elements de la vue
        mEditId			= (EditText) findViewById(R.id.EditId);
        mEditFact		= (EditText) findViewById(R.id.EditFact);
        
        mDetailViewController = new DetailViewController(this);
        
        //recuperation des parametres de l'activite precedente
        Bundle objetbunble  = this.getIntent().getExtras(); 
        int idFact = objetbunble.getInt("Id");
        
        //Affichage du numero de l'id
        mEditId.setText((CharSequence)String.valueOf(idFact));
        
        //Affichage de la fact full-text
        String textFact = mDetailViewController.recupererFact(idFact);
        mEditFact.setText((CharSequence) textFact );
    }
}
