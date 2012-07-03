/*
 * \file lieu.cpp
 * \author Maxime Escourbiac Jean-Christophe Septier
 * \brief fichier d'implementation de la classe Lieu
 * \version 1.0
 * \date 7 janvier 2011
 */

#include "Lieu.h"
#include "Point.h"

/**
 * \fn Lieu(int id,const Point & coord, int ouverture,int fermeture,int demande,
            int tempservice, int clientcollecte, int clientlivraison,
            Program myprogram )
 * \brief Constructeur de la classe Lieu
 * \param id identifiantt du lieu
 * \param coord coordonne du lieu
 * \param ouverture horaire d'ouverture du lieu
 * \param fermeture horaire de fermeture du lieu
 * \param demande quantite que demande ou envoie le lieu
 * \param tempservice temps de service du lieu
 * \param clientcollecte client qui recevra le colis
 * \param clientlivraison client qui envoie le colis
 * \param myprogram pointeur sur l'instance de classe program
 *
 */
Lieu::Lieu(int id,const Point & coord, int ouverture, int fermeture, int demande,
           int tempservice, int clientcollecte, int clientlivraison,
           Program * myprogram ):
           _id(id), _ouverture(ouverture), _fermeture(fermeture),
           _demande(demande),_tempservice(tempservice),
           _clientcollecte(clientcollecte),_clientlivraison(clientlivraison),
           _myprogram(myprogram)
{
    _coord.x = coord.x;
    _coord.y = coord.y;
}


