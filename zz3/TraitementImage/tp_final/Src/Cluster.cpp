/**
 * \file Cluster.cpp
 * \brief Fichier d'implementation de la classe Cluster
 * \author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 * \version 1.0
 * \date 5 decembre 2011
 *
 */

#include "Cluster.hpp"

/**
 * \fn Cluster::Cluster() 
 * \brief Constructeur par defaut de la classe Cluster
 * 
 */
Cluster::Cluster() 
{
    
}

/**
 * \fn Cluster::~Cluster() 
 * \brief Destructeur par defaut de la classe Cluster
 * 
 */
Cluster::~Cluster() 
{
}

/**
 * \fn void Cluster::setParametres(int width,int height, float brillance, float normeFlotOptique)
 * \brief Constructeur de la classe Cluster
 * \param width Largeur de l'image
 * \param height Hauteur de l'image
 * \param brillance Valeur de la brillance du centre du Cluster
 * \param normeFlotOptique Valeur de la norme du flot optique du centre du Cluster
 *  
 */
void Cluster::setParametres(int width,int height, float brillance, float normeFlotOptique)
{
    _nbElement               = 0;
    _normeFlotOptiqueCumulee = 0.0;
    _brillanceCumulee        = 0.0;
    _brillance               = brillance;
    _normeFlotOptique        = normeFlotOptique;
    
    _cluster.resize(width,height);
    _cluster.fill(0);
}


/**
 * \fn void Cluster::setNouveauxCentre()
 * \brief Calcule le nouveau centre du CLuster en fonction des elements qui le constitue
 */
void Cluster::setNouveauxCentre()
{
    if(_nbElement != 0)
    {    
        _brillance        = _brillanceCumulee / (float) _nbElement;
        _normeFlotOptique = _normeFlotOptiqueCumulee / (float) _nbElement;
    }
}

/**
 * \fn void Cluster::addFeature(float brillance, float normeFlotOptique)
 * \brief Ajout d'un element dans le cluster
 * \param brillance brillance de l'element ajoute
 * \param normeFlotOptique norme du flot optique de l'element ajoute
 * 
 */
void Cluster::addFeature(float brillance, float normeFlotOptique)
{
    _brillanceCumulee        += brillance;
    _normeFlotOptiqueCumulee += normeFlotOptique;
    ++_nbElement;
}

/**
 * \fn void Cluster::addPixel(int x, int y)
 * \brief Ajout d'un pixel dans l'image representant le cluster
 * \param x abssice du pixel
 * \param y coordonnee du pixel
 * 
 */
void Cluster::addPixel(int x, int y)
{
    _cluster(x,y) = 255;
}

/**
 * \fn void Cluster::reinitialiser()
 * \brief Reinitialise le cluster
 * 
 */
void Cluster::reinitialiser()
{
    _brillanceCumulee        = 0.0;
    _normeFlotOptiqueCumulee = 0.0;
    _nbElement               = 0;
}

/**
 * \fn float Cluster::distance(float brillance, float normeFlotOptique, float brillanceMax, float normeFlotOptiqueMax)
 * \brief Calcule la distance entre un point et le centre du cluster
 * \param brillance Brillance du point.
 * \param normeFlotOptique Norme du flot optique du point.
 * \param brillanceMax Brillance maximale presente sur l'image.
 * \param normeFlotOptiqueMax Norme du flot optique maxime present sur l'image.
 * \return la distance entre un point et le centre du cluster
 *
 * on joue sur la distance relative. pour equilibrer les valeurs m et M
 * Le calcul de la racine est pas important car pour tout x,y > 0 : x > y => sqrt(x) > sqrt(y) 
 * 
 */
float Cluster::distance(float brillance, float normeFlotOptique, float brillanceMax, float normeFlotOptiqueMax)
{
    return ( ((_brillance - brillance)*(_brillance - brillance) / brillanceMax) +
             ((_normeFlotOptique - normeFlotOptique)*(_normeFlotOptique - normeFlotOptique) / normeFlotOptiqueMax));             
}
