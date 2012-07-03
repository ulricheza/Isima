package groovyci;

import java.io.IOException;



public class Program {

	/**
	 * Main du GroovyContinousIntegration
	 * @param args se compose de la forme nom_du_script intervalle_du_script
	 * @author Maxime Escourbiac Jean-Christophe Septier
	 * @version 1.0
	 */
	public static void main(String[] args)
	{
		String[] files = new String[args.length/2];
		int[] intervals = new int[args.length/2];
		
		try
		{
			for(int i = 0 ; i < args.length/2; ++i)
			{
				files[i] = args[2*i];
				intervals[i] = Integer.parseInt(args[2*i + 1]);
			
			}
		}
		catch(NumberFormatException e)
		{
			System.out.println("Erreur dans les parametres");
			System.exit(-1);
		}
		
		Threader launcher = null;
		try
		{
			launcher = new Threader();
			if(launcher.launch(files, intervals) == false)
			{
				System.exit(-1);
			}
		}
		catch (SecurityException e)
		{
			System.out.println("Erreur dans la creation du journal du Threader : SecurityException");
			System.exit(-1);
		}
		catch (IOException e)
		{
			System.out.println("Erreur dans la creation du journal du Threader : IOException");
			System.exit(-1);
		}
	}
}
