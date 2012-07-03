public class Program {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stu
		int i;
		for(i = 0; i < args.length ; ++i) //ancienne facon
			System.out.println(args[i]);
		
		for(String arg:args)  //nouvelle version
		{
			System.out.println(arg);
		}
		
		GenericClass<Integer> maClassGene = new GenericClass<Integer>();
		maClassGene.add(0,1,2,3,4,5);
		
		Enumeration jour = new Enumeration();
		jour.afficher();
		
		ClavierReader lect = new ClavierReader();
		lect.LireEtAfficher();
		lect.LireEtEcrireFichier();
	}

}
