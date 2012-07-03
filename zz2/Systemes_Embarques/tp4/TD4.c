#include "bibliotheque.h"

void main()
{
     unsigned short phrase[14]={19,17,18,17,18,19,1,5,19,13,15,10,13,19};
     unsigned int i;
     unsigned int j;
     unsigned int k;
     unsigned int val[4];
     /*Initialisation des afficheurs et des diodes*/
     AFF_Init();
     LED_B_Init();
     LED_B_Init();
     while(1)
     {
         for(j=0;j<4;j++)
         {
             k = i + j;
             if(k>14) k-=14;
             val[j] = phrase[k];
         }
         AFF(val[0],val[1],val[2],val[3],2000);
         i++;
         if(i>14) i=0;
     }
}