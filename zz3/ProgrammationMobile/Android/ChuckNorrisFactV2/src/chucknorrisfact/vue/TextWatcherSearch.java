package chucknorrisfact.vue;

import chucknorrisfact.controlleur.FactAdapter;
import android.text.Editable;
import android.text.TextWatcher;
import android.widget.ListView;

/**
 * TextWatcher associé à notre edit text de filtre
 * @author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 *
 */
public class TextWatcherSearch implements TextWatcher {

	
	ListView mLv;			// ListeView de fact
	FactAdapter mAdapt;		// Adapter de fact
	
	/**
	 * Constructeur
	 * @param lv ListeView de fact
	 * @param adapt Adapter de fact
	 */
	public TextWatcherSearch(ListView lv, FactAdapter adapt )
	{
		mLv = lv;
		mAdapt = adapt;
	}
	
	public void afterTextChanged(Editable s) {
		// TODO Auto-generated method stub

	}

	public void beforeTextChanged(CharSequence s, int start, int count,
			int after) {
		// TODO Auto-generated method stub

	}

	/**
	 * Appelé quand on modifie le texte
	 */
    public void onTextChanged(CharSequence s, int start, int before, int count) 
    { 
    	// Applique le filtre sur notre adapter
    	mAdapt.getFilter().filter(s);

    	mAdapt.notifyDataSetInvalidated();
    	mAdapt.notifyDataSetChanged();   
    	mLv.setAdapter(mAdapt);
    }

}
