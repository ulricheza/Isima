/**
 * \file simulateur.h
 * \author Maxime ESCOURBIAC Jean Christophe SEPTIER
 * \brief Fichier d'en tete de la classe simulateur
 * \date 22 novembre 2010
 */


#include "Simulateur.h"

/**
 * \fn Simulateur::Simulateur()
 * \brief constructeur par defaut
 */

Simulateur::Simulateur() : temps(0)
{

}

/**
 * \fn Simulateur::~Simulateur()
 * \brief destructeur par defaut
 *
 *  Dans le diagramme de classe UML on a definit une composition entre les
 *  lapins et le simulateur donc on detruie les lapins lors de la destruction
 *  de l'instance simulateur
 */
Simulateur::~Simulateur()
{
    list<Lapin*>::iterator it;

    while(!_Lapin.empty())
    {
        it = _Lapin.begin();
        delete (*it);
        _Lapin.pop_front();
    }
}


/**
 * \fn float Simulateur::gene_rand() const
 * \brief tire un nombre reel entre 0 et 1 avec 2 chiffres significatifs
 * \return nombre compris en 0 et 1 avec 2 chiffres significatif
 */

float Simulateur::gene_rand() const
{
    return((float)(rand()%101) / 100.0);
}


/**
 * \fn int Simulateur::gene_porte_annee() const
 * \brief tire un nombre aleatoire simulant un histogramme
 * \return un nombre aleatorie simulant le nombre de portee par annee
 *
 * simule le nombre de portee par annee
 * probabilite de chaque element d'etre tire:
 *
 * 1 : 1/11
 * 2 : 1/11
 * 3 : 2/11
 * 4 : 3/11
 * 5 : 2/11
 * 6 : 1/11
 * 7 : 1/11
 */

int Simulateur::gene_porte_annee() const
{
    float valeur_alea;
    int val;
    int ret;

    valeur_alea = 100.0*gene_rand();
    valeur_alea = valeur_alea / (100.0/11.0);

    val = (int)valeur_alea;

    switch(val)
    {
        case 0:
            ret = 1;
            break;
        case 1:
            ret = 2;
            break;
        case 2:
        case 3:
            ret = 3;
            break;
        case 4:
        case 5:
        case 6:
            ret = 4;
            break;
        case 7:
        case 8:
            ret = 5;
            break;
        case 9:
            ret = 6;
            break;
        case 10:
        case 11:
            ret = 7;
            break;
    }
    return ret;
}

/**
 * \fn int Simulateur::gene_lapin_portee() const
 * \brief tire un nombre aleatoire simulant un histogramme
 * \return un nombre aleatoire simulant le nombre de lapin par portee
 *
 * simule le nombre de lapin par portee
 * probabilite de chaque element d'etre tire:
 *
 * 3 : 1/18
 * 4 : 1/18
 * 5 : 2/18
 * 6 : 2/18
 * 7 : 3/18
 * 8 : 3/18
 * 9 : 2/18
 * 10: 2/18
 * 11: 1/18
 * 12: 1/18
 */

int Simulateur::gene_lapin_portee() const
{
    float valeur_alea;
    int val;
    int ret;

    valeur_alea = 100.0*gene_rand();
    valeur_alea = valeur_alea / (100.0/18.0);

    val = (int)valeur_alea;

    switch(val)
    {
        case 0:
            ret = 3;
            break;
        case 1:
            ret = 4;
            break;
        case 2:
        case 3:
            ret = 5;
            break;
        case 4:
        case 5:
            ret = 6;
            break;
        case 6:
        case 7:
        case 8:
            ret = 7;
            break;
        case 9:
        case 10:
        case 11:
            ret = 8;
            break;
        case 12:
        case 13:
            ret = 9;
            break;
        case 14:
        case 15:
            ret = 10;
            break;
        case 16:
            ret = 11;
            break;
        case 17:
        case 18:
            ret = 12;
            break;
    }
    return ret;
}

/**
 * \fn int Simulateur::duree_vie_annee() const
 * \brief tire un nombre aleatoire simulant un histogramme
 * \return le nombre d'annee que vivra la lapin
 * probabilite de chaque element d'etre tire:
 *
 * 1 : 3/32
 * 2 : 2/32
 * 3 : 1/32
 * 4 : 1/32
 * 5 : 1/32
 * 6 : 1/32
 * 7 : 2/32
 * 8 : 4/32
 * 9 : 5/32
 * 10: 4/32
 * 11: 3/32
 * 12: 2/32
 * 13: 1/32
 * 14: 1/32
 * 15: 1/32
 *
 */

int Simulateur::duree_vie_annee() const
{
    float valeur_alea;
    int val;
    int ret;

    valeur_alea = 100.0*gene_rand();
    valeur_alea = valeur_alea / (100.0/32.0);

    val = (int)valeur_alea;

    switch(val)
    {
        case 0:
        case 1:
        case 2:
            ret = 1;
            break;
        case 3:
        case 4:
            ret = 2;
            break;
        case 5:
            ret = 3;
            break;
        case 6:
            ret = 4;
            break;
        case 7:
            ret = 5;
            break;
        case 8:
            ret = 6;
        case 9:
        case 10:
            ret = 7;
            break;
        case 11:
        case 12:
        case 13:
        case 14:
            ret = 8;
            break;
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
            ret = 9;
            break;
        case 20:
        case 21:
        case 22:
        case 23:
            ret = 10;
            break;
        case 24:
        case 25:
        case 26:
            ret = 11;
            break;
        case 27:
        case 28:
            ret = 12;
            break;
        case 29:
            ret = 13;
            break;
        case 30:
            ret = 14;
            break;
        case 31:
        case 32:
            ret = 15;
            break;
    }
    return ret;
}


/**
 * \fn int Simulateur::duree_vie_mois() const
 * \brief generateur equiprobable de nombre entre 0 et 11
 * \return le mois ou le lapin mourra
 * Sert pour affiner la duree de vie du Lapin
 */

int Simulateur::duree_vie_mois() const
{
    return((int)(gene_rand()*11.0));
}

/**
 * \fn int Simulateur::male_femelle() const
 * \brief generateur equiprobable de 1 ou de 0
 * \return si le nouveau lapin est un male ou une femelle
 *
 */

int Simulateur::male_femelle() const
{
    return(rand()%2);
}

/**
 * \fn void Simulateur::gestion_mois()
 * \brief gere chaque lapin pour une iteration donnee
 * 
 */

void Simulateur::gestion_mois()
{
    int i,size;
    list<Lapin*>::iterator it,itsauv;

    it = _Lapin.begin();
    size = _Lapin.size();
    for(i=0;i<size;++i)
    {
        if((*it)->doit_mourir())
        {
            itsauv = it;
            ++it;
            delete (*itsauv);
            _Lapin.remove(*itsauv);
        }
        else
        {
            (*it)->operation_mois();
            ++it;
        }
    }
}

/**
 * \fn void Simulateur::initialiser_simu()
 * \brief initialise les donnes pour la simulation
 *
 */

void Simulateur::initialiser_simu()
{
    int lapin_male,lapin_femelle,i;
    LapinMale * temp_male;
    LapinFemelle * temp_femelle;
    printf("Nombre de jeunes males pour le debut de la simulation\n");
    scanf("%d",&lapin_male);
    for(i=0;i<lapin_male;++i)
    {
        temp_male = new LapinMale(this);
        _Lapin.push_back(temp_male);
    }

    printf("Nombre de jeunes femelles pour le debut de la simulation\n");
    scanf("%d",&lapin_femelle);
    for(i=0;i<lapin_femelle;++i)
    {
        temp_femelle = new LapinFemelle(this);
        _Lapin.push_back(temp_femelle);
    }
}

