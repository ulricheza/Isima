#ifndef DYNAMIC_H_INCLUDED
#define DYNAMIC_H_INCLUDED

#include <boost/preprocessor/seq/enum.hpp>


/*
   Macro pour construire des objets sur le tas (allocation dynamique),
   plus ou moins l'equivalent du 'new' en C++.
   Exemple d'utilisation :
     Objet * ptrObjet = NEW( Objet, (param1)(param2)(param3) );
 */
#define NEW( Type, params ) \
    LeMeta##Type.init( ( Type * ) malloc( sizeof( Type ) ), BOOST_PP_SEQ_ENUM( params ) )


/*
  Macro pour detruire les objets alloues dynamiquement, plus ou moins
  l'equivalent du 'delete' en C++.
  Fonctionne avec destructeur virtuel ou non-virtuel.
 */
#define DELETE( ptr ) \
    ptr->maClasse->reset( ptr ), free( ptr )


#endif /* DYNAMIC_H_INCLUDED */
