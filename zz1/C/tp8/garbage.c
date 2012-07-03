
/**
 * \file garbage.c
 * \brief Programme de garbage collector utilise lors du partiel
 * \author Maxime Escourbiac
 * \version 0.1
 * \date Mardi 12 janvier 2010
 *
 * Programme qui gere dynamiquement la memoire
 *
 */

#include"garbage.h"

/*initialisation du tableau de pointeur generique*/

void ** gPool = NULL;
int gPoolIndex = 0;
int gPoolMax = 5;  /*5 pour limiter la saisie d'agenda =) */

/**
 *\fn creeGC()
 *\brief fonction d'initialisation du tableau de pointeur generique
 *
*/

void creerGC()
{
   if(gPool == NULL)
   {
      gPool = (void **)calloc(gPoolMax, sizeof(void *));
   }
   else
      printf("initialisation deja realise \n");

}

/**
 *\fn gc()
 *\brief fonction de liberation de tous les elements du tableau de pointeur
 *
 */

void gc()
{
   int i;
   for(i=0;i<gPoolMax;i++)
   {
      free(gPool[i]);
      gPool[i] = NULL;
   }
   gPoolIndex = 0;
} 

/**
 *\fn detruireGC()
 *\brief liberation totale du tableau de pointeur
 *
 */
void detruireGC()
{
   gc();
   free(gPool);
   gPool = NULL;
   gPoolIndex = 0;
}

/**
 *\fn void * allouer (int taille)
 *\brief fonction d'allocation d'un element du tableau de pointeur generique
 *\param taille taille en octect de l'element a allouer
 *\return point: pointeur sur la zone alloue sinon null
 *
 */

void * allouer (unsigned int taille)
{
   void * temp = NULL;
   void ** ptemp;
   if(gPoolIndex == gPoolMax)  /*tentative d'agrandissement du tableau*/
   {
       printf("reallocation en cours \n");
       ptemp = (void **)realloc(gPool,(gPoolMax + gPoolMax/4)*sizeof(void*));
       if(ptemp == NULL)
       {
          fprintf(stderr,"tableau plein\n");
          exit(EXIT_FAILURE);
       }
       gPool = ptemp;
       gPoolMax = gPoolMax + gPoolMax/4;
       printf("reallocation effectue avec succes \n");
   }
   if(gPool!=NULL && taille != 0 )
   {
      temp=(void*)malloc(taille);
      if(temp == NULL)
      {
         printf("probleme d'allocation\n");
         exit(EXIT_FAILURE);
      }
      gPool[gPoolIndex]= temp;
      gPoolIndex++;
   }
   return (temp);
}

/**
 *\fn void * reallouer (void * ptr ,int taille)
 *\brief fonction de reallocation d'un element du tableau de pointeur generique
 *\param taille taille en octect de l'element a reallouer
 *\param ptr    pointeur que l'on veut reallouer
 *\return point: pointeur sur la zone alloue sinon null
 *
 */
void * reallouer (void * ptr ,unsigned int taille)
{
   int i=0;
   void * temp = NULL;
   if(gPool != NULL)
   {
      while(i<gPoolMax && ptr!=gPool[i])
         i++;
      if(i == gPoolMax)
         printf("pointeur non trouve \n");
      else
      {
         temp = realloc(gPool[i],taille);
         if(temp != NULL)
           gPool[i]=temp;
      }
   }
   return temp;
}



