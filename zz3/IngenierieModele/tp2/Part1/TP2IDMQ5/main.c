/* 
 * File:   main.c
 * Author: maxime
 *
 * Created on 3 novembre 2011, 23:43
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>



#include "mt19937ar.h"

void ecritureFichier(int nbPoint, int nbReplication);
void lectureFichier(int nbPoint, int nbReplication);
/*
 * 
 */
int main(int argc, char** argv) {

    //Declaration des paramtres de la simulation
    int nbPoint;
    int nbReplication;

    /*Initialisation du MT*/
    unsigned long inittab[4]={0x123, 0x234, 0x345, 0x456}, length=4;
    init_by_array(inittab, length);

    //Variables servant pour le calcul de performance
    //Attention code fonctionnant que sur Linux/Unix.
    struct timeval tv1,tv2;
    long long tempsS,tempUS;

    printf("Combien de point?\n");
    scanf("%d",&nbPoint);

    printf("Combien de replications?\n");
    scanf("%d",&nbReplication);


    gettimeofday(&tv1,NULL);

    ecritureFichier(nbPoint,nbReplication);

    gettimeofday(&tv2,NULL);
    tempsS  =(tv2.tv_sec-tv1.tv_sec);
    tempUS =(tv2.tv_usec-tv1.tv_usec);
    printf("temps d'ecriture du fichier binaire : %lld s %lld us \n", tempsS, tempUS);


    gettimeofday(&tv1,NULL);

    lectureFichier(nbPoint,nbReplication);

    gettimeofday(&tv2,NULL);
    tempsS  =(tv2.tv_sec-tv1.tv_sec);
    tempUS =(tv2.tv_usec-tv1.tv_usec);
    printf("temps d'execution de la simulation : %lld s %lld us \n", tempsS, tempUS);
    
    return (EXIT_SUCCESS);
}

/**
 * \fn void ecritureFichier(int nbPoint, int nbReplication)
 * \brief Fonction d'ecriture des nombres aleatoires tire par le Mersenne Twister
 * \param nbPoint nombre de points a tirer
 * \param nbReplication Nombre de replication a effectuer pour la simulation
 *
 */
void ecritureFichier(int nbPoint, int nbReplication)
{
    int     i;
    int     nbElement = nbPoint * nbReplication * 2;
    float * tabMT;
    FILE  * MTBinary;

    

    /*Allocation tableau*/
    tabMT = (float *) malloc( nbElement * sizeof(float) );

    if(!tabMT)
    {
        fprintf(stderr,"Erreur allocation memoire\n");
        exit(EXIT_FAILURE);
    }

    /*On remplit le tableau de nombres generes*/
    for(i = 0; i < nbElement ; ++i)
    {
        tabMT[i] = genrand_real2();
    }

    MTBinary = fopen("mt.dat","wb");

    if(!MTBinary)
    {
        fprintf(stderr,"Erreur d'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }

    /*ecriture des donnees en binaire*/
    fwrite(tabMT,sizeof(float),nbElement,MTBinary);
    fclose(MTBinary);
    free(tabMT);
}

void lectureFichier(int nbPoint, int nbReplication)
{
    float * tabMT;
    int     file,i,j,valide,indexTab = 0;
    double  piIntermediate,moy,x,y;

    /*ouverture du fichier binaire*/
    file = open("mt.dat",O_RDWR);
    if(file < 0)
    {
        fprintf(stderr,"Erreur de lecture du fichier\n");
        exit(EXIT_FAILURE);
    }

    /*Mappage du fichier dans la zone memoire*/
    tabMT = (float *) mmap(NULL,nbPoint * nbReplication * 2*sizeof(float),PROT_READ,MAP_PRIVATE,file,0);

    /*Test si le mappage a marche*/
    if(tabMT == (float *) MAP_FAILED)
    {
        fprintf(stderr,"Erreur dans le mmap\n");
        exit(EXIT_FAILURE);
    }

    close(file);

    /*Approximation de pi*/
    for(i=0;i<nbReplication;++i)
    {
        printf("experience %d:\n",i);
        valide = 0;
        for(j=0;j<nbPoint;++j)
        {
           x = tabMT[indexTab++];
           y = tabMT[indexTab++];;
           if(sqrt(x*x+y*y)<= 1.0)
              ++valide;
        }
        piIntermediate = 4.0*((float)valide/(float)nbPoint);
        printf("Evaluation de pi : %lf \n",piIntermediate);
        moy += piIntermediate;
    }

    printf("------------------------------------------\n");
    printf("------------------------------------------\n");
    printf("exploitation des resultat\n");
    moy /= (float)nbReplication;
    printf("La moyenne est de : %lf \n",moy);
}

