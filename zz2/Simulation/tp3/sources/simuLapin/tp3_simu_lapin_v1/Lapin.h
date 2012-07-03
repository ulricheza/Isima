/**
 * \file Lapin.h
 * \author Maxime ESCOURBIAC Jean Christophe SEPTIER
 * \brief Fichier d'en tete de la classe lapin
 * \date 22 novembre 2010
 */

#ifndef __LAPIN_H__
#define __LAPIN_H__


#include "Simulateur.h"

class Simulateur;
/**
 * \class Lapin
 * \brief Classe Abstraite pour les lapins
 */
class Lapin{

 public:
    Lapin(Simulateur * attachSimu);
    virtual ~Lapin(){}
    virtual void operation_mois() = 0;
    virtual void passage_adulte() = 0;
    bool doit_mourir() const ;

 protected:
    int _id;
    int _date_naissance;
    int _date_mort;
    static int _lapin_cree;
    bool _adulte;
    Simulateur * _MySimulateur;
};


/**
 * \class LapinMale
 * \brief Classe simulant les lapins males
 */
class LapinMale : public  Lapin {

 public:
    LapinMale(Simulateur * attachSimu);
    ~LapinMale();
    virtual void operation_mois();
    virtual void passage_adulte();
    static int getLapinMaleVivant() {return nb_lapin_male_vivant;}
    static int getLapinMaleCree()   {return nb_lapin_male_cree;}
    static int getLapinMaleAdulte() {return nb_lapin_male_adulte;}
 protected:
    static int nb_lapin_male_cree ;
    static int nb_lapin_male_vivant;
    static int nb_lapin_male_adulte;
};


/**
 * \class LapinFemelle
 * \brief Classe simulant les lapins femelles
 */


class LapinFemelle : public Lapin{

 public:
     LapinFemelle(Simulateur * attachSimu);
     ~LapinFemelle();
    void accoucher();
    virtual void operation_mois();
    virtual void passage_adulte();
    static int getLapinFemelleVivant() {return nb_lapin_femelle_vivant;}
    static int getLapinFemelleCree()   {return nb_lapin_femelle_cree;}

 protected:
    int _portee_restante;
    int _prochaine_portee;
    int _portee_an;
    static int nb_lapin_femelle_cree ;
    static int nb_lapin_femelle_vivant ;
};

#endif // Lapin_h
