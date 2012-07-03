#include <stdio.h>

/*premier tp de C */
/* exemple de boucle*/

int fact_rec(int b);

int main()
{
   int a;
   int i;
   int res;
   printf("veuillez rentrer un nombre\n");
   scanf("%d",&a);
   for(i=a;i>0;i--)
   {
      printf("valeur de i == %d\n",i);
   }
   while (i <= a)
   {
       printf("%d x %d == %d\n",i,i,i*i);
       i++;
   }
   printf("mtn calculons la factorielle du nombre donnee\n");
   printf("d'abord de maniere classique\n");
   res = 1;
   for(i=2;i<=a;i++)
   {
       res = res * i;
   }
   printf("fact(%d) == %d \n",a,res);
   printf("puis de maniere recursive\n");
   res = fact_rec(a);
   printf("fact(%d) == %d \n",a,res);
}

int fact_rec(int b)
{  
   int quit = 0;
   if(b==0) 
   {
     quit = 1 ; 
     b = 1 ;
   }
   if(b!=1 && quit != 1)
   {
      b = b * fact_rec(b-1);
   }
   return (b);
   
}
