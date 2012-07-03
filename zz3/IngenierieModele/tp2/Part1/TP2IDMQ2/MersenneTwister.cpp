/**
 * \file   MersenneTwister.cpp
 * \author Maxime Escourbiac
 * \brief  Implement file of MersenneTwister class
 * \date   31 may 2011
 *
 */

/* 
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.

   Before using, initialize the state by using init_genrand(seed)  
   or init_by_array(init_key, key_length).

   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.                          

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote 
        products derived from this software without specific prior written 
        permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


   Any feedback is very welcome.
   http://www.math.sci.hiroshima-u.ac.jp/~m-mat/_mt/emt.html
   email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
*/

//*****************************************************************************
//This is modified for using in a Cpp project.
//The generator is now a class.
//Adapted by Maxime ESCOURBIAC
// 05/31/2011
//*****************************************************************************

#include "MersenneTwister.h"

/**
 * \fn MersenneTwister::MersenneTwister()
 * Constructor of MersenneTwister Class
 */
MersenneTwister::MersenneTwister()
{
}


/**
 * \fn void MersenneTwister::Init(unsigned long s)
 * \brief Initialize the generator with a seed
 * \param s seed
 *
 */
void MersenneTwister::Init(unsigned long s)
{
    _mt[0]= s & 0xffffffffUL;
    for (_mti=1; _mti<N; ++_mti)
    {
        _mt[_mti] =
	    (1812433253UL * (_mt[_mti-1] ^ (_mt[_mti-1] >> 30)) + _mti);
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array _mt[].                       */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        _mt[_mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}

/**
 * \fn unsigned long MersenneTwister::GenerateInt32()
 * \brief generates a random number on [0,0xffffffff]-interval
 * \return a random integer on [0,0xffffffff]-interval
 */
unsigned long MersenneTwister::GenerateInt32()
{
    unsigned long y;
    static unsigned long mag01[2]={0x0UL, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (_mti >= N) { /* generate N words at one time */
        int kk;

        if (_mti == N+1)   /* if init_genrand() has not been called, */
            Init(5489UL); /* a default initial seed is used */

        for (kk=0;kk<N-M;kk++) {
            y = (_mt[kk]&UPPER_MASK)|(_mt[kk+1]&LOWER_MASK);
            _mt[kk] = _mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<N-1;kk++) {
            y = (_mt[kk]&UPPER_MASK)|(_mt[kk+1]&LOWER_MASK);
            _mt[kk] = _mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (_mt[N-1]&UPPER_MASK)|(_mt[0]&LOWER_MASK);
        _mt[N-1] = _mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        _mti = 0;
    }
  
    y = _mt[_mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

/**
 * \fn double MersenneTwister::GenerateDouble()
 * \brief generates a random number on [0,1)-real-interval
 * \return a random number on [0,1)-real-interval
 * 
 */
double MersenneTwister::GenerateDouble()
{
    return GenerateInt32()*(1.0/4294967296.0);
    /* divided by 2^32 */
}

/**
 * \fn void MersenneTwister::init_by_array(unsigned long init_key[], int key_length)
 * \brief Methode d'initialisation du MT par un tableau
 * \param init_key Tableau d'initialisation
 * \param key_length nombre de clé generatoire
 *
 *
 * initialize by an array with array-length
 * init_key is the array for initializing keys
 * key_length is its length
 * slight change for C++, 2004/2/26
 *
 */
void MersenneTwister::Init_by_array(unsigned long init_key[], int key_length)
{
    int i, j, k;
    Init(19650218UL);
    i=1; j=0;
    k = (N>key_length ? N : key_length);
    for (; k; k--) {
        _mt[i] = (_mt[i] ^ ((_mt[i-1] ^ (_mt[i-1] >> 30)) * 1664525UL))
          + init_key[j] + j; /* non linear */
        _mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++; j++;
        if (i>=N) { _mt[0] = _mt[N-1]; i=1; }
        if (j>=key_length) j=0;
    }
    for (k=N-1; k; k--) {
        _mt[i] = (_mt[i] ^ ((_mt[i-1] ^ (_mt[i-1] >> 30)) * 1566083941UL))
          - i; /* non linear */
        _mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++;
        if (i>=N) { _mt[0] = _mt[N-1]; i=1; }
    }

    _mt[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */
}
