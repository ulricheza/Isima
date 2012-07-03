
public class Program {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
        
		//Lancement sans threads
		Testwithoutthread.Withouthread();
		
		//lancement avec thread implementant l'interface
		//Testwiththread matache = new Testwiththread();
	    //(new Thread(matache)).start();
	    
	    //lancement avec thread extends thread
	    //Extendthread matache = new Extendthread();
	    //matache.start();
        Affichage.afficher();
	}

}
