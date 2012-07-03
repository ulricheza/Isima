

#include <stdio.h>
#include <stdlib.h>
#include <math.h>



/*definition de la liste chainée des expressions*/

typedef struct expr 
{
  double evaluation;
  int id;
  struct expr * suivant ;
}expr_t;

/*definition de la liste chainée des operande  */
typedef struct ope
{
  int id;
  struct ope * suivant ; 
}ope_t;


void calcul(char * , double , double , int * );

