/* --------------------------------------------------------------------- */
/* 1. Le Maitre decoupe l'image a generer en blocs de taille presque egale    
   2. Le Maitre distribue le cacul de chaque bloc a un esclave en lui 
      envoyant les donnees necessaires
   3. Chaque esclave calcule son bloc de l'image, puis l'envoie au maitre
      pour qui puisse l'afficher                                         */
/* --------------------------------------------------------------------- */
#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

#include "complexe.h"
#include "fonctions.h"


/* --------------------------------------------------------------------- */
/* Les variables pour XWindow                                            */
/* --------------------------------------------------------------------- */
char         *tit_racine = "Newton Pixmap";
Display      *display;
Window        racine;        /* fenetre mere de toutes les autres fenetres */

GC            cg_cp;         /* contexte graphique pour le dessin definitif*/
Colormap      cmap;          /* table de couleurs par defaut               */
unsigned long val_pixels[6]; /* les indices des cellules de couleurs      
                                allouees dans cmap */

int           fait_coul = {DoRed | DoGreen | DoBlue};
unsigned long noir, blanc;   /* couleurs noir et blanche                  */
int           depth_def;
XColor        couleur, exact;
Drawable      image;         /* Drawable contenant la Pixmap   */

/* --------------------------------------------------------------------- */
/* Les variables globales concernant l'image                             */
/* --------------------------------------------------------------------- */
static int    dimx=240;
static int    dimy=240;      /* Taille de la fenetre graphique */
int           flag_cal=0;    /* flag pour le calcul de l'image */

main(int argc, char ** argv)
{
  int i, j;

  int               ecran;
  XEvent            evenement;
  unsigned long     masque_valeur;
  XGCValues         valeurs_gc;

  XSizeHints        indic;
  char              caractere[10];
  KeySym            touche;

  int               encore;
  char              rep;

  unsigned int      xe, ye;        /* coordonnees de l'ecran */
  unsigned int      c;             /* couleur */
  complexe_t        x;
   

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
  /* Allocation des couelurs                                   */
  /* --------------------------------------------------------- */
  depth_def = DefaultDepth(display, ecran);
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
  indic.width = dimx; indic.height = dimy;
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

  /* Creation de l'image */
  image=XCreatePixmap(display,racine,dimx,dimy,depth_def);
  XSetForeground(display,cg_cp,blanc);
  XFillRectangle(display,image,cg_cp,0,0,dimx,dimy);
  
  puts("Pressez la touche fin pour terminer");
  encore = 1;
  while (encore)
  {
    XNextEvent(display, &evenement);
    switch (evenement.type)
    {
    case KeyPress :
      i = XLookupString(&(evenement.xkey), caractere, 10, &touche, 0);
      if (touche == XK_End) encore = 0;
      break;
    case Expose :
      if (evenement.xexpose.count==0)
        {
	  if (flag_cal == 0) { 

	    for (xe=0; xe<dimx; xe++)
	      for (ye=0; ye<dimy; ye++)
		{
		  x.re = (double)XMIN + ((double)xe*(XMAX-XMIN))/((double)dimx); 
		  x.im = (double)YMAX - ((double)ye*(YMAX-YMIN))/((double)dimy);
		  c = couleur3(x, val_pixels[0], val_pixels[1], val_pixels[2]);

		  XSetForeground(display, cg_cp, c);
		  XDrawPoint(display, racine, cg_cp, xe,ye);
		  XDrawPoint(display, image, cg_cp, xe,ye);
	    }
	    flag_cal = 1;
	  }
	  else
	    XCopyArea(display,image,racine,cg_cp,0,0,dimx,dimy,0,0);
      	}
      break;
    case  ConfigureNotify :
      if (evenement.xconfigure.window == racine)
	{
	  if ((dimy != evenement.xconfigure.height) ||
	      (dimx != evenement.xconfigure.width)) {
	    dimy=indic.height = evenement.xconfigure.height;
	    dimx=indic.width = evenement.xconfigure.width;

	    XFreePixmap(display,image);
	    image=XCreatePixmap(display,racine,dimx, dimy,depth_def);
	    XSetForeground(display,cg_cp,blanc);
	    XFillRectangle(display,image,cg_cp,0,0,dimx,dimy);

	    for (xe=0; xe<dimx; xe++)
	      for (ye=0; ye<dimy; ye++)
		{
		  x.re = (double)XMIN + ((double)xe*(XMAX-XMIN))/((double)dimx); 
		  x.im = (double)YMAX - ((double)ye*(YMAX-YMIN))/((double)dimy);
		  c = couleur3(x, val_pixels[0], val_pixels[1], val_pixels[2]);
 		  XSetForeground(display, cg_cp, c);
		  XDrawPoint(display, racine, cg_cp, xe,ye);
		  XDrawPoint(display, image, cg_cp, xe,ye);
	    }

	    /*	    flag_cal = 1;*/
	  }
	}
    }
  }

  XDestroyWindow(display,racine);
  XFreeGC(display, cg_cp);
  XFreePixmap(display,image);
  XCloseDisplay(display);
  return 0;
}




