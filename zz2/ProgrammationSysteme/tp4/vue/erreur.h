/****************************************************************
*	BUT : Gestion des ERREURS				*
*	AUT : GOUINAUD Christophe				*
*	DAT : 11/10/93						*
*****************************************************************/

#define CG_ERREUR 1
#define OKDAC     1

/* Codes d'erreurs */


#define MEM_ERR		100
#define FILE_ERR	200

/* Macro de verification des pointeurs */

#define VPOINTEUR( who, point )					\
  {								\
    if (!(point))						\
      {								\
        erreur(who,"Probleme d'allocation",MEM_ERR);	        \
      }								\
  }

#define VFILE( who, point )					\
  {								\
    if (!(point))						\
      {								\
        erreur(who,"Probleme d'ouverture de ficher",MEM_ERR);   \
      }								\
  }
  
#ifdef __SUNPRO_C  
#define irint(x) 				\
    (int)floor(x)
#endif

#ifdef __GNUC__ 
#define irint(x)                                \
    (int)floor(x)
#endif

/* FIN DE ERREUR.H */								
double drand48();
void erreur();
