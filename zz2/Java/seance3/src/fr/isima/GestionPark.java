package fr.isima;
import fr.isima.vehicules.*;




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
