/**
 *\file affich_fonction.c
 *\brief Graphismes 3D sous X-Windows
 *\author Maxime ESCOURBIAC
 *\version 0.1
 *\date 13 decembre 2009
 *
 *Affichage des fonctions vue lors du tp "calculatrice" a l'aide de Xlib
 *Dans ce cas la on effectuera le trace point par point
 *
 */

/*declarations de bibliotheque */

#include <stdio.h>
#include <X11/Xlib.h>
#include <string.h>
#include "calcul.h"



/* ------- Declaration de variables globales ---------------------------- */

/*------------------------------Pour Xlib---------------------------------*/

   Bool           sortie = False; /* Indicateur de fin de pgm             */

   Window         root;           /* Fenetre racine (fond de l'ecran)     */
   Window         win;            /* Fenetre de travail                   */
   Window         subwin;         /* Sous fenetre                         */
   Display       *dpy;            /* Serveur de fenetrage de ce pgm       */
   
   int            ecran;          /* Declaration de l'ecran par defaut    */
   
   unsigned long  wpx,            /* Variables temporaires pour la        */
                  bpx;            /* Couleur whithe et black (fg, bg)     */

   XEvent         ev;             /* Dï¿½clare une variable evenement       */
   unsigned long  mask;           /* Declare un mask d'evenement          */

   GC             gcontext;         
   XGCValues      gcv;               
   unsigned long  gcmask;             

   Cursor	  curseur;        /* Definition d'un curseur souris       */

/* --------------------Pour le programme en lui meme--------------------- */



/*declarations des fonctions*/

void affich(char * expr, int * tab, int choix);


int main (int argc, char * argv[])
{
   char expr[50];
   double xmax,ymax;
   int x,y;
   int tab[400] = {0};
   int choix;

   /*partie pour l'evaluation de la fonction*/
   printf("-------------------------------\n");
   printf("1°) lignes                     \n");
   printf("2°) points                     \n");
   printf("-------------------------------\n");
   scanf("%d",&choix);
   getc(stdin);

   printf("Veuillez rentrer les tailles max de votre fenetre xmax,ymax \n");
   scanf("%lf %lf",&xmax,&ymax);
   getc(stdin);
   printf("Veuillez rentrer l'expression desire\n");
   fgets(expr,49,stdin);
   
   calcul(expr,xmax,ymax,tab);


   dpy = XOpenDisplay(0);
   if(!dpy)
   {
      printf("souci Ã  l'ouverture de la fenetre \n");
      exit(EXIT_FAILURE);
   }
   
   ecran = DefaultScreen(dpy);
   root  = DefaultRootWindow(dpy);

  /* ------- Recup. couleur de l'avant plan et arriere plan ------------ */
   
   bpx      = BlackPixel(dpy,ecran);
   wpx      = WhitePixel(dpy,ecran);
   
  
   /* ------- Creation de la fenetre: Epaiss 6 pixels, L 400 H 400 ------ */
   win = XCreateSimpleWindow(dpy,root,0,0,400,400,6,wpx,bpx);

  
   XStoreName(dpy,win,"TP 7: Graphisme 3D sous X-Windows");
   
   /* ------- Definition des evenements qui les concernent -------------- */

   XSelectInput(dpy,win,ButtonPressMask |
                        ButtonReleaseMask |
                        Button1MotionMask |
                        KeyPressMask |
                        ExposureMask );

   /*---------------------------------------------------------------------*/ 
  
   XMapWindow(dpy,win);
   
  /* ------- Creation des contextes standards -------------------------- */
   
   gcv.foreground = wpx;               /* Contexte standard         */
   gcv.background = bpx;
   gcv.line_width = 1;
   gcv.function   = GXcopy;
   gcmask = GCForeground | GCBackground | GCLineWidth | GCFunction;
   gcontext = XCreateGC(dpy,win,gcmask,&gcv);

  /* ------------------------------------------------------------------- */
   
   while(!sortie)
   {                                             
      XNextEvent(dpy,&ev);
      switch(ev.type)
      {
         case Expose : affich(expr,tab,choix);
                       break;

         case KeyPress : sortie = 1;
                         break;


      }
    }
 
   XCloseDisplay(dpy);
   
   return(EXIT_SUCCESS);
} 
   

/**
 *\fn void affich(char * expr , int * tab)
 *\brief contient toutes les manipulations d'affichage
 *
 *\param expr
 *\param tab
 *\param choix
 *\return 
 */

void affich(char * expr, int * tab, int choix)
{
   int i;
   /*affichage des axes*/
   XDrawLine(dpy,win,gcontext,0,199,399,199);
   XDrawLine(dpy,win,gcontext,199,0,199,399);
   
   /*affichage du nom de la fonction*/
   XDrawString(dpy,win,gcontext,0,10,expr,strlen(expr)-1);
   
   /*affichage point par point*/
   if(choix == 1)
   {
      for(i=0;i<399;i++)
      {
         if(tab[i] > 0 && tab[i] < 399 && tab[i+1] > 0 && tab[i+1] < 399)
            XDrawLine(dpy,win,gcontext,i,tab[i],i+1,tab[i+1]);
      }
   }
   else
   {
      for(i=0;i<400;i++)
      {
         if(tab[i] > 0 && tab[i] < 399)
            XDrawPoint(dpy,win,gcontext,i,tab[i]);
      }
   }
}



