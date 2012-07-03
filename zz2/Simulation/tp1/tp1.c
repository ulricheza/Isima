/**
 * \file tp1.c
 * \brief Programme sur la generation de nombres pseudo-aleatoire
 * \author Maxime Escourbiac Jean-Christophe Septier
 * \version 0.1
 * \date Vendredi 24 septembre 2010
 *
 * Programme de generation de nombres pseudo-aleatoire
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define VAR_START 1234
#define JET_MAX 100

/**
 *\fn float von_neumann()
 *\brief implementation d'un generateur de type elevation au carre sur 4 digit
 *\return la valeur aléatoire tire
 *
 */
float von_neumann()
{
   static int x = VAR_START; /*pour garder en memoire la derniere valeur*/
   x*=x;
   x /= 100;
   x %= 10000;
   return((float)x/(float)10000);
}

/**
 *\fn int congruentiel()
 *\brief Implementation de la technique dite congruentielle lineaire
 *\return la valeur aléatoire tire
 *
 */

int congruentiel(int a, int c, int m)
{
   static unsigned int x=VAR_START;
   x=(a*x+c)%m;
   return(x);
}

/**
 *\fn unsigned char fibo_4_lfsr()
 *\brief Implementation de la methode 4-bit Fibonacci LFSR vue en exemple en cours 
 *\return la valeur aléatoire tire
 *
 * Cette implementation a juste un but pedagogique il n'est nullement efficace,
 * on peut l'ameliorer en augmentant le nombre de bit utilise et en compliquant l'equation
 * logique la caracterisant 
 */

unsigned char fibo_4_lfsr()
{
  static unsigned char x = VAR_START%16; /*unsigned car sinon probleme avec valeur standard*/
  unsigned char bit;
  bit = ( x ^ (x >> 1)) & 1;
  x = (( x >> 1) | (bit << 3)) & 15;
  return x;
}

/**
 *\fn int brassage()
 *\brief Implementation de la technique dite de brassage de generateur
 *\return la valeur aléatoire tire
 * ici on va utiliser 2 generateurs differents la fonction rand implemente sur linux
 * et la methode congruentielle implemente dans ce tp;
 */

int brassage()
{
   static int tab[100];
   static int init = 1;	
   int a,i,val;
   if(init)
   {
      for(i=0;i<100;i++)
         tab[i] = congruentiel(16807, 0, 2147483647);
      
      srand(time(0));
      init = 0;
   }
   a = rand()%100;
   val = tab[a];
   tab[a] = congruentiel(16807, 0, 2147483647);
   return val;
}

/**
 *\fn void test_equiprobalite()
 *\brief test d'equiprobalite sur la methode congruentielle avec les parametres standards
 *
 */

void test_equiprobalite()
{
   int i,j;
   int * tab;
   float val;
   tab = (int *)calloc(10,sizeof(int));
   if(tab)
   {
      for(i=0;i<100000;i++)
      {
         j=congruentiel(16807, 0, 2147483647);
         val =(float)j/(float)2147483647;
         j = (int)10*val;
         tab[j]++;
      }
      printf("affichage des resultat \n");
      for(i=0;i<10;i++)
         printf("pourcentage des valeurs entre %1.1f et %1.1f :: %f\n",(float)i/10.0,(float)(i+1)/10.0,(float)tab[i]/1000.0);
   }
}

int main(int argc, char * argv[])
{
  int i,val;
  unsigned char x;
  float n;
  
  /*test de la fonction de Von Neumann*/
  
  for(i=0;i<JET_MAX;i++)
  {
    n = von_neumann();
    printf("iter %d n= %0.4f\n",i,n);
  }
  */
  
  /*test de la methode congruentielle lineaire*/
  
  for(i=0;i<JET_MAX;i++)
  {
     val = congruentiel(16807, 0, 2147483647);
     printf("iter %d val = %d \n",i,val);
  }
  
  /*test de la fonction de generation de fibonacci LFSR sur bit*/ 
  for(i=0;i<16;i++)
  {
     x = fibo_4_lfsr();
     printf(" iter %d x=%d \n",i,x);
  }
  
  
  /*test de la fonction de brassage de generateur*/
  for(i=0;i<JET_MAX;i++)
  {
     val = brassage();
     printf("i = %d, val = %d \n",i,val);
  }
  
  test_equiprobalite();
  
  return(EXIT_SUCCESS);
}
