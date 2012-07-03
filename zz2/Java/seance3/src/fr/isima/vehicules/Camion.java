package fr.isima.vehicules;

public class Camion extends Vehicule
{
  float capacite;
  public Camion(String im, float cap)
  {
     immat = im;
     capacite = cap;
  }
  public final void afficher()
  {
     System.out.println("Je suis un camion d'immatriculation " + immat);
  }
  public final void avancer()
  {
     System.out.println("vroum");
  }
}