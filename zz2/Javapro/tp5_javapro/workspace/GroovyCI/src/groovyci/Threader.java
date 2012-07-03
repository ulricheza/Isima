package groovyci;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Date;
import java.util.Properties;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;
import java.util.logging.FileHandler;
import java.util.logging.Handler;
import java.util.logging.Logger;
import java.util.logging.XMLFormatter;

//Cette classe permet de lancer 3 instances de builder simultanement

/**
 * Classe permettant de lancer plusieurs scripts en parallele
 * @author Maxime Escourbiac Jean-Christophe Septier
 * @version 1.0 
 */
public class Threader {
	
	private int concurrentExecutionNumber;
	private Logger logger;
    
    /**
     * Constructeur de la classe Threader
     * Charche un fichier de proprietes
     * @author Maxime Escourbiac Jean-Christophe Septier
     * @version 1.0 
     * @throws IOException 
     * @throws SecurityException 
     */
	public Threader() throws SecurityException, IOException
	{
		this.logger = Logger.getLogger("Threader");
		this.logger.setUseParentHandlers(false);         //desactive les handlers des parents
		
		Handler fh = new FileHandler("log/threader.log",true);//on efface pas les logs precedents
	    fh.setFormatter(new XMLFormatter());              //on passe en XML pour une reutilisabilite
		logger.addHandler(fh);
        logger.info("Session du " + new Date().toString());
        
		Properties prop = new Properties();
		try
		{
			FileInputStream stream = new FileInputStream("./ressources/properties.txt");
		    try 
		    {
				prop.load(stream);
				try
				{
					this.concurrentExecutionNumber = Integer.parseInt(prop.getProperty("concurrentExecutionNumber"));
				}
				catch (NumberFormatException e)
				{
					logger.warning("Le fichier de config est fausse, la valeur par default 3 sera prise");
					System.out.println("Warning: Le fichier de config est fausse, la valeur par default 3 sera prise");
					this.concurrentExecutionNumber = 3;
				}
		    } 
		    catch (IOException e) 
		    {
		    	logger.warning("Le fichier est corrompu ou impossible a lire, la valeur par default 3 sera prise");
				System.out.println("Warning: Le fichier est corrompu ou impossible a lire, la valeur par default 3 sera prise");
				this.concurrentExecutionNumber = 3;
			}
		} 
		catch (FileNotFoundException e) 
		{
			logger.warning("Le fichier est inexistant, la valeur par defaut 3 sera prise");
			System.out.println("Warning: Le fichier est inexistant, la valeur par defaut 3 sera prise");
			this.concurrentExecutionNumber = 3;
		}
	}
	
	/**
	 * Methode qui lance plusieurs scripts Groovy en boucle
	 * @param files scripts Groovy a executer
	 * @param intervals intervalle en minute entre chaque execution du script
	 * @return
	 */
	public boolean launch(String[] files , int[] intervals)
	{
		boolean result = true;
		Builder[] build = new Builder[files.length];
		ScheduledExecutorService scheduler = Executors.newScheduledThreadPool(concurrentExecutionNumber);
		try
		{
			for(int i = 0 ; i < files.length; ++i)
			{
				build[i] = new Builder(files[i]);
				scheduler.scheduleWithFixedDelay(build[i], 0 , intervals[i], TimeUnit.SECONDS);
			}
		}
		catch (SecurityException e)
		{
			logger.severe("Erreur dans la creation du journal d'un des Builder : SecurityException");
			System.out.println("Threader:Erreur dans la creation du journal d'un des Builder : SecurityException");
			return false;
		}
		catch (IOException e)
		{
			logger.severe("Erreur dans la creation du journal d'un des Builder : IOException");
			System.out.println("Threader:Erreur dans la creation du journal d'un des Builder : IOException");
			return false;
		}
		return result;
	}
}
