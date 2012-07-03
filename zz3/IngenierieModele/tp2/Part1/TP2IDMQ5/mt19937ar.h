/*
 * \file  mt19937ar.h
 * \author Maxime Escourbiac
 * \brief fichier d'en-tete pour le mersenne twister
 * Created on 14 décembre 2010, 23:31
 *  Ce fichier a ete pour le tp il permet d'encapsuler le generateur au projet
 */

#ifndef __MT19937AR_H__
#define	__MT19937AR_H__

/* Period parameters */
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

void          init_genrand (unsigned long );
void          init_by_array(unsigned long *, int);
unsigned long genrand_int32(void);
double        genrand_real2(void);

#endif	/* _MT19937AR_H */
