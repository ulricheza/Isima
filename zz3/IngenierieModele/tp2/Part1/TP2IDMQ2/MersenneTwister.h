/**
 * \file   MersenneTwister.h
 * \author Maxime Escourbiac
 * \brief  Fichier de declaration de la classe MersenneTwister
 * \date   31 mai 2011
 *
 * Mersenne Twister encapsule dans une classe.
 */


#ifndef __MERSENNETWISTER_H__
#define	__MERSENNETWISTER_H__

/* Period parameters */
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

/**
 * \class MersenneTwister
 * \brief High-Performance Generator
 */
class MersenneTwister
{
private:
    unsigned long _mt[N]; /* the array for the state vector  */
    int           _mti;   /* mti==N+1 means mt[N] is not initialized */

public :
    MersenneTwister();
    unsigned long GenerateInt32();
    double        GenerateDouble();
    void          Init(unsigned long);
    void          Init_by_array(unsigned long init_key[], int key_length);
};
#endif	/* _MT19937AR_H */

