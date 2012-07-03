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

import android.widget.EditText;
import android.widget.ListView;

import chucknorrisfact.controlleur.FactAdapter;
import chucknorrisfact.controlleur.MainViewController;
import chucknorrisfact.pro.R;


/**
 * Vue principale de l'application ChuckNorrisFact
 * @author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 *
 */
public class MainView extends Activity{
	
	private MainViewController mMainController; // Controlleur de la vue
	private ListView lvListe;			// Liste de fact
	private EditText mEditTextSearch;	// Edit text du filtre
	private FactAdapter mFactAdapter;	// Adapter de la liste
	
	

	
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        mMainController = new MainViewController(this);
        lvListe = (ListView)findViewById(R.id.lvListe);

        // Ajoute notre adaptateur dans notre liste
        mFactAdapter = new FactAdapter(this, getApplicationContext());
        lvListe.setAdapter(mFactAdapter);
        
        // Rend clickable la liste, en appelant la fonction OnItemClickListenerListFact
        lvListe.setClickable(true);
        lvListe.setOnItemClickListener(new OnItemClickListenerListFact(mMainController) );
		        
        // Créer un filtre de recherche
        mEditTextSearch = (EditText)findViewById(R.id.EditTextSearch);
        mEditTextSearch.addTextChangedListener( new TextWatcherSearch(lvListe, mFactAdapter) );
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