/* -------------------------------------------------------------------------- */
/* Methode de NEWTON pour le calcul des racines d'une fonction f(x)=x^3-1     */
/* xn+1 = xn + f(xn) / f'(xn)                                                 */
/* -------------------------------------------------------------------------- */

#include <stdio.h>
#include <errno.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/X.h>
#include <X11/keysym.h>

#include "complexe.h"
#include "fonctions.h"

/* -------------------------------------------------------------------------- */
/* Les variables pour XWindow                                                 */
/* -------------------------------------------------------------------------- */
char         *tit_racine = "Newton";
Display      *display;
Window        racine;        /* fenetre mere de toutes les autres fenetres       */

GC            cg_cp;         /* contexte graphique pour le dessin definitif      */
Colormap      cmap;          /* table de couleurs par defaut                     */
unsigned long val_pixels[6]; /* les indices des cellules de couleurs allouees dans cmap */
int           fait_coul = {DoRed | DoGreen | DoBlue};
unsigned long noir, blanc;   /* couleurs noir et blanche                         */
int           i;
XColor        couleur, exact;



/* -------------------------------------------------------------------------- */
/* Fonction "main"  du programme newton                                       */
/* -------------------------------------------------------------------------- */
main(int argc, char **argv)
{
  int               ecran;
  XEvent            evenement;
  unsigned long     masque_valeur;
  XGCValues         valeurs_gc;

  XSizeHints        indic;
  char              caractere[10];
  KeySym            touche;

  int               encore, i;

  unsigned int      xe, ye;        /* coordonnees de l'ecran */
  unsigned int      c;             /* couleur */
  complexe_t          x;
  char              rep;


  /* --------------------------------------------------------- */
  /* Connexion au serveur X                                    */
  /* --------------------------------------------------------- */
  display = XOpenDisplay(NULL);
  if (!display) {
    fprintf(stderr, "Impossible d'ouvrir le display.\n");
    fprintf(stderr, "Assurez-vous que la variable DISPLAY est initialisee.\n");
    fprintf(stderr, "Elle doit contenir, par exemple : \"termx:0\"\n");
    exit(1);
  }

  /* --------------------------------------------------------- */
  /* Consultation de certaines caracteristiques du serveur X.  */
  /* --------------------------------------------------------- */
  ecran = DefaultScreen(display);
  blanc = WhitePixel(display,ecran);
  noir = BlackPixel(display,ecran);

  /* --------------------------------------------------------- */
  /* Allocation des couleurs                                   */
  /* --------------------------------------------------------- */

  cmap = DefaultColormap(display,ecran);

  /* allocation de couleurs rouge, vert, bleu */
  if (XAllocNamedColor(display, cmap, "indian red", &couleur, &exact)) 
    val_pixels[0] = couleur.pixel;
  else
    val_pixels[0] = noir;

  if (XAllocNamedColor(display, cmap, "navy blue", &couleur, &exact)) 
    val_pixels[1] = couleur.pixel;
  else
    val_pixels[1] = blanc;  

  if (XAllocNamedColor(display, cmap, "forest green", &couleur, &exact)) 
    val_pixels[2] = couleur.pixel;
  else
    val_pixels[2] = noir;

   
  /* --------------------------------------------------------- */
  /* Creation de la fenetre top-niveau du nom de "Newton"      */
  /* --------------------------------------------------------- */
  indic.x = 200; indic.y = 300;
  indic.width = 100; indic.height = 100;
  indic.flags = PPosition | PSize;
  racine = XCreateSimpleWindow(display, DefaultRootWindow(display),
			    indic.x, indic.y, indic.width, indic.height,
			    1, noir, blanc);
  /* Definition des proprietes standards de la fenetre top-niveau 
     a l'intention du gestionnaire de fenetres */
  XSetStandardProperties(display, racine, 
			 tit_racine, tit_racine, None, argv, argc, &indic);
  /* Selection des evenements interessants pour la fenetre top-niveau */
  XSelectInput(display, racine, 
	       KeyPressMask | ButtonPressMask |
	       ExposureMask | StructureNotifyMask);

  /* --------------------------------------------------------- */
  /* Creation d'un contexte graphique dessin */
  /* --------------------------------------------------------- */
  valeurs_gc.foreground = noir;
  valeurs_gc.background = blanc;
  valeurs_gc.line_width = 1;
  valeurs_gc.function = GXcopy;
  masque_valeur = GCForeground | GCBackground | GCLineWidth | GCFunction;
  cg_cp = XCreateGC(display, racine, masque_valeur, &valeurs_gc);

  XMapRaised(display, racine);

  /* --------------------------------------------------------- */
  /* Boucle Principale */
  /* --------------------------------------------------------- */
  encore = True;
  while (encore) {
    XNextEvent(display, &evenement);
    switch (evenement.type) {
    case Expose :
      if (evenement.xexpose.count == 0) {
	for (xe=0; xe<indic.width; xe++)
	  for (ye=0; ye<indic.height; ye++) {
	    x.re = (double)XMIN + ((double)xe*(XMAX-XMIN))/((double)(indic.width-1)); 
	    x.im = (double)YMAX - ((double)ye*(YMAX-YMIN))/((double)(indic.height-1));
            if (x.re==0 && x.im==0) c=0; else
	    c = couleur3(x, val_pixels[0], val_pixels[1], val_pixels[2]);
	    XSetForeground(display, cg_cp, c);
	    XDrawPoint(display, racine, cg_cp, xe,ye);
	  }
      }
      break;
     
    case MappingNotify :
	XRefreshKeyboardMapping(&(evenement.xmapping));
	break;

	/* a la reception d'un changement de taille de fenetre "racine", 
	   on change aussi la taille des fenetres descendantes  */ 
    case ConfigureNotify : 
	if (evenement.xconfigure.window == racine) {
	    /* recuperation de la nouvelle position et 
	       la nouvelle taille de la fenetre racine */
	  indic.x = evenement.xconfigure.x;
	  indic.y = evenement.xconfigure.y;
	  if ( (indic.width != evenement.xconfigure.width) ||
	       (indic.height != evenement.xconfigure.height)){
	    indic.width = evenement.xconfigure.width;
	    indic.height = evenement.xconfigure.height;

	    /* Reaffiche le contenu de la fenetre */
	    for (xe=0; xe<indic.width; xe++)
	      for (ye=0; ye<indic.height; ye++) {
		x.re = XMIN + xe*(XMAX-XMIN)/indic.width;
		x.im = YMAX - ye*(YMAX-YMIN)/indic.height;
		if (x.re==0 && x.im==0) c=0; else
		  c = couleur3(x, val_pixels[0], val_pixels[1], val_pixels[2]);
		XSetForeground(display, cg_cp, c);
		XDrawPoint(display, racine, cg_cp, xe,ye);
	      }
	  }
	}
      break;

    case KeyPress :
      i = XLookupString(&(evenement.xkey), caractere, 10, &touche, 0);
      if (touche == XK_End)
	encore = False;
      break;
    }
  }

  XDestroyWindow(display,racine);
  XFreeGC(display, cg_cp);
  XCloseDisplay(display);
}

