/**
 * \file simulateur.h
 * \author Maxime ESCOURBIAC Jean Christophe SEPTIER
 * \brief Fichier d'en tete de la classe simulateur
 * \date 22 novembre 2010
 */


#include "Simulateur.h"

 LapinMale male[10000000];
 LapinFemelle femelle[10000000];

/**
 * \fn Simulateur::Simulateur()
 * \brief constructeur par defaut
 * La version de Mersenne Twister que l'on a choisi doit etre initialise par
 * un tableau de unsigned long donc on l'initialise via le generateur GNU
 * qui est suffisament performant pour cette tache.
 * On remarquera que l'on initialisera qu'une seule fois le Mersenne Twister
 * lors de l'execution de toutes les experiences
 */

Simulateur::Simulateur()
{

    unsigned long init[4];
    
    srand(time(0));
    init[0]= (unsigned long) rand();
    init[1]= (unsigned long) rand();
    init[2]= (unsigned long) rand();
    init[3]= (unsigned long) rand();

    init_by_array(init,4); // initialisation du generateur mersenne twister

}


/**
 * \fn int Simulateur::gene_int(int modulo) const;
 * \brief genere un entier entre 0 et modulo-1 via le generateur MT
 * \param modulo valeur maximale + 1 que l'on pourra optenir au tirage
 * \return un nombre entier entre 0 et modulo-1
 */

int Simulateur::gene_int(int modulo) const
{
    return(genrand_int32()%modulo);
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
    static int tab[11] = {1,2,3,3,4,4,4,2,2,1,1};
    return(tab[gene_int(11)]);
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
    static int tab[18] = {3,4,5,5,6,6,7,7,7,8,8,8,9,9,10,10,11,12};
    return(tab[gene_int(18)]);
}

/**
 * \fn int Simulateur::duree_vie_annee() const
 * \brief tire un nombre aleatoire simulant un histogramme
 * \return le nombre d'annee que vivra la lapin
 * probabilite de chaque element d'etre tire:
 *
 * 0 : 4/32
 * 1 : 3/32
 * 2 : 1/32
 * 3 : 1/32
 * 4 : 1/32
 * 5 : 1/32
 * 6 : 1/32
 * 7 : 2/32
 * 8 : 4/32
 * 9 : 5/32
 * 10: 3/32
 * 11: 2/32
 * 12: 1/32
 * 13: 1/32
 * 14: 1/32
 * 15: 1/32
 *
 */

int Simulateur::duree_vie_annee() const
{
    static int tab[32]
    ={0,0,0,0,1,1,1,2,3,4,5,6,7,7,8,8,8,8,9,9,9,9,9,10,10,10,11,11,12,13,14,15};

    return(tab[gene_int(32)]);
}


/**
 * \fn int Simulateur::duree_vie_mois() const
 * \brief generateur equiprobable de nombre entre 0 et 11
 * \return le mois ou le lapin mourra
 * Sert pour affiner la duree de vie du Lapin
 */

int Simulateur::duree_vie_mois() const
{
    return(gene_int(12));
}

/**
 * \fn int Simulateur::male_femelle() const
 * \brief generateur equiprobable de 1 ou de 0
 * \return si le nouveau lapin est un male ou une femelle
 *
 */

int Simulateur::male_femelle() const
{
    return(gene_int(2));
}

/**
 * \fn void Simulateur::gestion_mois()
 * \brief gere chaque lapin pour une iteration donnee
 * 
 */

void Simulateur::gestion_mois()
{
   int size;
   list<Lapin*>::iterator it = _Lapin.begin();
   list<Lapin*>::iterator itsauv;
   size = _Lapin.size();
   for(int i=0; i<size;++i)
   {
       if((*it)->doit_mourir())
       {
           itsauv = it;
           ++it;
           (*itsauv)->meurt();
           _Lapin.erase(itsauv);
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
    int lapin_male = 5,lapin_femelle = 5;
    int i;
    _it_lapinmale = 0;
    _it_lapinfemelle = 0;
    temps = 0;


    for(i=0;i<lapin_male;++i)
        addLapin(true);

    for(i=0;i<lapin_femelle;++i)
        addLapin(false);
}

/**
 *\fn void Simulateur::purger_simu()
 *\brief fonction qui permet de purger le simulateur afin de realiser une autre
 *       experience
 */

void Simulateur::purger_simu()
{
    _Lapin.clear();
    Lapin::clear_cpt();
}

/**
 *\fn void addLapin(bool male)
 *\brief rajoute un lapin dans la liste des lapins
 *\param male true si on doit rajouter un male sinon on rajoute une femelle
 *
 */

void Simulateur::addLapin(bool ismale)
{
    if(ismale)
    {
         male[_it_lapinmale].naitre();
        _Lapin.push_back(&male[_it_lapinmale]);
        male[_it_lapinmale++].initLapin(this);
    }
    else
    {
        femelle[_it_lapinmale].naitre();
        _Lapin.push_back(&femelle[_it_lapinfemelle]);
        femelle[_it_lapinfemelle++].initLapin(this);
    }
}

