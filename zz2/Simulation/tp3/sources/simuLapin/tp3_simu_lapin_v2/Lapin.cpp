/**
 * \file Lapin.cpp
 * \author Maxime ESCOURBIAC Jean Christophe SEPTIER
 * \brief Fichier source de la classe lapin
 * \version 2.0
 * \date 15 decembre 2010
 */

#include "Lapin.h"

//initialisation des variables de classe de Lapin
int Lapin::_lapin_male_vivant     = 0;
int Lapin::_lapin_femelle_vivante = 0;

/**************************************************************************/
/**************************************************************************/
/*                    LAPIN                                               */
/**************************************************************************/
/**************************************************************************/

/**
 *\fn void initLapin(Simulateur * mysimu)
 *\brief initialise un lapin
 *\param mysimu pointeur sur le simulateur auquel sera rattache le lapin
 *
 * Cette fonction ne peut pas se faire dans le constructeur car on utilise
 * un pool de lapin pour maximiser les performances
 */

void Lapin::initLapin(Simulateur * mysimu)
{
    _adulte = false;
    _date_naissance = mysimu->getTemps();
    _date_mort = _date_naissance +
                 mysimu->duree_vie_annee()*12 + mysimu->duree_vie_mois();
    _MySimulateur = mysimu;
}


/**
 *\fn Lapin::doit_mourir() const
 *\brief fonction qui retourne true si le lapin doit mourir
 *\return true si le lapin doit mourir
 */

bool Lapin::doit_mourir() const
{
    return(_date_mort == _MySimulateur->getTemps());
}

/**
 *\fn Lapin::clear_cpt()
 *\brief remet a zero les compteurs de lapins
 */

void Lapin::clear_cpt()
{
    _lapin_male_vivant     = 0;
    _lapin_femelle_vivante = 0;
}

/**************************************************************************/
/**************************************************************************/
/*                    LAPIN MALE                                          */
/**************************************************************************/
/**************************************************************************/

/**
 *\fn void LapinMale::operation_mois()
 *\brief fonction qui effectue les operations de la classe LapinMale
 *
 */
void LapinMale::operation_mois()
{
    if(!_adulte)
    {
       passage_adulte();
    }
}

/**
 *\fn bool LapinMale::passage_adulte()
 *\brief fonction qui verifie si un lapin est a l'age de passser adulte
 *
 */

void LapinMale::passage_adulte()
{
    if( (_date_naissance+3) <= _MySimulateur->getTemps())
    {
        _adulte = true;
    }
}



/**************************************************************************/
/**************************************************************************/
/*                    LAPIN FEMELLE                                       */
/**************************************************************************/
/**************************************************************************/

/**
 *\fn void LapinFemelle::accoucher()
 *\brief fonction qui simule un accouchement de lapine
 *
 */

void LapinFemelle::accoucher()
{
    int nb_enfant,i;

    nb_enfant = _MySimulateur->gene_lapin_portee();
    for(i=0;i<nb_enfant;++i)
    {
        if(_MySimulateur->male_femelle() == 0)
        {
            _MySimulateur->addLapin(false);
        }
        else
        {
            _MySimulateur->addLapin(true);
        }
    }
}


/**
 *\fn void LapinFemelle::operation_mois()
 *\brief fonction qui effectue les operations de la classe LapinFemelle
 *
 */

void LapinFemelle::operation_mois()
{
    if(!_adulte) // cas lapine enfant
    {
       passage_adulte();
    }
    else
    {
        // a changer la gestion de l'autorisationd e l'acouchemennt
        if(_prochaine_portee == _MySimulateur->getTemps()
           && _lapin_male_vivant > 0)
        {
            switch(--_portee_restante)
            {
                case 1:
                    //on comble l'annee avec la dernier portee
                    _prochaine_portee += 12 - (12/_portee_an)*(_portee_an-1);
                    break;
                case 0:
                    //on redefinit le nombre de portee par an
                    _portee_an = _MySimulateur->gene_porte_annee();
                    _portee_restante = _portee_an;
                    _prochaine_portee += 12/_portee_an;
                    break;
                default:
                    //on redefinit la prochaine portee
                    _prochaine_portee += (12/_portee_an);
                    break;
            }
            accoucher();
        }
    }
}


/**
 *\fn bool LapinFemelle::passage_adulte()
 *\brief fonction qui verifie si une lapine est a l'age de passser adulte
 *
 */

void LapinFemelle::passage_adulte()
{
    if( (_date_naissance+4) <= _MySimulateur->getTemps())
    {
        _adulte = true;
        //on definit le nombre de portee par an
        _portee_an = _MySimulateur->gene_porte_annee();
        _portee_restante = _portee_an;
        _prochaine_portee = _MySimulateur->getTemps() + 12/_portee_an;
    }
}
