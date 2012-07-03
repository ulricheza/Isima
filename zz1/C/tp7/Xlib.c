/* ---------------------------------------------------------------------- */
/* Xline.c       Affichage de lignes avec gestion de la souris            */
/* ---------------------------------------------------------------------- */

#include <X11/Xlib.h>
#include <string.h>

/* ---------------------------------------------------------------------- */

void afficheGraphisme();
void saisie();

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

void main()
{
   dpy = XOpenDisplay(0);         /* Connexion du serveur, il faudra      */
                                  /* tester le resultat                   */
                                     
   ecran    = DefaultScreen(dpy);
   root     = DefaultRootWindow(dpy);
   
   /* ------- Recup. couleur de l'avant plan et arriere plan ------------ */
   
   bpx      = BlackPixel(dpy,ecran);
   wpx      = WhitePixel(dpy,ecran);
   
   /* ------- Creation de la fenetre: Epaiss 6 pixels, L 500 H 300 ------ */
   
   win = XCreateSimpleWindow(dpy,root,30,40,600,500,6,wpx,bpx);
   

   XStoreName(dpy,win,"ISIMA 1: Utilisation de la Xlib");

   /* ------- Definition des evenements qui les concernent -------------- */

   XSelectInput(dpy,win,ButtonPressMask |
                        ButtonReleaseMask |
                        Button1MotionMask |
                        KeyPressMask |
                        ExposureMask );

   /* ------------------------------------------------------------------- */

   XMapWindow(dpy,win);                      /* Affiche la fenetres       */


   /* ------- Creation des contextes standards -------------------------- */
   
   gcv.foreground = wpx;               /* Contexte standard         */
   gcv.background = bpx;
   gcv.line_width = 3;
   gcv.function   = GXcopy;
   gcmask = GCForeground | GCBackground | GCLineWidth | GCFunction;
   gcontext = XCreateGC(dpy,win,gcmask,&gcv);



   /* ------------------------------------------------------------------- */
                         

   while(!sortie)
   {                                             
      XNextEvent(dpy,&ev);
      switch(ev.type)
      {
         case Expose      : afficheGraphisme();
                            break;
         case KeyPress    : saisie();
                            break;
         case ButtonPress :       
         default          : puts("Evenement Inconnu !");
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
   char         chaine[] ="Texte sur ecran graphique";
   static int   numcur = 80;
   Font         police;

   XDrawLine(dpy,win,gcontext,10,10,200,200);
   XDrawRectangle(dpy,win,gcontext,50,80,200,100);
   XFillRectangle(dpy,win,gcontext,150,380,100,30);
   XDrawArc(dpy,win,gcontext,350,350,50,50,0,360*64);
   XFillArc(dpy,win,gcontext,200,250,80,80,30*64,330*64);  

   /* --------- Modes: ArcPieSlice (defaut) ou ArcChord --------------- */
      
   XSetArcMode(dpy,gcontext,ArcChord);  
   XFillArc(dpy,win,gcontext,100,450,100,50,90*64,270*64);  
                            
   /* --------- Affichage de Texte puis changement de Police ---------- */

   XDrawString(dpy,win,gcontext,80,20,chaine,strlen(chaine));

   strcpy(chaine,"Hajimemashite");
   XDrawString(dpy,win,gcontext,80,40,chaine,strlen(chaine));

   
   /* --------- Changement du Curseur Souris -------------------------- */

   curseur = XCreateFontCursor(dpy,numcur % 100);  /* Init du curseur souris */
   XDefineCursor(dpy,win,curseur);                                         
   if (numcur > 0) XFreeCursor(dpy,curseur);
   numcur++;


}

/* ---------------------------------------------------------------------- */
/* saisie                Saisie de touches                                */
/* ---------------------------------------------------------------------- */

void saisie()
{   
   #define    FIN   0xff57
   
   char       chaine[2];
   KeySym     ks;
   int        nbc;           
   static int x = 0, y = 0;                                                
                                                

   nbc = XLookupString(&ev,chaine, 2, &ks, NULL);
   printf("Nbc : %d Code touche : %x\n",nbc, ks);
   if (ks == FIN) sortie = True;

}

/* ---------------------------------------------------------------------- */
 
                 
