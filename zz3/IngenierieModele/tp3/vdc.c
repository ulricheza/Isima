/* ------------------------------------------------------------------------- */
/* vdc.c          Séquence de van der Corput sequence                        */
/*                                                                           */
/* 1ere cycle (le 0 est exclu)      2nd cycle                                */
/* 0.50000,                         0.25000, 0.75000,                        */
/*                                                                           */
/* 3ème cycle                                                                */
/* 0.12500, 0.62500, 0.37500, 0.87500,                                       */
/*                                                                           */
/* 4ème cycle                                                                */
/* 0.06250, 0.56250, 0.31250, 0.81250, 0.18750, 0.68750, 0.43750, 0.93750    */
/*                                                                           */
/*                              (C) Gnu Public Licence D.Hill - 30/5/2007    */
/* ------------------------------------------------------------------------- */


long long MirroirPuissances[24][2] =
{
   {                   1LL, 140737488355328LL},   /*               1 - 2e47 */
   {                   2LL,  70368744177664LL},   /*               2 - 2e46 */
   {                   4LL,  35184372088832LL},   /*               4 - 2e45 */
   {                   8LL,  17592186044416LL},   /*               8 - 2e44 */
   {                  16LL,   8796093022208LL},   /*              16 - 2e43 */
   {                  32LL,   4398046511104LL},   /*              32 - 2e42 */
   {                  64LL,   2199023255552LL},   /*              64 - 2e41 */
   {                 128LL,   1099511627776LL},   /*             128 - 2e40 */
   {                 256LL,    549755813888LL},   /*             256 - 2e39 */
   {                 512LL,    274877906944LL},   /*             512 - 2e38 */
   {                1024LL,    137438953472LL},   /*    2e10    1024 - 2e37 */
   {                2048LL,     68719476736LL},   /*            2048 - 2e36 */
   {                4096LL,     34359738368LL},   /*            4096 - 2e35 */
   {                9192LL,     17179869184LL},   /*            9192 - 2e34 */
   {               16384LL,      8589934592LL},   /*           16384 - 2e33 */
   {               32768LL,     4294967296LL},    /*           32768 - 2e32 */
   {               65536LL,     2147483648LL},    /*           65536 - 2e31 */
   {              131072LL,     1073741824LL},    /*          131072 - 2e30 */
   {              262144LL,      536870912LL},    /*          262144 - 2e29 */
   {              524288LL,      268435456LL},    /*          524288 - 2e28 */
   {             1048576LL,      134217728LL},    /*    2e20 1048576 - 2e27 */
   {             2097152LL,       67108864LL},    /*         2097152 - 2e26 */
   {             4194304LL,       33554432LL},    /*         4194304 - 2e25 */
   {             8388608LL,       16777216LL}     /*    2e23 8388608 - 2e24 */
};


/* ------------------------------------------------------------------------- */
/* vdC32         Algorithme de Van der Corput en base 2 sur 32 bits adapté   */
/*                                                                           */
/* En entrée : l'indice du nombre que l'on veut (son statut dans la serie !) */
/*                                                                           */
/* Algo adapté à partir de l'article de Kollig & Keller, Eurographics 2002,  */
/* Volume 21, numero 3, 7 p.                                                 */
/* ------------------------------------------------------------------------- */

double vdC32(unsigned int bits)
{
   bits = ( bits << 16) | ( bits >> 16);
   bits = ((bits & 0x00ff00ff) << 8) | ((bits & 0xff00ff00) >> 8);
   bits = ((bits & 0x0f0f0f0f) << 4) | ((bits & 0xf0f0f0f0) >> 4);
   bits = ((bits & 0x33333333) << 2) | ((bits & 0xcccccccc) >> 2);
   bits = ((bits & 0x55555555) << 1) | ((bits & 0xaaaaaaaa) >> 1);

   return (double) bits / 4294967296.0;
}

/* ------------------------------------------------------------------------- */
/* vdC48     Algorithme de Van der Corput en base 2 non optimisé             */
/*                                                                           */
/* En entrée : l'indice du nombre que l'on veut (son statut dans la serie !) */
/*                                                                           */
/* Algo basique utilisant un mirroir de bits                                 */
/*                                                                           */
/* En Sortie : Attention limite a 2e48 nombres : + de 281474 milliards       */
/* ------------------------------------------------------------------------- */

double vdC48(long long bits)
{
   long long result = 0;
   int       i      = 0;

   // Possibilité d'unrolling + remplacement des tableaus par des constantes
   // pour optimiser

   for(i = 0 ; i < 24 ; i++)
   {
       if ( (bits & MirroirPuissances[i][0]) == MirroirPuissances[i][0]) 
       {
          result |= MirroirPuissances[i][1];
       }
   }

   return (double) result / 281474976710656LL;
}

/* ---------------------------------------------------------------------- */

int main()
{
   unsigned long long il = 0;

   printf("Sl %d\n", sizeof(long long));

   for(il = 1; il < 16 ; il++)
   {
      printf("%0.15f\n", vdC48(il));
   }
   puts("");

   /* Mise en évidence des correlations apres 1 milliard de tirage */
   for(il = 1000000000LL; il < 1000000016LL ; il++)
   {
      printf("%0.15f\n", vdC48(il));
   }
   puts("");

   /* Test pour 10000 milliards */
   for(il = 10000000000000LL; il < 10000000000016LL ; il++)
   {
       printf("%0.15f\n", vdC48(il));
   }
   puts("");

   return 0;
}
/* ---------------------------------------------------------------------- */

