/*
 * \file requete.cpp
 * \author Maxime Escourbiac Jean-Christophe Septier
 * \brief fichier d'implementation de la classe Requete
 * \version 1.0
 * \date 7 janvier 2011
 */

#include "Requete.h"

/**
 * \fn Requete(int collecte, int livraison)
 * \brief Constructeur de la classe Requete
 * \param collecte id du lieu de collecte
 * \param livraison id du lieu de livraison
 * \param depart id du lieu de depart du vehicule
 *
 */
Requete::Requete(int collecte, int livraison,int quantite,Program * myprogram):
                 _collecte(collecte),_livraison(livraison),_myprogram(myprogram),
                 _quantite(quantite)

{
}


