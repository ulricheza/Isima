package groovyci;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Date;
import java.util.logging.FileHandler;
import java.util.logging.Handler;
import java.util.logging.Logger;
import java.util.logging.XMLFormatter;

import javax.script.*;

/**
 * Classe qui permet d'executer un script groovy 
 * @author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 * @version 1.0
 * 
 */
public class Builder implements Runnable {
	
	private ScriptEngine engine; //moteur de lancement du script
	private String file;         //string representant le fichier a executer
	private Logger logger;       //Journal de log (specifique a chaque script)
	private String name;         //Nom a utiliser pour les log
	private Object returnValue;  //Sauvegarde la derniere valeur(utile pour les test)
	
	/**
	 * Getter de returnValue
	 * @return retourne la derniere valeur obtenue
	 */
	public Object getReturnValue()
	{
		return this.returnValue;
	}
	
	/**
	 * Constructeur du builder
	 * La separation des journaux est voulue pour que la gestion des resultats puissent
	 * etre independantes entre chaque script
	 * @param file nom du fichier a executer
	 * @throws SecurityException  erreur lors de la creation du fichier de log
	 * @throws IOException erreur lors de la creation du fichier de log
	 */
	public Builder(String file) throws SecurityException, IOException
	{
		returnValue = null;
		this.file = file;
		ScriptEngineManager factory = new ScriptEngineManager();
		this.engine = factory.getEngineByName("groovy");
		
		
		//on recupere un nom potable du script
		String[] mess = file.split("/");
		this.name = mess[mess.length - 1]; 
		
		this.logger = Logger.getLogger("Journal" + name);
		this.logger.setUseParentHandlers(false);         //desactive les handlers des parents
		
		Handler fh = new FileHandler("./log/"+ name + ".log",true);//on efface pas les logs precedents
	    fh.setFormatter(new XMLFormatter());                       //on passe en XML pour une reutilisabilite
		logger.addHandler(fh);
        logger.info("Session du " + new Date().toString());
        if(engine == null)
        {
        	System.out.println("ERREUR CRITIQUE: Groovy non installe!!!");
        	logger.severe("CRITICAL ERROR: Groovy non installe!!!");
        }
	}

	/**
	 * Methode d'execution du script groovy 
	 * Implemente l'interface Runnable
	 * Stocke le resultat dans returnValue
	 * @author Maxime ESCOURBIAC Jean-Christophe SEPTIER
	 * @version 1.0
	 *
	 */
	@Override
	public void run() {
		try 
		{
			System.out.println(name + " Debut du build: " + new Date().toString());
			logger.info("Debut du build: " + new Date().toString());
			FileReader reader = new FileReader(file);
			returnValue = engine.eval(reader);
			System.out.println(name + " Valeur retournee: " + returnValue);
			logger.info("Valeur retournee " + returnValue);
		} 
		catch (FileNotFoundException e) 
		{
			returnValue = "Erreur fichier script non trouve";
			System.out.println(name + " Erreur fichier script non trouve");
			logger.severe("Erreur fichier script non trouve");
		}
		catch (ScriptException e)
		{
			returnValue = "Erreur a l'execution du script";
			System.out.println(name + " Erreur a l'execution du script");
			logger.severe("Erreur a l'execution du script");
		}
		finally
		{
			System.out.println(name + " Fin du build:" + new Date().toString());
			logger.info("Fin du build: " + new Date().toString());
		}
	}
}
