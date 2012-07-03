package fr.isima.vehicules;

public class Voiture extends Vehicule
{
   int couleur;
   int places;
   public Voiture(String im,int c, int p)
   {
      immat = im;
      couleur = c;
      places = p;
   }
   public final void afficher()
   {
      System.out.println("Je suis la voiture d'immatriculation " + immat);
   }
   public final void avancer()
   {
      System.out.println("vroum");
   }
}