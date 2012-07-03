package chucknorrisfact.vue;
import chucknorrisfact.controlleur.MainViewController;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;

/**
 * Listener de notre liste
 * @author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 *
 */
public class OnItemClickListenerListFact implements OnItemClickListener {

	MainViewController mMainController; // Controller
	
	/**
	 * Contructeur du listener
	 * @param controller controller de la main view
	 */
	public OnItemClickListenerListFact(MainViewController controller)
	{
		mMainController = controller;
	}
	
	/**
	 * Action à effectuer après avoir cliquer sur notre liste
	 */
	public void onItemClick(AdapterView<?> a, View v, int position, long id) 
	{
		mMainController.afficherFact(position);
	}

}
