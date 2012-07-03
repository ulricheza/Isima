/*test sur un algo de tirage sans remise*/




#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*on se propose de tirer une valeur sans remise dans un intervalle donne par l'user   */
/*Prenons le cas entre 0 et 10 pour expliquer                                         */
/*le principe est de succesivement tire un nombre entre 0 et i ou i decroit           */
/*ce nombre tiré servira a chercher la valeur dans le tableau                         */
/*apres avoir tiré le nombre on stocke tab[rand] dans result et on ecrase cette valeur*/
/*par la derniere valeur du tableau restant ici tab[i-1]                              */

int main(int argc, char * argv[])
{
    int i,result,temp,min,max,j;
    int tab[100];
    printf("min?\n");
    scanf("%d",&min);
    printf("max?\n");
    scanf("%d",&max);
    printf("on va tirer les nombres entre %d et %d sans reminse \n",min,max);
    for(i=0;i<(max-min)+1;i++)
       tab[i]= min + i;
    srand(time(0));
    j=(max-min)+1;
    for(i=0;i<(max-min)+1;i++)
    {
       temp = rand()%j;
       result = tab[temp];
       tab[temp] = tab[j-1];
       printf(" pour i = %d on tire %d \n",i,result);
       --j;
    }
    system("pause");
    return 0;
}
