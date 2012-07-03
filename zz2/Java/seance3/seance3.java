

public class seance3
{
   public static void main(String[] argv)
   {
       System.out.println(convertir("3.0"));
       System.out.println(convertir("toto"));
       divideby0();

   }

   static double convertir(String s)
   {
      double res;
      try
      {
         res = Double.parseDouble(s);
      }
      catch (NumberFormatException e)
      {
         System.out.println(e.getMessage());
         System.out.println("Erreur dans le parametre");
         res = 0.0;
      }
      return res;
   }

   static void divideby0()
   {
      int n = 10;
      int d = 0 ;
      try
      {
         System.out.println(n/d);
         System.out.println(11);
      }
      catch(ArithmeticException e)
      {
         System.out.println("Division par 0");
      }
   }
}