
/* fichier qui ccontient les fonctions necessaire a la lecture des images */

#define SLACH "/"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "erreur.h"
#include "imaio.h"
#include <sys/types.h>
#include <sys/mman.h>
#include <netinet/in.h>


FILE *FRMT(filename,np,nl)

char *filename;
int *np,*nl;

/****************************************************************
*   SUJ : AERO,SAR						*
*   BUT : Lire la taille d'une image et ouvrir le fichier	*
*	  de donnees						*
*****************************************************************/

{
FILE *fp;
char path[255];

strcpy(path,filename);
strcat(path,".dim");

fp = fopen(path,"r");

if (fp==NULL) erreur("FRMT","impossible d'ouvrir le fichier entete",1);

fscanf(fp,"%d %d",np,nl);

fclose(fp);

strcpy(path,filename);
strcat(path,".ima");

fp = fopen(path,"rb");

if (fp==NULL) erreur("FRMT","impossible d'ouvrir le fichier de donne",1);

return(fp);

}

int test_ima(filename,np,nl)

char *filename;
int *np,*nl;

/****************************************************************
*   SUJ : AERO,SAR,IMA						*
*   BUT : Tester l'existence d'une image, Lire sa taille d'une 	*
*	  de donnees						*
*   PAR : filename	nom de fichier				*
*	  np,nl		nombre de colonne et de ligne		*
*   RET : 0		Ok sur toute la ligne			*
*	  1		Pas de fichier .dim			*
*	  2		Pas de fichier .ima			*
*   DAT : 17/01/93						*
*****************************************************************/

{
FILE *fp;
char path[255];

strcpy(path,filename);
strcat(path,".dim");

fp = fopen(path,"r");

if (fp==NULL) return(1);

fscanf(fp,"%d %d",np,nl);

fclose(fp);

strcpy(path,filename);
strcat(path,".ima");

fp = fopen(path,"rb");

if (fp==NULL) return(2);

fclose(fp);

return(0);

} /* FIN test_ima */



FILE *ouvre_sortie(filename,np,nl)

char *filename;
int *np,*nl;

/****************************************************************
*   SUJ : AERO,SAR						*
*   BUT : ecrire la taille d'une image et ouvrir le fichier	*
*	  de donnees						*
*****************************************************************/

{
FILE *fp;
char path[255];

strcpy(path,filename);
strcat(path,".dim");

fp = fopen(path,"w");

if (fp==NULL) erreur("ouvre_sortie","impossible d'ouvrir le fichier entete",1);

fprintf(fp,"%d %d",*np,*nl);

fclose(fp);

strcpy(path,filename);
strcat(path,".ima");

fp = fopen(path,"wb");

if (fp==NULL) erreur("FRMT","impossible d'ouvrir le fichier de donne",1);

return(fp);

}  /* FIN de ouvre_sortie */


FILE *ouvre_sortie16(filename,np,nl)

char *filename;
int *np,*nl;

/****************************************************************
*   SUJ : AERO,SAR						*
*   BUT : ecrire la taille d'une image et ouvrir le fichier	*
*	  de donnees (16 bits)					*
*****************************************************************/

{
FILE *fp;
char path[255];

strcpy(path,filename);
strcat(path,".dim");

fp = fopen(path,"w");

if (fp==NULL) erreur("FRMT","impossible d'ouvrir le fichier entete",1);

fprintf(fp,"%d %d",*np,*nl);

fclose(fp);

strcpy(path,filename);
strcat(path,".imw");

fp = fopen(path,"wb");

if (fp==NULL) erreur("FRMT","impossible d'ouvrir le fichier de donne",1);

return(fp);

}  /* FIN de ouvre_sortie16 */


void LECIMA(fp,buff,np,rien,nbm,nbf)

FILE *fp;
void *buff,*rien;
int *np,*nbm,*nbf;

/****************************************************************
* 	SUJ :	AERO						*
*	BUT :	Lire une ligne de l'image pointer par fp	*
*								*
*****************************************************************/

{
  fread(buff,*nbf,*np,fp);

  if (fp==NULL) erreur("LECIMA","TENTATIVE DE LIRE APRES LA FIN DE FICHIER",1);


}


void ECRIMA(fp,buff,np,rien,nbm,nbf)

FILE *fp;
void *buff,*rien;
int *np,*nbm,*nbf;

/****************************************************************
* 	SUJ :	AERO						*
*	BUT :	ECRIRE une ligne de l'image pointer par fp	*
*								*
*****************************************************************/

{
  fwrite(buff,*nbf,*np,fp);

  if (fp==NULL) erreur("LECIMA","TENTATIVE D'ECRITURE APRES LA FIN DE FICHIER",1);


}

int readline(buff,ima)
void *buff;
TIMAGE *ima;

/****************************************************************
* 								*
*	BUT :	Lire une ligne de l'image 			*
*								*
*****************************************************************/

{
int ret;
int i;

ret = fread(buff,IMA_NBF(ima),IMA_NP(ima),IMA_DES(ima));

if (IMA_TYPE(ima)==TEL_IMW)
for (i=0;i<(IMA_NP(ima));i++)
  ((PIXRAD *)buff)[i] = ntohs(((PIXRAD *)buff)[i]);

return(ret);

}  /* FIN de readima */


int writeline(buff,ima)
void *buff;
TIMAGE *ima;

/****************************************************************
* 	SUJ :	AERO						*
*	BUT :	ECRIRE une ligne de l'image 			*
*								*
*****************************************************************/

{
int i;

if (IMA_TYPE(ima)==TEL_IMW)
for (i=0;i<(IMA_NP(ima));i++)
  ((PIXRAD *)buff)[i] = htons(((PIXRAD *)buff)[i]);


return(fwrite(buff,IMA_NBF(ima),IMA_NP(ima),IMA_DES(ima)));

}  /* FIN de writeima */

int verbose = 1;

int open_ima_in(ima,type)
TIMAGE *ima;
int type;
/****************************************************************
*	BUT : Ouvrir une image sur disk				*
*	PAR : 	ima l'image					*
*		type le type de l'image				*
*	RET :	Le type de l'image				*
*****************************************************************/
{
int ret;


switch (type)
  {
    case  0   :	/* pas de type specifie */
                verbose = 0;
                if (open_ima_in(ima,TEL_IMW))
                   ret = TEL_IMW;
                    else
                   if (open_ima_in(ima,TEL_IMA))
                   ret = TEL_IMA;
                    else
                     ret = 0;                   
    		break;
    		
    case  TEL_IMA :  /* .ima 8 bit */
                  {
                	FILE *fp;
			char path[512];

			strcpy(path,IMA_NAME(ima));
			strcat(path,".dim");

			fp = fopen(path,"r");

			if (fp==NULL) ret = 0;
			else
			{
			fscanf(fp,"%d %d",&(IMA_NP(ima)),&(IMA_NL(ima)));

			fclose(fp);

			strcpy(path,IMA_NAME(ima));
			strcat(path,".ima");

			IMA_DES(ima) = fopen(path,"rb");

			if ((IMA_DES(ima))==NULL) ret = 0;
				else
			 {
				IMA_TYPE(ima) = TEL_IMA;
                        	IMA_NBF(ima) = 1;
                        	IMA_NBM(ima) = 1;
                        	IMA_PLAN(ima) = 1;
                        	IMA_PIX_MAX(ima) = 256; 
                        	
                        	ret = TEL_IMA;
                         } 
			}                         
                }
                	break;
    case  TEL_IMW :  /* .imw 16 bit */
                  {
                	FILE *fp;
			char path[512];

			strcpy(path,IMA_NAME(ima));
			strcat(path,".dim");

			fp = fopen(path,"r");

			if (fp==NULL) ret = 0;
			else
			{
			fscanf(fp,"%d %d",&(IMA_NP(ima)),&(IMA_NL(ima)));

			fclose(fp);

			strcpy(path,IMA_NAME(ima));
			strcat(path,".imw");

			IMA_DES(ima) = fopen(path,"rb");

			if ((IMA_DES(ima))==NULL) ret = 0;
			  else
			 {

                        	IMA_TYPE(ima) = TEL_IMW;
                        	IMA_NBF(ima) = 2;
                        	IMA_NBM(ima) = 2;
                        	IMA_PLAN(ima) = 1;
                        	IMA_PIX_MAX(ima) = 65536; 
                        	
                        	ret = TEL_IMW;                          
                	 }
                	}
                }
                break;
                
    case  TEL_RVB : /* .rvb 24 bit */
                  {
                	FILE *fp;
			char path[512];

			strcpy(path,IMA_NAME(ima));
			strcat(path,".dim");

			fp = fopen(path,"r");

			if (fp==NULL) ret = 0;
			else
			{
			fscanf(fp,"%d %d",&(IMA_NP(ima)),&(IMA_NL(ima)));

			fclose(fp);

			strcpy(path,IMA_NAME(ima));
			strcat(path,".rvb");

			IMA_DES(ima) = fopen(path,"rb");

			if ((IMA_DES(ima))==NULL) ret = 0;
			else
			 {

                          IMA_TYPE(ima) = TEL_RVB;
                          IMA_NBF(ima) = 3;
                          IMA_NBM(ima) = 3;
                          IMA_PLAN(ima) = 3;
                          IMA_PIX_MAX(ima) = 256;  
                          
                          ret = TEL_RVB;                         
                         }
			}
                }             
                break;
                
    case  TEL_IMC : /* .imc 32 bit */
                  {
                	FILE *fp;
			char path[512];

			strcpy(path,IMA_NAME(ima));
			strcat(path,".dim");

			fp = fopen(path,"r");

			if (fp==NULL) ret = 0;
                          else
                        {
			fscanf(fp,"%d %d",&(IMA_NP(ima)),&(IMA_NL(ima)));

			fclose(fp);

			strcpy(path,IMA_NAME(ima));
			strcat(path,".rvb");

			IMA_DES(ima) = fopen(path,"rb");

			if (IMA_DES(ima)==NULL) ret = 0;
                           else
			      {
                        	IMA_TYPE(ima) = TEL_IMC;
                        	IMA_NBF(ima) = 4;
                        	IMA_NBM(ima) = 4;
                        	IMA_PLAN(ima) = 4;
                        	IMA_PIX_MAX(ima) = 256;                           
                        	ret = TEL_IMC;
                              }
			}
                	
                }   
                break;    
    default : erreur("open_ima_in","Type d'image inconnue",200);   
          
  } /* fin du switch */
  
  if (ret == 0)
    {
      if (verbose)
        {
      fprintf(stderr,"------------- Open_ima_in --------------\n");
      fprintf(stderr,"Probleme sur : %s \n",IMA_NAME(ima));
      fprintf(stderr,"----------------------------------------\n");
        }
      return(0);
    }
    else { verbose = 1; return(IMA_TYPE(ima)); }
    

}  /* FIN DE OPEN IMA */

int open_ima_out(ima,type)
TIMAGE *ima;
int type;
/****************************************************************
*	BUT : Ouvrir une image sur disk				*
*	PAR : 	ima l'image					*
*		type le type de l'image				*
*	RET :	Le type de l'image				*
*****************************************************************/
{
int ret;

switch (type)
  {    		
    case  TEL_IMA :  /* .ima 8 bit */
                  {
                	FILE *fp;
			char path[512];

			strcpy(path,IMA_NAME(ima));
			strcat(path,".dim");

			fp = fopen(path,"w");

			if (fp==NULL) ret = 0;
			else
			{
			fprintf(fp,"%d %d",(IMA_NP(ima)),(IMA_NL(ima)));

			fclose(fp);

			strcpy(path,IMA_NAME(ima));
			strcat(path,".ima");

			IMA_DES(ima) = fopen(path,"wb");

			if (IMA_DES(ima)==NULL) ret = 0;
                        }   
                }
                	break;
    case  TEL_IMW :  /* .imw 16 bit */
                  {
                	FILE *fp;
			char path[512];

			strcpy(path,IMA_NAME(ima));
			strcat(path,".dim");

			fp = fopen(path,"w");

			if (fp==NULL) ret = 0;
			else
			{
			fprintf(fp,"%d %d",(IMA_NP(ima)),(IMA_NL(ima)));

			fclose(fp);

			strcpy(path,IMA_NAME(ima));
			strcat(path,".imw");

			IMA_DES(ima) = fopen(path,"wb");

			if (IMA_DES(ima)==NULL) ret = 0;
                	}              	
                }
                break;
                
    case  TEL_RVB : /* .rvb 24 bit */
                  {
                	FILE *fp;
			char path[512];

			strcpy(path,IMA_NAME(ima));
			strcat(path,".dim");

			fp = fopen(path,"w");

			if (fp==NULL) ret = 0;
			else
			{
			fprintf(fp,"%d %d",(IMA_NP(ima)),(IMA_NL(ima)));

			fclose(fp);

			strcpy(path,IMA_NAME(ima));
			strcat(path,".rvb");

			IMA_DES(ima) = fopen(path,"wb");

			if (IMA_DES(ima)==NULL) ret = 0;
			}

                }             
                break;
                
    case  TEL_IMC : /* .imc 32 bit */
                  {
                	FILE *fp;
			char path[512];

			strcpy(path,IMA_NAME(ima));
			strcat(path,".dim");

			fp = fopen(path,"w");

			if (fp==NULL) ret = 0;
			else
			{
			fprintf(fp,"%d %d",(IMA_NP(ima)),(IMA_NL(ima)));

			fclose(fp);

			strcpy(path,IMA_NAME(ima));
			strcat(path,".rvb");

			IMA_DES(ima) = fopen(path,"wb");

			if (IMA_DES(ima)==NULL) ret = 0;;
			}
                }   
                break;    
    default : erreur("open_ima_in","Type d'image inconnue",200);   
          
  } /* fin du switch */
  
  if (ret = 0)
    {
      fprintf(stderr,"------------- Open_ima_out\n --------------");
      fprintf(stderr,"Probleme sur : %s \n",IMA_NAME(ima));
      fprintf(stderr,"------------------------------------------");
      return(0);
    }
    else return(IMA_TYPE(ima));
    

}  /* FIN DE OPEN IMA OUT*/

int rew_ima(ima)
TIMAGE *ima;
/****************************************************************
*	BUT : Rembobiner une image sur disk			*
*	PAR : 	ima l'image					*
*****************************************************************/
{

rewind(IMA_DES(ima));

} /* FIN de rew_ima */

int close_ima(ima)
TIMAGE *ima;
/****************************************************************
*	BUT : fermer une image sur disk				*
*	PAR : 	ima l'image					*
*****************************************************************/
{

fclose(IMA_DES(ima));

} /* FIN de close_ima */


void set_ima_filename(ima,dir,name)
TIMAGE *ima;
char *dir,*name;
/****************************************************************
*	BUT : donner le nom de fichier d'une image 		*
*	PAR : 	ima l'image 					*
*		name le nom de fichier				*
*****************************************************************/
{

  if (strlen(dir)!=0)
    {
      strcpy(IMA_NAME(ima),dir);
      strcat(IMA_NAME(ima),SLACH);
      strcat(IMA_NAME(ima),name);
    }
    else
    {
      strcpy(IMA_NAME(ima),name);
    }
    
} /* FIN de set_ima filename */


long of_pixel(x,y,plan,ima)
long x,y,plan;
TIMAGE *ima;
/**********************************************************
*	BUT : renvoyer l'offset en pixel dans un tableau  *
*		de char qu'elle que soit la taille	  *
*	PAR : 	x	position en ligne		  *
*		y	position en colonne		  *
*		plan le plan de travail			  *
*		ima l'image concerne			  *
***********************************************************/
{
int of;

of = IMA_NP(ima)*IMA_NBM(ima)*IMA_PLAN(ima)*y
		 + x*IMA_NBM(ima)*IMA_PLAN(ima) 
		 + plan*IMA_NBM(ima);
		 
return(of);

} /* fin of_pixel */


long pixel_val(x,y,plan,ima)
long x,y,plan;
TIMAGE *ima;
/**********************************************************
*	BUT : renvoyer la valeur du pixel sur l'image     *
*		de char qu'elle que soit la taille	  *
*	PAR : 	x	position en ligne		  *
*		y	position en colonne		  *
*		plan le plan de travail			  *
*		ima l'image concerne			  *
***********************************************************/
{

int of,i;

long value = 0;

of=of_pixel(x,y,plan,ima);

if (IMA_CODE(ima))
  for (i=0;i<IMA_NBM(&ima);i++)
    {
      value = 256L*value+(long)(((PIXEL *)IMA_BUFFER(ima))[of+i]);
    }
   else
  for (i=0;i<IMA_NBM(&ima);i++)
    {
      value = 256L*value+
      	    (long)(((PIXEL *)IMA_BUFFER(ima))[of+IMA_NBM(&ima)-i]);
    }
     
      

} /* FIN de pixel_val */


PIXRAD  **charima16(ima)
TIMAGE *ima;
/*****************************************************************
*	BUT : charger une image 8 bits ou 16 bits dans un buffer 16 bit    *
*	PAR : ima le type image			    *
*	RET : le pointeur sur l'image			    *
*	WAR : ocupation memoire double		    *
*****************************************************************/
{
PIXRAD **buffer,*point;
PIXEL *b8;
register int i,j;

if  ((IMA_TYPE(ima)==TEL_IMA)||(IMA_TYPE(ima)==TEL_IMW))
  if (IMA_DES(ima)!=NULL)
    {

    buffer = (PIXRAD **)malloc(IMA_NL(ima)*sizeof(*buffer));

   VPOINTEUR("char_ima16",buffer);

   b8 = (PIXEL *)malloc(IMA_NP(ima)*sizeof(*b8));

   for (i=0;i<IMA_NL(ima);i++)
    {
       buffer[i] = (PIXRAD *)malloc(IMA_NP(ima)*sizeof(**buffer) );
       VPOINTEUR("char_ima16",buffer[i]);
         switch (IMA_TYPE(ima))
          { 
            case TEL_IMA : 
                readline(b8,ima);
                for (j=0;j<IMA_NP(ima);j++)
                   buffer[i][j] = b8[j];
                break;
             case TEL_IMW :
                readline(buffer[i],ima);
                /* for (j=0;j<IMA_NP(ima);j++)
                    buffer[i][j]=(PIXRAD)ntohs(buffer[i][j]); */
               break;
          }    
      }
    }
    else
       erreur("charima16","IMAGE non ouverte",100);
        else
          erreur("charima16","IMAGE de type incorrecte pour cette operation",200);
          
free(b8);
return(buffer);          
          
} /* fin de charima */

/* ajout du memory mmaaaping */

void *mk_map(NP_LOC,NL_LOC,NO_LOC)
  int NP_LOC, NL_LOC,NO_LOC;
/****************************************************************
*	BUT : Creation d'un fichier NP*NL			*
*	PAR : 	NP_LOC, NL_LOC, NO_LOC les taille x,y,z		*
*		FILE le nom du fichier de mmapings		*
*****************************************************************/			{								
	  char CHAINE_LOC[512];
	  FILE *fp;						
	  static int FILE_NUM;
	  void *adresse;
	  
	  if (getenv("AU_FOU"))
	    if (atoi(getenv("AU_FOU"))<(NL_LOC*NP_LOC*NO_LOC))
	       erreur("mk_map","AU FOU : Ca va pas non : memoire",500);
	       
	  							
	  sprintf(CHAINE_LOC,"mkfile %d /tmp/cg_mmap_%d_%d"		
	  				      ,NL_LOC*NP_LOC*NO_LOC
	  				      ,getpid()
	  				      ,FILE_NUM); 
	  system(CHAINE_LOC);						
	  sprintf(CHAINE_LOC,"/tmp/cg_mmap_%d_%d",getpid(),FILE_NUM);
	  
	  FILE_NUM++;
	  
	  fp = fopen(CHAINE_LOC,"r+b");
	  
	  /* la on map */
	  
	  adresse = (void *)mmap(0,
	  		/* taille */ NP_LOC*NL_LOC*NO_LOC,
	  		/* prot   */ PROT_READ|PROT_WRITE,
	  		/* mode   */ MAP_SHARED,
	  		/* file   */ fileno(fp),
	  		/* offset */ 0);
	  		
	  if (adresse!=NULL) return(adresse);
	         else
	          return(NULL);	
}	


/* Ajout de la gestion des luts */
/* DAT : lun avr  3 18:16:11 MEST 2000 */


int read_3lt(cmap,filename)
TCMAP *cmap;
char *filename;
/*********************************************************************
*	BUT : Lire une lu dans filename.3lt                          *
*       PAR : cmap       une colormap                                *
*             filename   un nom de fichier                           *
*       RET : 1 table gris par defaut                                *
*             2 table lut dans un fichier                            *
*       REM : le fichier 3lt est de  format : 255*r puis 255*v	     *
*             et 225*v                                               *                                	
**********************************************************************/
{
FILE *fp;
char file[512];
int i;

strcpy(file, filename);
strcat(file,".3lt");

cmap->nb_colors=PIXEL_MAX;

fp = fopen(file,"r");

if (fp==NULL)
  { 
  
  for (i=0;i<PIXEL_MAX;i++)
    {
       cmap->r[i] = i;
       cmap->v[i] = i;
       cmap->b[i] = i;
    }
    
    return(1);
  }
  
for (i=0;i<PIXEL_MAX;i++)
  fscanf(fp,"%d",&(cmap->r[i]));
  
for (i=0;i<PIXEL_MAX;i++)
  fscanf(fp,"%d",&(cmap->v[i]));
  
for (i=0;i<PIXEL_MAX;i++)
  fscanf(fp,"%d",&(cmap->b[i]));

fclose(fp);

return(2);

} /* FIN de read_3lt */


/*********************************************************
* IMAGE RVB                                              *
* DAT : Tue Aug 30 16:21:53 CEST 2005                    *
**********************************************************/

PIXRVB **charimarvb(char *file, int *np, int *nl)
/***********************************************************
*	BUT : charger une image rvb                        *
************************************************************/
{
PIXRVB **ima;
int i;
char chaine[512];
FILE *fp;

/*********************** entete **************************/
strcpy(chaine,file);
strcat(chaine,".dim");

fp = fopen(chaine,"r");

if (fp==NULL)
  erreur("charimarvb -> erreur",file,FILE_ERR);

fscanf(fp,"%d %d",np,nl);

fclose(fp);

/********************** allocation ************************/

ima = (PIXRVB **)malloc(*nl*sizeof(*ima));

if (ima==NULL)
  erreur("charimarvb -> erreur",file,MEM_ERR);

for (i=0;i<*nl;i++)
  {
    ima[i] = (PIXRVB *)malloc(*np*sizeof(**ima)); 
    if (ima[i]==NULL)
       erreur("charimarvb -> erreur",file,MEM_ERR);

  }

/********************************************************/
strcpy(chaine,file);
strcat(chaine,".rvb");

fp = fopen(chaine,"rb");

if (fp==NULL)
  erreur("charimarvb -> erreur",file,FILE_ERR);

for (i=0;i<*nl;i++)
   fread(ima[i],*np,3,fp);

fclose(fp);

return(ima);

} /* FIN de charimarvb */



int vidimarvb(char *file,PIXRVB **rvb,int np,int nl)
{
FILE *fp;
char chaine[512];
int i;

/*********************** entete **************************/
strcpy(chaine,file);
strcat(chaine,".dim");

fp = fopen(chaine,"w");

if (fp==NULL)
  erreur("vidimarvb -> erreur",file,FILE_ERR);

fprintf(fp,"%d %d",np,nl);

fclose(fp);

/********************************************************/
strcpy(chaine,file);
strcat(chaine,".rvb");

fp = fopen(chaine,"w");

if (fp==NULL)
  erreur("vidimarvb -> erreur",file,FILE_ERR);

for (i=0;i<nl;i++)
   fwrite(rvb[i],np,3,fp);

fclose(fp);

return(OKDAC);

}


char *ima_basename(char *res, char *filename)
/***********************************************************
*      BUT : enleve l'extention au nom de fichier pour     *
*            .ima, .rvb, .imw et .dim                      *
*      PAR:  filename                                      *
*             res le resulat                               *
*	RET:  l'adresse de res                             *
************************************************************/
{
char last[5];
int nocut=1;

if (strlen(filename)>4)
  {
        strcpy(last,&(filename[strlen(filename)-4]));
	
	nocut*=strcmp(last,".ima");
	nocut*=strcmp(last,".dim");
	nocut*=strcmp(last,".imw");
	nocut*=strcmp(last,".rvb");
	
	strcpy(res,filename);
	
	if (!nocut)
	  {
	    res[strlen(filename)-4]=0;
	  }   
  }	  

return(res);

}  /* FIn de ima_basename */

/* FIN DU FICHIER imaio.c */
