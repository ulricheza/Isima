/**
 * \file ClusterSpatioTemporel.hpp
 * \brief Fichier de declaration de la classe ClusterSpatioTemporel
 * \author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 * \version 1.0
 * \date 5 decembre 2011
 *
 */

#ifndef CLUSTERINGSPATIOTEMPOREL_HPP
#define	CLUSTERINGSPATIOTEMPOREL_HPP

#include "CImg.h"
#include "Cluster.hpp"

#define LAMBDA 10.0
#define ITER_HORN_SCHUNK 50

using namespace cimg_library;

class ClusteringSpatioTemporel {

public:
    ClusteringSpatioTemporel();
    ClusteringSpatioTemporel(char * img1, char * img2);
    virtual ~ClusteringSpatioTemporel();
      
    void   clustering();
    
    /**
     * \fn CImg<> getImage(int cluster)
     * \brief Retourne l'image d'un cluster selectionne
     * \param cluster Indice du clusteur selectionne
     * \return L'image representant un cluster
     * 
     */
    CImg<> getImage(int cluster) { return _cluster[cluster].getImage(); }
    
    /**
     * \fn CImg<> getImageOriginale()
     * \brief Getter de l'image originale
     * \return L'image originale de test.
     */
    CImg<> getImageOriginale() { return _sequence; }
    
    /**
     * \fn CImg<> getNormeFlotOptique()
     * \brief Getter de l'image de la norme du flot optique
     * \return L'image representant la norme du flot optique
     */
    CImg<> getNormeFlotOptique() { return _normeFlotOptique; }
 
private:
    
    CImg<>  _sequence;
    CImg<>  _normeFlotOptique;
    Cluster _cluster[4];
    
    //Methodes privees
    void   HornSchunck();
    short  appartenanceCluster(float brillance, float normeFlotOptique, float brillanceMax, float normeFlotOptiqueMax);

};

#endif	/* CLUSTERINGSPATIOTEMPOREL_HPP */
