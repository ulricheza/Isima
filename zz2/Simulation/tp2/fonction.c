/**
 * \file fonction.c
 * \brief Generation de nombres pseudo aleatoires suivant differentes
ditributions
 * \author Maxime Escourbiac Jean-Christophe Septier
 * \version 0.1
 * \date Jeudi 7 octobre 2010
 *
 * Tp2 de simulation
 *
 */

#include "fonction.h"

float gene_rand()
{
  return((float)(rand()%1001) / 1000.0);
}

int infini(double value)
{
   return(value == value);
}
int * test_histogramme_ABC()
{
  int i;
  float val;
  int * tab;
  tab = (int *) calloc(3,sizeof(int));
  if(!tab)
  {
     fprintf(stderr,"erreur alloc tab \n");
     exit(EXIT_FAILURE);
  }
  
  for(i=0;i<1000;i++)
  {
     val= gene_rand();
     if(val > 0.6)
        ++tab[2];
     else 
     {
        if(val > 0.5)
           ++tab[1];
        else
           ++tab[0];
     }
  }
  return tab;
}

int * loi_uniforme(double a, double b)
{
  /*dans cet exemple on prendra des intervalles de 1                            
               */
  /*pour des questions de lisibilité du tableau, on testera que pour valeurs de
a et b entieres */
  int i;
  int * tab;
  float val;

  tab = (int *) calloc((int)b - (int)a,sizeof(int));
  if(!tab)
  {
     fprintf(stderr,"erreur alloc tab \n");
     exit(EXIT_FAILURE);
  }
  for(i=0;i<1000;++i)
  {
     val = a+(b-a)*gene_rand(); 
     tab[(int)(val-a)]++;
  }
  return tab;
}

int * loi_exponentielle_neg(double moyenne,double max)
{
   int i;
   int * tab;
   double val,moy = 0.0;

   tab = (int *) calloc((int)max,sizeof(int));
   if(!tab)
   {
      fprintf(stderr,"erreur alloc tab \n");
      exit(EXIT_FAILURE);
   }
   for(i=0;i<1000;++i)
   {
      do
      {
         val = -moyenne*log(1.0 - gene_rand());
      }while(isinf(val)); /*en cas si gene_rand = 1.0 => ln(0) indefini*/
      /*par contre isinf n'est pas une fonction ANSI C*/
      
      moy += val;
      if(val<max)
         tab[(int)(val)]++;   
   }
   moy /= 1000.0;
   
   fprintf(stdout,"Moyenne reelle = %f \n",moy);
   
   return tab;
}

int * loi_normale(double moyenne, double ecart_type, double min, double max)
{
   int i;
   int * tab;
   double x,y,u1,u2,moy=0.0,ecart=0.0;
   double tab_ecart[1000];

   tab = (int *) calloc((int)max-(int)min,sizeof(int));
   if(!tab)
   {
      fprintf(stderr,"erreur alloc tab \n");
      exit(EXIT_FAILURE);
   }   
   for(i=0;i<500;++i) /*500 car chaque iteration produit 2 tirages*/
   {
      /*generation des deux valeurs entre 0 et 1 */
      u1 = gene_rand();
      do
      {
         u2 = log(gene_rand());
      }while(isinf(u2));
      /*log(x) peut avoir un comportement indefini si u2 tend vers 0     */
      /*donc on teste la valeur tiree si elle est pas "egale" a l'infini */
      
      /*calcul des 2 tirages*/
      x = cos(2*PI*u1)*sqrt(-2.0*u2);
      y = sin(2*PI*u1)*sqrt(-2.0*u2);
      x = moyenne + ecart_type*x;
      y = moyenne + ecart_type*y;
      
      moy += x + y;
      tab_ecart[2*i] = x;
      tab_ecart[2*i+1] = y;
      
      if(x<max && x>min)
         tab[(int)x -(int)min]++;
      if(y<max && y>min)
         tab[(int)y -(int)min]++;
   }
   /*calcul de moyenne*/
   moy /= 1000,0;
   
   /*calcul de l'ecart type*/
   for(i=0;i<1000;++i)
      ecart += (tab_ecart[i] - moy)*(tab_ecart[i] - moy);
   ecart /= 1000.0;
   ecart = sqrt(ecart);
   
   fprintf(stdout,"Moyenne reelle = %f \n",moy);
   fprintf(stdout,"Ecart-type reel = %f \n",ecart);
   return tab;
}

int gene_nombre_AB(int min,int max)
{
    return(rand()%(max-min+1) +  min);
}

int * histogramme_gene(int * data,int size, int effectif)
{
    int i,j,*tab;
    float *histo,alea,cumul = 0.0;
    
    tab = (int *) calloc(size,sizeof(int));
    histo = (float *) calloc(size,sizeof(float));
    
    if(!tab || !histo)
    {
        fprintf(stderr,"erreur allocation tableau \n");
        exit(EXIT_FAILURE);
    }
    
    /*creation du tableau de repartition*/
    for(i=0;i<size;++i)
    {
       cumul += (float)data[i] / (float)effectif;
       histo[i] = cumul;
    }
     
    /*simulation avec le genrateur rand*/
    for(i=0;i<1000;++i)
    {
        alea = gene_rand();
        j = 0;
        while(j<size && alea > histo[j])
        {
            ++j;
        }
        if(j==size)
           tab[size-1]++;
        else
           tab[j]++;
    }
    
    free(histo);
    return tab;
}

int * loi_normale_rejection(double moyenne, double ecart_type, double minX, double maxX)
{
   double maxY,Na1,Na2,x,y,moy,ecart=0.0,tab_ecart[1000];
   int * tab,i,nbre_tir = 0, nbre_essai = 0;
   
   tab = (int *) calloc((int)maxX-(int)minX,sizeof(int));
   if(!tab)
   {
      fprintf(stderr,"erreur alloc tab \n");
      exit(EXIT_FAILURE);
   }   
   
   /*ecart_type = sqrt(ecart_type);*/
   
   /*calcul de la norme sup de la distribution*/
   maxY = 1.0/(ecart_type*sqrt(2.0*PI));
   
   while(nbre_tir<1000)
   {
      Na1 = gene_rand();
      Na2 = gene_rand();
         
      x = minX + Na1 * (maxX - minX);
      y = maxY * Na2;
      
      if(maxY*exp(-0.5*((x-moyenne)/ecart_type)*((x-moyenne)/ecart_type)) > y)
      {
         tab[(int)x - (int)minX]++;
         tab_ecart[nbre_tir] = x;
         moy += x;
         nbre_tir++;
      }
      nbre_essai++;
   }
   
   /*calcul de moyenne*/
   moy /= 1000,0;
   
   /*calcul de l'ecart type*/
   for(i=0;i<1000;++i)
      ecart += (tab_ecart[i] - moy)*(tab_ecart[i] - moy);
   ecart /= 1000.0;
   ecart = sqrt(ecart);
   
   fprintf(stdout,"Moyenne reelle = %f \n",moy);
   fprintf(stdout,"Ecart-type reel = %f \n",ecart);
   return tab;
}
         
   
