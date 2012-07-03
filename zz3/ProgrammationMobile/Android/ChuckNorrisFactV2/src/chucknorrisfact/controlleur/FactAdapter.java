/*
 * -------------------------------------------------------------------------------
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *-------------------------------------------------------------------------------"
 */

package chucknorrisfact.controlleur;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;

import chucknorrisfact.modele.Fact;
import chucknorrisfact.modele.ListFact;
import chucknorrisfact.vue.CellView;
import chucknorrisfact.vue.MainView;
import chucknorrisfact.pro.R;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.Filter;
import android.widget.Filterable;
import android.widget.TextView;

/**
 * Adapter de la liste de fact
 * @author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 */
public class FactAdapter extends BaseAdapter implements Filterable {

	private ListFact mListfact;					// Liste des facts
	private Context mContextApplication;		// Contexte de l'application
	private MainView mMainView;					// MainView
	private LayoutInflater mCellLayout;			// Layout de la cellule
    private ArrayFilter mFilter;				// Filtre de la liste
    private ArrayList<Fact> mListfactOriginal; // List de fact original

    /**
     * Constructeur de l'adapter de fact
     * @param mainView Mainview
     * @param context Context de l'application
     */
	public FactAdapter(MainView mainView, Context context) 
	{
		this.mContextApplication = context;
		this.mMainView = mainView;
		mCellLayout = LayoutInflater.from(context);
		parser(context);
	}

	/**
	 * Retourne la taille de la liste
	 */
	public int getCount() {

		return mListfact.getSize();
	}

	/**
	 * Retourne l'item à la position arg0
	 */
	public Object getItem(int arg0) {
		
		return mListfact.getAt(arg0);
	}

	/**
	 * Retourne l'id de l'item
	 */
	public long getItemId(int position) 
	{
		return position;
	}

	/**
	 * Affiche la vue de la cellule à la position position
	 */
	public View getView(int position, View convertView, ViewGroup parent) {
		
		CellView cellView;

		if(convertView == null) {
			
			cellView = new CellView();
			convertView = mCellLayout.inflate(R.layout.cellfact, null);
			cellView.setFactTitre( (TextView)convertView.findViewById(R.id.factTitre) );
			convertView.setTag(cellView);

		} else {
			cellView = (CellView) convertView.getTag();
		}

		cellView.setFactTitreText( "Fact " + mListfact.getAt(position).getId() );

		return convertView;

	}
	
	/**
	 * Permet de parser le fichier csv et remplie la liste de fact
	 */
	private void parser(Context context) {
		try {
			mListfact = ParserCSV.readFacts(mContextApplication);
		} catch (FileNotFoundException e) {
			mMainView.messageAlerte(context.getString(R.string.ressource_manquante));
		} catch (IOException e) {
			mMainView.messageAlerte(context.getString(R.string.ressource_illisible));
		}
		mListfact.sort();
	}



	/**
	 * Retourne le filtre de la liste
	 */
	public Filter getFilter() {
        if(mFilter==null)
        {
             mFilter = new ArrayFilter();
        }
        return mFilter;
	}
	
	/**
	 * Classe privée correspondant au filtre de notre liste.
	 * Filtre sur l'id de la fact
	 * @author  Maxime ESCOURBIAC Jean-Christophe SEPTIER
	 *
	 */
    private class ArrayFilter extends Filter {
    	
        @Override
        protected FilterResults performFiltering(CharSequence prefix) {
        	
        	FilterResults results = new FilterResults();
        	
        	// Synchronized pour éviter d'appeler plusieurs fois cette méthode en même temps
        	// si l'on écrit trop vite dans l'editText
        	synchronized(mListfact)
        	{
        		// Créer une liste originale de fact
				if (mListfactOriginal == null) {
	                	mListfactOriginal = mListfact.getListe();
	            }
	
				// Si la séquence a comparer est vide
	            if (prefix == null || prefix.length() == 0) {
	            		// Réinitialiser la liste
	                    //mListfact.setListe( new ArrayList<Fact>(mListfactOriginal) );
	                    results.values = mListfact.getListe();
	                    results.count = mListfact.getSize();
	            } else {
	            	// Met en minuscule notre prefix
	                String prefixString = prefix.toString().toLowerCase();
	
	                final ArrayList<Fact> values = mListfactOriginal;
	                final int count = values.size();
	
	                final ArrayList<Fact> newValues = new ArrayList<Fact>();
	
	                // Compare tout les id de fact avec notre préfix
	                for (int i = 0; i < count; i++) {
	                	
	                    final Fact value = values.get(i);
	                    final String valueText = ("Fact " + value.getId()).toLowerCase();
	                  
	                    // First match against the whole, non-splitted value
	                    if (valueText.startsWith(prefixString)) {
	                    	// Ajoute à notre nouvelle liste si la le mot commence par le prefix
	                        newValues.add(value);
	                    } else {
	                    	// Sinon, couper le mot et regarder si les autres mots correspondent à notre préfix
	                        final String[] words = valueText.split(" ");
	                        final int wordCount = words.length;
	
	                        for (int k = 0; k < wordCount; k++) {
	                            if (words[k].startsWith(prefixString)) {
	                                newValues.add(value);
	                                break;
	                            }
	                        }
	                    }
	                }
	
	                results.values = newValues;
	                results.count = newValues.size();
                }
        	}
            return results;
        }

        @SuppressWarnings("unchecked")
		@Override
        protected void publishResults(CharSequence constraint, FilterResults results) {
        	mListfact.setListe((ArrayList<Fact>) results.values);
            if (results.count > 0) {
                notifyDataSetChanged();
            } else {
                notifyDataSetInvalidated();
            }
        }
    }
}
