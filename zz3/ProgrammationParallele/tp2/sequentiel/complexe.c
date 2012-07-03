#include "complexe.h"

/* --------------------------------------------------------- */
/* mult_comp : calcule le produit de deux complexes          */
/*   entrees : "a", "b"  et l'adresse de "c"                 */
/*   sortie  : "c" = a*b                                     */
/* --------------------------------------------------------- */
void  mult_comp( complexe_t a,  complexe_t b,  complexe_t *c)
{
    c->re = a.re * b.re - a.im * b.im;
    c->im = a.re * b.im + a.im * b.re;
}

/* --------------------------------------------------------- */
/* mult_scal : calcule le produit d'un scalaire et d'un      */
/*             complexe                                      */
/*   entrees : le scalaire "a", "b" et l'adresse de "c"      */
/*   sortie  : "c" = a*b                                     */
/* --------------------------------------------------------- */
void  mult_scal(double a, complexe_t b, complexe_t *c)
{
    c->re = b.re * a;
    c->im = b.im * a;
}

/* --------------------------------------------------------- */
/* somme     : effectue l'addition de deux complexes         */
/*   entrees : "a", "b"  et l'adresse de "c"                 */
/*   sortie  : "c" = a+b                                     */
/* --------------------------------------------------------- */
void somme(complexe_t a, complexe_t b, complexe_t *c)
{
    c->re = a.re + b.re;
    c->im = a.im + b.im;
}

/* --------------------------------------------------------- */
/* norme2    : calcule la norme au carre d'un complexes      */
/*   entrees : l'adresse de "a"                              */
/*   sortie  : ||a||^2                                       */
/* --------------------------------------------------------- */
double  norme2(complexe_t a)
{
    return (a.re * a.re + a.im * a.im);
}

/* --------------------------------------------------------- */
/* division  : effectue la division de deux complexes        */
/*   entrees : l'adresse de "a", "b"  et "c"                 */
/*   sortie  : "c" = a/b                                     */
/* --------------------------------------------------------- */
void division(complexe_t a, complexe_t b, complexe_t *c)
{
    double n;

    b.im = -b.im;
    n = norme2(b);
    mult_comp(a,b,c);
    c->re = c->re / n;
    c->im = c->im / n;
}
