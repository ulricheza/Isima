/* 
 * File:   Attribut.cpp
 * Author: maxime
 * 
 * Created on 5 novembre 2011, 23:13
 */

#include "Attribut.h"

/**
 * \fn Attribut::Attribut()
 * \brief Constructeur par defeaut de la classe Attribut
 *
 */
Attribut::Attribut() {
}

/**
 * \fn Attribut::Attribut(string id, string type, Accesibility access, unsigned char characteristics)
 * \brief Constructeur de la classe Attribut
 * \param id              identificant de l'attribut
 * \param type            type de l'attribut
 * \param access          Accessibilite de l'attribut
 * \param characteristics Caracteristiques de l'attribut
 *
 */
Attribut::Attribut(string id, string type, Accesibility access, unsigned char characteristics)
: Membre(id,type,access, characteristics & M_STATIC) //$ M_STATIC sert a verifier que l'user n'a pas mis l'attribut virtuel
{

}

/**
 * \fn Attribut::~Attribut()
 * \brief Destructeur de la classe Attribut
 *
 */
Attribut::~Attribut() {
}

/**
 * \fn string Attribut::toString()
 * \brief Affiche les caracteristiques de l'attribut
 * \return Une chaine de caractere avec tous les caracteristiques de l'attribut
 *
 */
string Attribut::toString()
{
    string attribut = "";

    if( isStatic() == true )
        attribut += "static ";

    attribut += _type + " " + _id;

    return attribut;
}
