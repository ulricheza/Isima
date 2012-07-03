/**
 * \file Cluster.hpp
 * \brief Fichier de declaration de la classe Cluster
 * \author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 * \version 1.0
 * \date 5 decembre 2011
 *
 */

#ifndef CLUSTER_H
#define	CLUSTER_H

#include "CImg.h"

using namespace cimg_library;

/**
 * \class Cluster
 * \brief Classe modelisant un cluster utilise dans l'algorithme du k-means
 * 
 */
class Cluster {
public:
    Cluster();
    virtual ~Cluster();
    
    //Methodes
    void  addFeature(float brillance, float normeFlotOptique);
    void  addPixel(int x, int y);
    void  reinitialiser();
    void  setNouveauxCentre();
    void  setParametres(int width,int height, float brillance, float normeFlotOptique);
    float distance(float brillance, float normeFlotOptique, float brillanceMax, float normeFlotOptiqueMax);
    
    /**
     * \fn float getBrillance()
     * \brief getter de la brillance moyenne du cluster
     * \return La brillance du centre du cluster.
     * 
     */    
    float getBrillance() { return _brillance; }
    
    /**
     * \fn float getNormeFlotOptique()
     * \brief getter de la norme du flot optique moyenne du cluster
     * \return La norme du flot optique du centre du cluster
     * 
     */
    float getNormeFlotOptique() { return _normeFlotOptique; }
    
    /**
     * \fn CImg<> getImage()
     * \brief getter de l'image representative du cluster
     * \return l'image representant le cluster
     * 
     * L'image retourne est une copie, donc pas de soucis si delete du cluster.
     * 
     */
    CImg<> getImage() { return _cluster; }
    
private:
    
    CImg<unsigned char> _cluster;   //Image representative du cluster
    
    float _brillance;               //Brillance du centre du cluster
    float _brillanceCumulee;        //Brillance culumee des elements du cluster
    float _normeFlotOptique;        //Norme du flot optique 
    float _normeFlotOptiqueCumulee; //Norme du flot optique cumule des elements du cluster
    int   _nbElement;               //Nombre des elements du cluster
    
};

#endif	/* CLUSTER_H */

