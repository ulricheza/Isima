/****************************************************************
*   	BUT : fichier include pour imaio.h			*
*****************************************************************
*	AUT : Gouinaud Christophe				*
*	DAT : 11/10/93						*
*****************************************************************/

#ifndef CG_ERREUR
#include "erreur.h"
#endif


#define CG_IMAIO 1


#define PIXEL unsigned char
#define PIXRAD unsigned short

#define PIXEL_MAX  256
#define PIXRAD_MAX 65536


#define TEL_IMA		100
#define TEL_RVB		102
#define TEL_IMW		101
#define TEL_IMC		103


#define MEM_ERR_IMAIO(X) if (X==NULL) erreur("imaio","erreur d'allocation",2)

#define VALLOC(X,NP)  					        	\
        X=(PIXEL *)malloc(NP*sizeof(*X));				\
        MEM_ERR_IMAIO(X);

#define VALLOC2(X,NP)  					        	\
        X=(PIXRAD *)malloc(NP*sizeof(*X));				\
        MEM_ERR_IMAIO(X);

#define VALLOCI(X,NP)  					        	\
        X=(int *)malloc(NP*sizeof(*X));					\
        MEM_ERR_IMAIO(X);

#define VALLOCF(X,NP)  					        	\
        X=(float *)malloc(NP*sizeof(*X));					\
        MEM_ERR_IMAIO(X);

#define VALLOCD(X,NP)  					        	\
        X=(double *)malloc(NP*sizeof(*X));					\
        MEM_ERR_IMAIO(X);

#define MALLOC(X,NP,NL)  					        \
        X=(PIXEL **)malloc(NL*sizeof(*X));				\
        MEM_ERR_IMAIO(X); 						\
        { int I_LOC;							\
        for (I_LOC=0;I_LOC<NL;I_LOC++) 					\
            { X[I_LOC]=(PIXEL *)malloc(NP*sizeof(**X));			\
        			MEM_ERR_IMAIO(X[I_LOC]); } 	}		
#define MALLOC2(X,NP,NL)  					        \
        X=(PIXRAD **)malloc(NL*sizeof(*X));				\
        MEM_ERR_IMAIO(X); 						\
        { int I_LOC;							\
        for (I_LOC=0;I_LOC<NL;I_LOC++) 					\
            { X[I_LOC]=(PIXRAD *)malloc(NP*sizeof(**X));		\
        			MEM_ERR_IMAIO(X[I_LOC]); }    }		

#define MALLOCRVB(X,NP,NL)  					        \
        X=(PIXRVB **)malloc(NL*sizeof(*X));				\
        MEM_ERR_IMAIO(X); 						\
        { int I_LOC;							\
        for (I_LOC=0;I_LOC<NL;I_LOC++) 					\
            { X[I_LOC]=(PIXRVB *)malloc(NP*sizeof(**X));		\
        			MEM_ERR_IMAIO(X[I_LOC]); }    }		

#define MALLOC4(X,NP,NL)  					        \
        X=(int **)malloc(NL*sizeof(*X));				\
        MEM_ERR_IMAIO(X); 						\
        { int I_LOC;							\
        for (I_LOC=0;I_LOC<NL;I_LOC++) 					\
            { X[I_LOC]=(int *)malloc(NP*sizeof(**X));		\
        			MEM_ERR_IMAIO(X[I_LOC]); }    }


#define MALLOCF(X,NP,NL)  					        \
        X=(float **)malloc(NL*sizeof(*X));				\
        MEM_ERR_IMAIO(X); 						\
        { int I_LOC;							\
        for (I_LOC=0;I_LOC<NL;I_LOC++) 					\
            { X[I_LOC]=(float *)malloc(NP*sizeof(**X));		\
        			MEM_ERR_IMAIO(X[I_LOC]); }    }


#define CALLOC(X,NP,NL)  					        \
        X=(PIXEL **)malloc(NL*sizeof(*X));				\
        MEM_ERR_IMAIO(X); 						\
        { int I_LOC;							\
        for (I_LOC=0;I_LOC<NL;I_LOC++) 					\
            { X[I_LOC]=(PIXEL *)calloc(NP,sizeof(**X));			\
        			MEM_ERR_IMAIO(X[I_LOC]); } 	}		
#define CALLOC2(X,NP,NL)  					        \
        X=(PIXRAD **)malloc(NL*sizeof(*X));				\
        MEM_ERR_IMAIO(X); 						\
        { int I_LOC;							\
        for (I_LOC=0;I_LOC<NL;I_LOC++) 					\
            { X[I_LOC]=(PIXRAD *)calloc(NP,sizeof(**X));		\
        			MEM_ERR_IMAIO(X[I_LOC]); }    }
#define CALLOC4(X,NP,NL)  					        \
        X=(int **)malloc(NL*sizeof(*X));				\
        MEM_ERR_IMAIO(X); 						\
        { int I_LOC;							\
        for (I_LOC=0;I_LOC<NL;I_LOC++) 					\
            { X[I_LOC]=(int *)calloc(NP,sizeof(**X));		\
        			MEM_ERR_IMAIO(X[I_LOC]); }    }        			
#define CALLOCF(X,NP,NL)  					        \
        X=(float **)malloc(NL*sizeof(*X));				\
        MEM_ERR_IMAIO(X); 						\
        { int I_LOC;							\
        for (I_LOC=0;I_LOC<NL;I_LOC++) 					\
            { X[I_LOC]=(float *)calloc(NP,sizeof(**X));		\
        			MEM_ERR_IMAIO(X[I_LOC]); }    }		

#define CALLOCD(X,NP,NL)  					        \
        X=(double **)malloc(NL*sizeof(*X));				\
        MEM_ERR_IMAIO(X); 						\
        { int I_LOC;							\
        for (I_LOC=0;I_LOC<NL;I_LOC++) 					\
            { X[I_LOC]=(double *)calloc(NP,sizeof(**X));		\
        			MEM_ERR_IMAIO(X[I_LOC]); }    }	


#define FREE(X,NP,NL)							\
	{ int I_LOC;							\
	for (I_LOC=0;I_LOC<NL;I_LOC++)					\
		free(X[I_LOC]);						\
	free(X);							\
	}
	
/* les meme en memorry-maping */
 

#define MALLOC_MMAP(X,NP,NL)  					        \
	{ 								\
	  PIXEL *BU_LOC;						\
	  BU_LOC = (PIXEL *)mk_map(NP,NL,1);				\
          X=(PIXEL **)malloc(NL*sizeof(*X));				\
        MEM_ERR_IMAIO(X); 						\
        { int I_LOC;							\
        for (I_LOC=0;I_LOC<NL;I_LOC++) 					\
            { X[I_LOC]=&(BU_LOC[I_LOC*NP]);				\
        			MEM_ERR_IMAIO(X[I_LOC]); } 	}     }	
        				
#define MALLOC2_MMAP(X,NP,NL)  					        \
	{ 								\
	  PIXRAD *BU_LOC;						\
	  BU_LOC = (PIXRAD *)mk_map(NP,NL,2);				\
          X=(PIXRAD **)malloc(NL*sizeof(*X));				\
        MEM_ERR_IMAIO(X); 						\
        { int I_LOC;							\
        for (I_LOC=0;I_LOC<NL;I_LOC++) 					\
            { X[I_LOC]=&(BU_LOC[I_LOC*NP]);				\
        			MEM_ERR_IMAIO(X[I_LOC]); } 	}     }	
#define MALLOCF_MMAP(X,NP,NL)  					        \
	{ 								\
	  float *BU_LOC;						\
	  BU_LOC = (float *)mk_map(NP,NL,sizeof(float));		\
          X=(float **)malloc(NL*sizeof(*X));				\
        MEM_ERR_IMAIO(X); 						\
        { int I_LOC;							\
        for (I_LOC=0;I_LOC<NL;I_LOC++) 					\
            { X[I_LOC]=&(BU_LOC[I_LOC*NP]);				\
        			MEM_ERR_IMAIO(X[I_LOC]); } 	}     }
        			
#define CALLOC_MMAP(X,NP,NL)  					        \
        X=(PIXEL **)malloc(NL*sizeof(*X));				\
        MEM_ERR_IMAIO(X); 						\
        { int I_LOC;							\
        for (I_LOC=0;I_LOC<NL;I_LOC++) 					\
            { X[I_LOC]=(PIXEL *)calloc(NP,sizeof(**X));			\
        			MEM_ERR_IMAIO(X[I_LOC]); } 	}		
#define CALLOC2_MMAP(X,NP,NL)  					        \
        X=(PIXRAD **)malloc(NL*sizeof(*X));				\
        MEM_ERR_IMAIO(X); 						\
        { int I_LOC;							\
        for (I_LOC=0;I_LOC<NL;I_LOC++) 					\
            { X[I_LOC]=(PIXRAD *)calloc(NP,sizeof(**X));		\
        			MEM_ERR_IMAIO(X[I_LOC]); }    }
        			
#define CALLOCF_MMAP(X,NP,NL)  					        \
        X=(float **)malloc(NL*sizeof(*X));				\
        MEM_ERR_IMAIO(X); 						\
        { int I_LOC;							\
        for (I_LOC=0;I_LOC<NL;I_LOC++) 					\
            { X[I_LOC]=(float *)calloc(NP,sizeof(**X));		\
        			MEM_ERR_IMAIO(X[I_LOC]); }    }		

#define CALLOCD_MMAP(X,NP,NL)  					        \
        X=(double **)malloc(NL*sizeof(*X));				\
        MEM_ERR_IMAIO(X); 						\
        { int I_LOC;							\
        for (I_LOC=0;I_LOC<NL;I_LOC++) 					\
            { X[I_LOC]=(double *)calloc(NP,sizeof(**X));		\
        			MEM_ERR_IMAIO(X[I_LOC]); }    }

#define FREE_MMAP(X,NP,NL)							\
	{ int I_LOC;							\
	for (I_LOC=0;I_LOC<NL;I_LOC++)					\
		free(X[I_LOC]);						\
	free(X);							\
	}

/* entre sortie en mode flash (ca fait luxe) */ 

#define CHARIMA(FIC,BUFF) {	FILE *FP; int I,NP,NL,NBM=1,NBF=1;\
        FP=FRMT(FIC,&NP,&NL);						\
        for(I=0;I<NL;I++)						\
             LECIMA(FP,BUFF[I],&NP,NULL,&NBM,&NBF);			\
        fclose(FP); }	
 
#define CHARIMA8(FIC,BUFF,NP,NL) {	FILE *FP; int I,NBM=1,NBF=1;    \
        FP=FRMT(FIC,&NP,&NL);						\
	MALLOC(BUFF,NP,NL);						\
        for(I=0;I<NL;I++)						\
             LECIMA(FP,BUFF[I],&NP,NULL,&NBM,&NBF);			\
        fclose(FP); }	 
        			
	
#define CHARIMA16(FIC,BUFF,NX,NY) { TIMAGE TIMA_LOC;			\
	set_ima_filename(&TIMA_LOC,"",FIC);				\
	if (open_ima_in(&TIMA_LOC,0)==0)				\
  		erreur("CHARIMA16","Impossible d'ouvrir",FILE_ERR);	\
  	BUFF = (PIXRAD **)charima16(&TIMA_LOC);				\
  	NX = IMA_NP(&TIMA_LOC); NY = IMA_NL(&TIMA_LOC);		\
  	close_ima(&TIMA_LOC); }			
							

#define VIDIMA(FIC,BUFF,NP,NL) {FILE *FP; int I,NBM=1,NBF=1;		\
        FP=ouvre_sortie(FIC,&NP,&NL);					\
        for(I=0;I<NL;I++)						\
             ECRIMA(FP,BUFF[I],&NP,NULL,&NBM,&NBF);			\
        fclose(FP); }

#define VIDIMA16(FIC,BUFF,NP,NL) 					\
	{FILE *FP; int I,NBM=1,NBF=1,J_LOC; PIXRAD R_LOC ;		\
        FP=ouvre_sortie16(FIC,&NP,&NL);					\
        for(I=0;I<NL;I++)						\
             for (J_LOC=0;J_LOC<NP;J_LOC++)				\
               { R_LOC=htons(BUFF[I][J_LOC]);fwrite(&R_LOC,1,2,FP); }	\
        fclose(FP); }
        
#define VIDIMARVB(FIC,BUFF,NP,NL) 				\
	vidimarvb(FIC,BUFF,NP,NL)
	
	
#define MAXIMA(MIN,MAX,IMA,NP,NL)				\
	{							\
	int IMAX,JMAX;						\
	MAX = IMA[0][0]; MIN= IMA[0][0];			\
	for (IMAX=0;IMAX<NL;IMAX++)				\
	  for (JMAX=0;JMAX<NP;JMAX++)				\
	    {							\
	      if (IMA[IMAX][JMAX]>MAX) MAX = IMA[IMAX][JMAX];	\
	      if (IMA[IMAX][JMAX]<MIN) MIN = IMA[IMAX][JMAX];	\
	    }							\
	}
	
 
	
#define COPIMA16TO8(X,Y,NP,NL)  				        \
        { int I_LOC, J_LOC;						\
        for (I_LOC=0;I_LOC<NL;I_LOC++) 					\
          for (J_LOC=0; J_LOC<NP;J_LOC++)				\
            { X[I_LOC][J_LOC]=(PIXEL)Y[I_LOC][J_LOC];			\
        			 } 	}

#define COPIMA(X,Y,NP,NL)  				        \
        { int I_LOC, J_LOC;						\
        for (I_LOC=0;I_LOC<NL;I_LOC++) 					\
          for (J_LOC=0; J_LOC<NP;J_LOC++)				\
            { X[I_LOC][J_LOC]=Y[I_LOC][J_LOC];			\
        			 } 	}

#define COPIMA8TO16(X,Y,NP,NL)  				        \
        { int I_LOC, J_LOC;						\
        for (I_LOC=0;I_LOC<NL;I_LOC++) 					\
          for (J_LOC=0; J_LOC<NP;J_LOC++)				\
            { X[I_LOC][J_LOC]=(PIXRAD)Y[I_LOC][J_LOC];			\
        			 } 	}


typedef PIXEL PIXRVB[3];


typedef struct 
		{
 		  FILE *fp;	/* pointeur sur fichier */
 		  long np,nl;   /* taille x et y */
 		  long nbm,nbf; /* nombre d'octet en memoire */
 		  long plan;	/* nombre de plan */
 		  void *buffer; /* un buffer	*/
 		  unsigned char **pix_8;   /* tableau 8 bits */
 		  unsigned short **pix_16;  /* tableau 16 bits */
 		  unsigned char  ***pix_rvb;  /* tableau RVB ou imc */
 		  long type;	  /* type de l'image */
 		  char name[512]; /* Le nom de fichier associe */
 		  long pix_max;
 		  char sun_c;       /* codage sun */
 		}TIMAGE;
 		
typedef struct
                {
                  PIXEL r[PIXEL_MAX];
                  PIXEL v[PIXEL_MAX];
                  PIXEL b[PIXEL_MAX];
                  int nb_colors;
                }TCMAP;

/* macro */


#define IMA_DES(IMAGED)		((TIMAGE *)IMAGED)->fp
#define IMA_NP(IMAGED)		((TIMAGE *)IMAGED)->np
#define IMA_NL(IMAGED)		((TIMAGE *)IMAGED)->nl
#define IMA_NBM(IMAGED)		((TIMAGE *)IMAGED)->nbm
#define IMA_NBF(IMAGED)		((TIMAGE *)IMAGED)->nbf
#define IMA_PLAN(IMAGED)	((TIMAGE *)IMAGED)->plan
#define IMA_BUFFER(IMAGED)	((TIMAGE *)IMAGED)->buffer
#define IMA_TYPE(IMAGED)	((TIMAGE *)IMAGED)->type
#define IMA_NAME(IMAGED)	((TIMAGE *)IMAGED)->name
#define IMA_PIX_MAX(IMAGED)	((TIMAGE *)IMAGED)->pix_max
#define IMA_CODE(IMAGED)	((TIMAGE *)IMAGED)->sun_c



#define INIT_IMA(IMAGED,NAME,NP,NL,NBM,NBF,PLAN,TYPE,BUFFER)	\
        {							\
	  strcpy(IMA_NAME(IMAGED), NAME);			\
	  IMA_NP(IMAGED) = NP;					\
	  IMA_NL(IMAGED) = NL;					\
	  IMA_NBM(IMAGED) = NBM;				\
	  IMA_NBF(IMAGED) = NBF;				\
	  IMA_PLAN(IMAGED) = PLAN;				\
	  IMA_TYPE(IMAGED) = TYPE;				\
	  IMA_BUFFER(IMAGED) = BUFFER;				\
	  switch (TYPE)						\
            {							\
		case TEL_IMA :  IMA_PIX_MAX(IMAGED) = 256; 	\
				IMA_CODE(IMAGED) = 1;		\
			  break;				\
		case TEL_IMW: IMA_PIX_MAX(IMAGED) = 65536;	\
				IMA_CODE(IMAGED) = 1;		\
	 		  break;				\
		case TEL_RVB: IMA_PIX_MAX(IMAGED) = 256;	\
				IMA_CODE(IMAGED) = 1;		\
			  break;				\
		case TEL_IMC: IMA_PIX_MAX(IMAGED) = 256;	\
				IMA_CODE(IMAGED) = 1;		\
			  break;				\
		default: IMA_PIX_MAX(IMAGED) = 256;		\
			 IMA_CODE(IMAGED) = 1;			\
                          break;				\
             } 							\
       }

#define INIT_CMPA_GREY8(CMAP_LOC)				\
	{							\
	  int I_LOC;						\
	  for (I_LOC=0;I_LOC<PIXEL_MAX;I_LOC++)			\
	    {							\
	    CMAP_LOC.r[I_LOC] = I_LOC;				\
	    CMAP_LOC.v[I_LOC] = I_LOC;				\
	    CMAP_LOC.b[I_LOC] = I_LOC;				\
	    }							\
	  CMAP_LOC.nb_colors = PIXEL_MAX;    			\
	}

/* prototypes */

FILE *FRMT();
FILE *ouvre_sortie();
FILE *ouvre_sortie16();
int test_ima();
void set_ima_filename();


/* Fonction specialise */

char *ima_basename(char *res, char *filename);
/***********************************************************
*      BUT : enleve l'extention au nom de fichier pour     *
*            .ima, .rvb, .imw et .dim                      *
*      PAR:  filename                                      *
*             res le resulat                               *
*	RET:  l'adresse de res                             *
************************************************************/

/* image 16 bit */

PIXRAD **charima16();

/* image rvb */

PIXRVB **charimarvb(char *file, int *np, int *nl);
/***********************************************************
*	BUT : charger une image rvb                        *
************************************************************/
int vidimarvb(char *file,PIXRVB **rvb,int np,int nl);


