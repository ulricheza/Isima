

public class GestionPark {

   public static void main(String[] argv)
   {
      Voiture v = new Voiture("1234XX56",2,5);
      Camion  c = new Camion("7894YY81",100.4f);
      v.afficher();
      v.avancer();
      c.afficher();
      c.avancer();
   }
}

abstract class Vehicule
{
   String immat;
   abstract void afficher();
   abstract void avancer();
}

class Voiture extends Vehicule
{
   int couleur;
   int places;
   Voiture(String im,int c, int p)
   {
      immat = im;
      couleur = c;
      places = p;
   }
   final void afficher()
   {
      System.out.println("Je suis la voiture d'immatriculation " + immat);
   }
   final void avancer()
   {
      System.out.println("vroum");
   }
}

class Camion extends Vehicule
{
  float capacite;
  Camion(String im, float cap)
  {
     immat = im;
     capacite = cap;
  }
  final void afficher()
  {
     System.out.println("Je suis un camion d'immatriculation " + immat);
  }
  final void avancer()
  {
     System.out.println("vroum");
  }
}
