/*
 * \file service.cpp
 * \author Maxime Escourbiac Jean-Christophe Septier
 * \brief fichier d'implemention de la classe Service
 * \version 1.0
 * \date 7 janvier 2011
 */

#include "Service.h"

/**
 * \fn Service(int client, int quantite)
 * \brief Constructeur reduit de la classe Service
 * \param client id du client
 * \param quantite quantite livree
 *
 */
Service::Service(int client, int quantite):
         _client(client), _quantite(quantite)
{
}

/**
 * \fn Service(int client, int arrive, int depart, int quantite)
 * \brief Constructeur de la classe Service
 * \param client id du client
 * \param arrive heure d'arrive
 * \param depart heure de depart
 * \param quantite quantite livree
 *
 */
Service::Service(int client, int arrive, int depart, int quantite):
         _client(client), _arrive(arrive), _depart(depart), _quantite(quantite)
{
}


