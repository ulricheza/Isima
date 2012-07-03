/* --------------------------------------------------------------------- */
/* 1. Le Maitre decoupe l'image a generer en blocs de taille presque egale    
   2. Le Maitre distribue le cacul de chaque bloc a un esclave en lui 
      envoyant les donnees necessaires
   3. Chaque esclave calcule son bloc de l'image, puis l'envoie au maitre
      pour qu'il puisse l'afficher                                         */
/* --------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

#include "complexe.h"
#include "fonctions.h"

#include "mpi.h"

#define TAILLE_ENTETE 8

// identification des communications
// message type
// longueur(int): nbDonnes + 6
// [idProc][xMin][xMax][yMin][yMax][nbDonnees][donnes]

int etiquette=0; // données
/*
int etiquette=1; // xmin
int etiquette=2; // xmax
int etiquette=3; // ymin
int etiquette=4; // ymax
* */

int nbProc = 4;

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

/* résultats de la paralisation */
int ** ret;

void paralNewton();



void maitre(int argc, char ** argv)
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
  
  // allocation of the return variable
  ret = (int **)malloc(sizeof(int*)*dimx);
  for (i=0; i<dimx; i++)
  {
     ret[i] =  (int*) malloc(sizeof(int)*dimy);
  }
  
  
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
        
      // calc
      paralNewton();
      
      // print results
	    for (xe=0; xe<dimx; xe++)
	      for (ye=0; ye<dimy; ye++)
		{
		  c = val_pixels[ret[xe][ye]];

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
            
      for (i=0; i<dimx; i++)
      {
           free(ret[i]);
      }
      free(ret);
            
      dimy=indic.height = evenement.xconfigure.height;
	   dimx=indic.width = evenement.xconfigure.width;

      

        // allocation of the return variable
        ret = (int **)malloc(sizeof(int*)*dimx);
        for (i=0; i<dimx; i++)
        {
           ret[i] =  (int*) malloc(sizeof(int)*dimy);
        }

	    XFreePixmap(display,image);
	    image=XCreatePixmap(display,racine,dimx, dimy,depth_def);
	    XSetForeground(display,cg_cp,blanc);
	    XFillRectangle(display,image,cg_cp,0,0,dimx,dimy);
      
      printf("maitre : dimx=%d, dimy=%d\n",dimx,dimy);
      // calc
      paralNewton();
      
      // print results
	    for (xe=0; xe<dimx; xe++)
	      for (ye=0; ye<dimy; ye++)
	       {
           c = val_pixels[ret[xe][ye]];
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

}

// write results in global variable ret
void paralNewton()
{
   
   // répartition des calculs
   int pasX = dimx / (nbProc-1);
   int i, j, xprec=0;
   int count, currX, currY;
   int message[TAILLE_ENTETE];
   int * messageIn;
   int tailleMessageMax=0;
   int tailleMessage;
   
   
   printf("pas=%d\n",pasX);
   
   for ( i=1; i< nbProc; i++)
   {
      // [idProc][xMin][xMax][yMin][yMax][nbDonnees][dimX][dimY][donnees]
      message[0] = i; /* id proc */
      message[1] = xprec; // xMIN
      tailleMessage=xprec;
      xprec += pasX;
      message[2] = xprec-1;
      if ( dimx - xprec < pasX)
      {
         message[2] = dimx; // xMAX
      }
      
      message[3] = 0; // minY = 0
      message[4] = dimy; // maxY
      message[5] = 0; // nbDonnees
      message[6]=dimx;
      message[7]=dimy;
      
      
      
      // envoi du message
      MPI_Send(message, TAILLE_ENTETE, MPI_INT, i, etiquette, MPI_COMM_WORLD);      
   }
      
   
   /* attente de réponse des fils */
   /* & réorganisation des résultats */
   
   MPI_Status statut;
   //sleep(4);
   xprec=0;
   count = 0;
   currX =0; currY=0;
   
   // allocation of the return variable
     ret = (int **)malloc(sizeof(int*)*dimx);
     for (i=0; i<dimx; i++)
     {
        ret[i] =  (int*) malloc(sizeof(int)*dimy);
     }
   
   for ( i=1; i<nbProc; i++)
   {   
      
      // prévision de la taille du message à recevoir
      tailleMessage = xprec;
      xprec += pasX;
      if ( dimx - xprec < pasX)
      {
         xprec = dimx; // xMAX
      }
      
      tailleMessage = (xprec - tailleMessage) * dimy + TAILLE_ENTETE;
      printf("tailleMessage - pere : %d\n",tailleMessage);

      messageIn = (int*) malloc (sizeof(int)*tailleMessage);
      puts("RECEPTION PERE");
      //sizeof(int)*tailleMessage
      MPI_Recv(messageIn, tailleMessage, MPI_INT, i, etiquette, MPI_COMM_WORLD, &statut);
      printf("pere: de fils %d (%d)", messageIn[0],i);
      puts("");
      
      for (j=0; j<20; j++)
      {
         printf("recu: %d | ",messageIn[j]);
      }
      puts("");

      // [idProc][xMin][xMax][yMin][yMax][nbDonnees][donnes]
      count = TAILLE_ENTETE;
      for (currX=messageIn[1]; currX<messageIn[2]; currX++)
      {
         for (currY=messageIn[3]; currY<messageIn[4]; currY++)
         {
            ret[currX][currY]=messageIn[count];
            count ++;
         }
         
      }
      /*
      for (j=6; j<messageIn[5]; j++)
      {
         ret[currX++][currY]=messageIn[j];
         if (currX >= dimx)
         {
            currX =0;
            currY++;
            printf("passage à la ligne %d\n",currY);
         }
         count++;
         // organisation des résultats
      }
      */
      puts("");
      free(messageIn);
   }
   printf("count = %d\n",count);
}



int main (int argc, char ** argv)
{
   int rang;
   MPI_Status statut;
   int messageIn[TAILLE_ENTETE];
   int * message;
   unsigned int i,j, count;
   int tailleMessage;
   complexe_t x;
   int c;
   int offset;
   
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD,&rang);
   MPI_Comm_size(MPI_COMM_WORLD,&nbProc);
   
   
   if (rang == 0) // maitre
   {
      //maitre(argc, argv);
      printf("nbProc = %d\n", nbProc);
      maitre(argc, argv);
      //paralNewton();
   }
   else { // esclave
   

      while (1)
      {
         printf("Je suis no %d\n",rang);
         
         
         
         MPI_Recv(messageIn, TAILLE_ENTETE, MPI_INT, 0, etiquette, MPI_COMM_WORLD, &statut);
         
         // [idProc][xMin][xMax][yMin][yMax][nbDonnees][dimX][dimY][donnees]
         tailleMessage = (messageIn[2] - messageIn[1]) * (messageIn[4] - messageIn[3]);
         message = (int *) malloc(sizeof(int)*(TAILLE_ENTETE+tailleMessage));
         count =TAILLE_ENTETE;
         printf("messageIN :");
         // entete du message
         for (i=0; i<TAILLE_ENTETE; i++)
         { message[i] = messageIn[i]; }
            message[5] = tailleMessage;
            dimx = messageIn[6];
            dimy = messageIn[7];
            printf("maitre : dimx=%d, dimy=%d\n",dimx,dimy);
         // calculs
         for (i=messageIn[1]; i<messageIn[2]; i++)
         {
            for ( j=messageIn[3]; j<messageIn[4]; j++)
            {
               x.re = (double)XMIN + ((double)i*(XMAX-XMIN))/((double)dimx); 
               x.im = (double)YMAX - ((double)j*(YMAX-YMIN))/((double)dimy);
               // indice de couleur 0, 1 ou 2
               c = couleur3(x, 0, 1, 2);
               /*printf("c = %d - x.re = %lf - x.im = %lf | i=%d & j=%d\n", c, x.re, x.im, i, j);*/
               message[count++] = c;
            }
         }
         
         
         printf("\n count: %d | taille message %d\n",count, tailleMessage);
         /*
         for (i=0; i<(tailleMessage+6); i++)
         {
            printf("%d | ",message[i]);
         }
         puts("");
         */
         // 6+tailleMessage -> si suppression, marche
         // sizeof(int)*(6+tailleMessage)
         MPI_Send(message, TAILLE_ENTETE+tailleMessage, MPI_INT, 0, etiquette, MPI_COMM_WORLD);
         
         puts("FILS: message sent");
         free(message);
      }
      
   }
   
   MPI_Finalize(); 
   return 0;
}

