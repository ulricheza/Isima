/* 
 * File:   ClusteringSpatioTemporel.cpp
 * Author: maxime
 * 
 * Created on 5 décembre 2011, 20:29
 */

#include <stdio.h>
#include <time.h>
#include <sys/time.h>

#include "ClusteringSpatioTemporel.hpp"

ClusteringSpatioTemporel::ClusteringSpatioTemporel()
{
}

ClusteringSpatioTemporel::ClusteringSpatioTemporel(char * img1, char * img2)
{
    //Chargement des images
    _sequence = CImg<>(img1).channel(0);
    _sequence.append(CImg<>(img2).channel(0),'z');
    
    //calcul de la norme du flot optique
    HornSchunck();
}

ClusteringSpatioTemporel::~ClusteringSpatioTemporel() {
}

/**
 * \fn void ClusteringSpatioTemporel::HornSchunck()
 * \brief  Methode de calcul de la norme euclidienne du flot optique de la sequence d'image. 
 * 
 * L'algorithme utilisé ici est l'algorithme de Horn et Schunk qui est explique
 * dans le sujet du tp6.
 * 
 */
void ClusteringSpatioTemporel::HornSchunck()
{
    CImg<> champVecteurVitesse(_sequence.width(),_sequence.height(),1,2,0);
    CImg<> champMoyen;
    CImg<float> moyenneur(3,3,1,1,1./9.); //Filtrage
    
    //Variables servant pour le calcul de performance
    //Attention code fonctionnant que sur Linux/Unix.
    struct timeval tv1,tv2;
    long long tempsS,tempUS;
    
    gettimeofday(&tv1,NULL);
    
    //On redimensionne l'image representant le flot optique
    _normeFlotOptique.resize(_sequence.width(),_sequence.height());
    
    // Calcul des gradients de l'image
    CImgList<> gradient = _sequence.get_gradient("xyz",0);

    for(int k=0;k<ITER_HORN_SCHUNK;++k)
    {
        // Calcul des versions moyennees du champ
        champMoyen = champVecteurVitesse.get_convolve(moyenneur);

        cimg_forXY(champVecteurVitesse,x,y)
        {
            float temp = (gradient[0](x,y) * champMoyen(x,y,0) + gradient[1](x,y) * champMoyen(x,y,1) + gradient[2](x,y) )
                         / ( LAMBDA * LAMBDA + gradient[0](x,y) * gradient[0](x,y) + gradient[1](x,y) * gradient[1](x,y));
         
            champVecteurVitesse(x,y,0)   = champMoyen(x,y,0) - gradient[0](x,y) * temp;
            champVecteurVitesse(x,y,1)   = champMoyen(x,y,1) - gradient[1](x,y) * temp;
         
            //On preferera calculer la norme euclidienne manuellement qu'avec la methode get_norm()
            _normeFlotOptique(x,y) = sqrt(champVecteurVitesse(x,y,0) * champVecteurVitesse(x,y,0) +
                                          champVecteurVitesse(x,y,1) * champVecteurVitesse(x,y,1));
        }
    }
    
    gettimeofday(&tv2,NULL);
    tempsS  =(tv2.tv_sec-tv1.tv_sec);
    tempUS =(tv2.tv_usec-tv1.tv_usec);
    printf("temps de calcul de la norme de flot optique : %lld s %lld us \n", tempsS, tempUS);
}

/**
 * \fn short ClusteringSpatioTemporel::appartenanceCluster(float brillance, float normeFlotOptique, float brillanceMax, float normeFlotOptiqueMax)
 * \brief Determine l'appartenance d'un point a un cluster.
 * \param brillance Brillance du point
 * \param normeFlotOptique Norme du flot optique du point
 * \param brillanceMax Brillance maximale presente sur l'image.
 * \param normeFlotOptiqueMax Norme du flot optique maxime present sur l'image.
 * \return indice du cluster auquel appartient le point.
 * 
 */
short ClusteringSpatioTemporel::appartenanceCluster(float brillance, float normeFlotOptique, float brillanceMax, float normeFlotOptiqueMax)
{
    float distanceMin = 100000000000.0;
    float distanceTemp;
    short cluster = -1;
    
    for(int i = 0; i < 4 ; ++i)
    {
        //calcul de la distance entre le centre du cluster i et le point calcule
        distanceTemp = _cluster[i].distance(brillance,normeFlotOptique,brillanceMax,normeFlotOptiqueMax);
        if(distanceTemp < distanceMin )
        {
            cluster = (short)i;
            distanceMin = distanceTemp;
        }
    }
    return cluster;
}

/**
 * \fn void ClusteringSpatioTemporel::clustering()
 * \brief Methode de clustering utilisant l'agorithme du K-Means avec k = 4
 * 
 */
void ClusteringSpatioTemporel::clustering()
{
    int      width;                    //Largeur de l'image
    int      height;                   //Hauteur de l'image
    int      nbIter;                   //No;bre d'iteration realise par l'algorithme
    short    cluster;                  //Variable temporaire qui recupere le cluster le plus proche d'un element
    short ** representationClustering; //Representation de l'image selon l'appartenance au cluster
    float    brillance;                //Variable temporaire indiquant la brillance d'un point
    float    norme;                    //Variable temporaire indiquant la norme du flot optique pour un point
    float    brillanceMax;             //Brillance maximale de l'image
    float    normeFLotOptiqueMax;      //Norme du flot optique maximal de l'image
    bool     continuer;                //Variable de test de fin d'algorithme
    
    //Variables servant pour le calcul de performance
    //Attention code fonctionnant que sur Linux/Unix.
    struct timeval tv1,tv2;
    long long tempsS,tempUS;
    
    gettimeofday(&tv1,NULL);
    
    //Initialisation des variables
    width               = _sequence.width();
    height              = _sequence.height();
    nbIter              = 0;
    continuer           = true;
    brillanceMax        = _sequence.max();
    normeFLotOptiqueMax = _normeFlotOptique.max();    
    
    //initialisation des clusters
    _cluster[0].setParametres(width,height,0.0,0.0);    
    _cluster[1].setParametres(width,height,0.0,normeFLotOptiqueMax);
    _cluster[2].setParametres(width,height,brillanceMax,0.0);
    _cluster[3].setParametres(width,height,brillanceMax,normeFLotOptiqueMax);
    
    //Initialisation du tableau representant l'etat du clustering
    representationClustering = new short * [width];
    for(int i = 0; i < width; ++i)
    {
        representationClustering[i] = new short[height];
        for(int j = 0; j < height; ++j)
           representationClustering[i][j] = -1;
    }
             
    
    while(continuer == true)
    {
        continuer = false;
        
        //Reinitialisation des clusters
        _cluster[0].reinitialiser();
        _cluster[1].reinitialiser();
        _cluster[2].reinitialiser();
        _cluster[3].reinitialiser();
        
        for(int i = 0; i < width; ++i)
        {
            for(int j = 0; j < height; ++j)
            {
                brillance = _sequence(i,j);
                norme     = _normeFlotOptique(i,j);
                
                //On calcule a quel centre de cluster le point est le plus proche
                cluster = appartenanceCluster(brillance,norme,brillanceMax,normeFLotOptiqueMax);
                
                //Test si le point a change de cluster
                if(cluster != representationClustering[i][j])
                {
                    continuer = true;
                    representationClustering[i][j] = cluster;
                }
                
                _cluster[cluster].addFeature(brillance,norme);
            }
        }
        
        //On calcule les nouveaux centres de cluster.
        _cluster[0].setNouveauxCentre();
        _cluster[1].setNouveauxCentre();
        _cluster[2].setNouveauxCentre();
        _cluster[3].setNouveauxCentre();
        
        ++nbIter;
    }
    
    //remplissage des cluster
    for(int i = 0; i < width; ++i)
        for(int j = 0; j < height; ++j)
            _cluster[representationClustering[i][j]].addPixel(i,j);
    
    gettimeofday(&tv2,NULL);
    tempsS  =(tv2.tv_sec-tv1.tv_sec);
    tempUS =(tv2.tv_usec-tv1.tv_usec);
    printf("temps de calcul du clustering : %lld s %lld us \nNombre d'iteration du K-Means %d \n", tempsS, tempUS, nbIter);
}
