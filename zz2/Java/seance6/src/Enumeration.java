
public class Enumeration {
	
	private enum Jour { LUNDI,MARDI,MERCREDI,JEUDI,VENDREDI,SAMEDI,DIMANCHE};
	
	public void afficher()
	{
		for(Jour jour: Jour.values())
		{
			System.out.println(jour);
		}
	}
}
