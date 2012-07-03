/**
 * \file Lapin.cpp
 * \author Maxime ESCOURBIAC Jean Christophe SEPTIER
 * \brief Fichier source de la classe lapin
 * \date 22 novembre 2010
 */

#include "Lapin.h"

//Initialisation des variables statiques
int Lapin::_lapin_cree = 0;
int LapinMale::nb_lapin_male_cree = 0;
int LapinMale::nb_lapin_male_vivant = 0;
int LapinMale::nb_lapin_male_adulte = 0;
int LapinFemelle::nb_lapin_femelle_cree = 0 ;
int LapinFemelle:: nb_lapin_femelle_vivant = 0 ;

/**************************************************************************/
/**************************************************************************/
/*                    LAPIN                                               */
/**************************************************************************/
/**************************************************************************/

/**
 *\fn Lapin::Lapin(Simulateur * attachSimu)
 *\brief constructeur de la classe Lapin
 *\param attachSimu pointeur sur l'instance Simulateur qui gere la population
 */

Lapin::Lapin(Simulateur * attachSimu): _MySimulateur(attachSimu), _adulte(false)
{
    _id = _lapin_cree++;
    _date_naissance = attachSimu->getTemps();
    _date_mort = _date_naissance + 12*attachSimu->duree_vie_annee()
                 + attachSimu->duree_vie_mois();
}

/**
 *\bool Lapin::doit_mourir() const
 *\brief fonction qui retourne true si le lapinb doit mourir
 *\return true si le lapin doit mourir
 */

bool Lapin::doit_mourir() const
{
    return(_date_mort == _MySimulateur->getTemps());
}



/**************************************************************************/
/**************************************************************************/
/*                    LAPIN MALE                                          */
/**************************************************************************/
/**************************************************************************/


/**
 *\fn Lapin::LapinMale(Simulateur * attachSimu)
 *\brief constructeur de la classe LapinMale
 *\param attachSimu pointeur sur l'instance Simulateur qui gere la population
 */
LapinMale::LapinMale(Simulateur *attachSimu):Lapin(attachSimu)
{
    nb_lapin_male_cree++;
    nb_lapin_male_vivant++;
}

/**
 *\fn Lapin::~LapinMale()
 *\brief constructeur de la classe LapinMale
 */
LapinMale::~LapinMale()
{
    --nb_lapin_male_vivant;
    if(_adulte == true)
        --nb_lapin_male_adulte;
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
         ++nb_lapin_male_adulte;
    }
}

/**
 *\fn void LapinMale::operation_mois()
 *\brief fonction qui effectue les operations de la classe LapinMale
 *
 */
void LapinMale::operation_mois()
{
    if(_adulte==false)
    {
       passage_adulte();
    }
}

/**************************************************************************/
/**************************************************************************/
/*                    LAPIN FEMELLE                                       */
/**************************************************************************/
/**************************************************************************/

/**
 *\fn Lapin::LapinFemelle(Simulateur * attachSimu)
 *\brief constructeur de la classe LapinFemelle
 *\param attachSimu pointeur sur l'instance Simulateur qui gere la population
 */
LapinFemelle::LapinFemelle(Simulateur *attachSimu):Lapin(attachSimu),
                                                   _portee_restante(0)
{
    nb_lapin_femelle_cree++;
    nb_lapin_femelle_vivant++;
}

/**
 *\fn Lapin::~LapinFemelle()
 *\brief constructeur de la classe LapinMale
 */

LapinFemelle::~LapinFemelle()
{
    --nb_lapin_femelle_vivant;
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
        _portee_an = _MySimulateur->gene_porte_annee();
        _portee_restante = _portee_an;
        _prochaine_portee = _MySimulateur->getTemps() + 12/_portee_an;
    }
}

/**
 *\fn void LapinFemelle::operation_mois()
 *\brief fonction qui effectue les operations de la classe LapinFemelle
 *
 */
void LapinFemelle::operation_mois()
{
    if(_adulte==false) // cas lapine enfant
    {
       passage_adulte();
    }
    else
    {
        if(_prochaine_portee == _MySimulateur->getTemps() && LapinMale::getLapinMaleVivant() > 0)
        {
            --_portee_restante;
            switch(_portee_restante)
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
 *\fn void LapinFemelle::accoucher()
 *\brief fonction qui simule un accouchement de lapine
 *
 */

void LapinFemelle::accoucher()
{
    LapinFemelle * nvx_nee;
    LapinMale    * nvx_ne;
    int nb_enfant,i;

    nb_enfant = _MySimulateur->gene_lapin_portee();
    for(i=0;i<nb_enfant;++i)
    {
        if(_MySimulateur->male_femelle() == 0)
        {
            nvx_nee = new LapinFemelle(_MySimulateur);
            _MySimulateur->addLapin(nvx_nee);
        }
        else
        {
            nvx_ne = new LapinMale(_MySimulateur);
            _MySimulateur->addLapin(nvx_ne);
        }
    }
}
