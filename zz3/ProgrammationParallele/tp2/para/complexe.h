typedef struct complexe {
    double re, im;
} complexe_t;


/* -------------------------------------------------------------------------- */
/* Prototypes des fonctions                                                   */
/* -------------------------------------------------------------------------- */

void         mult_comp( complexe_t,  complexe_t,  complexe_t *);

void         mult_scal(double, complexe_t, complexe_t *);

void         somme(complexe_t, complexe_t, complexe_t *);

double       norme2(complexe_t);

void         division(complexe_t, complexe_t, complexe_t *);
