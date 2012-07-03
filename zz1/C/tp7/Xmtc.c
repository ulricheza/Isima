/* ---------------------------------------------------------------------- */
/* Xmtc.c   Calcul de PI avec ma methode de Monte Carlo (Simul aleatoire) */
/*                                                                        */
/* Cette methode tres puissante n'est pas adapt‚e au calcul de PI mais il */
/* reste interesant de voir que l'on peut approcher PI avec des nombres   */
/* aleatoires.                                                            */
/* ---------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <X11/Xlib.h>

/* ---------------------------------------------------------------------- */

#define  MAXX  600 
#define  MAXY  600 

/* ---------------------------------------------------------------------- */

void afficheGraphisme();

/* ------- Declaration de variables globales ---------------------------- */


   Bool           sortie = False; /* Indicateur de fin de pgm             */

   Window         root;           /* Fenetre racine (fond de l'ecran)     */
   Window         win;            /* Fenetre de travail                   */
   Window         subwin;         /* Sous fenetre                         */
   Display       *dpy;            /* Serveur de fenetrage de ce pgm       */
   
   int            ecran;          /* Declaration de l'ecran par defaut    */
   
   unsigned long  wpx,            /* Variables temporaires pour la        */
                  bpx;            /* Couleur whithe et black (fg, bg)     */

   XEvent         ev;             /* Déclare une variable evenement       */
   unsigned long  mask;           /* Declare un mask d'evenement          */

   GC             gcontext;         
   XGCValues      gcv;               
   unsigned long  gcmask;             

   Cursor	  curseur;        /* Definition d'un curseur souris       */

/* ---------------------------------------------------------------------- */

void main(int argc, char *argv[])
{
   dpy = XOpenDisplay(0);         /* Connexion du serveur, il faudra      */
                                  /* tester le resultat                   */
                                     
   ecran    = DefaultScreen(dpy);
   root     = DefaultRootWindow(dpy);
   
   /* ------- Recup. couleur de l'avant plan et arriere plan ------------ */
   
   bpx      = BlackPixel(dpy,ecran);
   wpx      = WhitePixel(dpy,ecran);
   
   /* ------- Creation de la fenetre: Epaiss 6 pixels, L 600 H 600 ------ */
   
   win = XCreateSimpleWindow(dpy,root,0,0,MAXX,MAXY,6,wpx,bpx);

   XStoreName(dpy,win,"Approximation de PI en simulation aleatoire");

   /* ------- Definition des evenements qui les concernent -------------- */

   XSelectInput(dpy,win, ExposureMask );
                        
   /* ------------------------------------------------------------------- */

   XMapWindow(dpy,win);                      /* Affiche la fenetres       */




   /* ------- Creation des contextes standards -------------------------- */
   
   gcv.foreground = wpx;                     /* Contexte standard         */
   gcv.background = bpx;
   gcv.line_width = 3;
   gcv.function   = GXcopy;
   gcmask         = GCForeground | GCBackground | GCLineWidth | GCFunction;
   gcontext       = XCreateGC(dpy,win,gcmask,&gcv);


   /* ------------------------------------------------------------------- */
                         
   while(!sortie)
   {                                             
      XNextEvent(dpy,&ev);
      switch(ev.type)
      {
         case Expose      : afficheGraphisme();
                            break;
      }
   }
   XCloseDisplay(dpy);
}
 
/* ---------------------------------------------------------------------- */
/* afficheGraphisme         Test de primitives graphiques                 */
/* ---------------------------------------------------------------------- */

void afficheGraphisme()
{                 
   #define      MAX      500000
   #define      MAXXF    599.
   #define      MAXYF    599.
                 
   static int   numcur   = 0;
   Font         police;
   long         i, cumul = 0; 
   double       x,y,pi;              
   int          px,py;

   srand(1);
   XDrawArc(dpy,win,gcontext,0,0,MAXX-1,MAXY-1,0,360*64);
   for( i = 0; i < MAX ; i++)
   {
      x = (double) rand() / (double) RAND_MAX;
      y = (double) rand() / (double) RAND_MAX;
      if (((x-1)*(x-1) + (y-1)*(y-1)) <= 1) cumul++;
      px = (int) (x * MAXXF);
      py = (int) (y * MAXYF);
      XDrawPoint(dpy,win,gcontext,px,py);
   }
   pi = ((double) cumul * 4. / MAX);
   printf("%d points, Approx de PI = %f, Approx Err : %f\n",
          MAX, pi, 3.14159 - pi); 
   exit(1);

}

/* ---------------------------------------------------------------------- */

