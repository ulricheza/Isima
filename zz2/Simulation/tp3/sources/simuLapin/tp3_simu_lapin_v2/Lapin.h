/**
 * \file Lapin.h
 * \author Maxime ESCOURBIAC Jean Christophe SEPTIER
 * \brief Fichier d'en tete de la classe lapin
 * \version 2.0
 * \date 15 decembre 2010
 */

#ifndef __LAPIN_H__
#define __LAPIN_H__


#include "Simulateur.h"

class Simulateur;

// Explication du choix pour l'implementation des compteurs de lapins:
// L'utilisation d'un pool comme celui-ci ne permet pas d'utiliser les
// constructeurs et les destructeurs afin de decrementer les compteurs.
// Donc on a decide d'implementer les fonctions naitre() et meurt() afin de
// realiser les decrementations. On aurait pas pu les implementer sous forme
// de methodes de classe car dans le simulateur on se sert du polymorphisme
// pour les distinguer par rapport a la liste de Lapin *


/**
 * \class Lapin
 * \brief Classe Abstraite pour les lapins
 */
class Lapin{

 public:
    Lapin(){}
    virtual ~Lapin(){}
    void initLapin(Simulateur * Mysimu);
    bool doit_mourir() const ;
    virtual void operation_mois() = 0;
    virtual void passage_adulte() = 0;
    virtual void meurt()  = 0;
    virtual void naitre() = 0;
    static int nb_male_vivant()     {return _lapin_male_vivant;}
    static int nb_femelle_vivante() {return _lapin_femelle_vivante;}
    static void clear_cpt();
 protected:
    static int _lapin_male_vivant;
    static int _lapin_femelle_vivante;
    int _date_naissance;
    int _date_mort;
    bool _adulte;
    Simulateur * _MySimulateur;
};


/**
 * \class LapinMale
 * \brief Classe simulant les lapins males
 */
class LapinMale : public  Lapin {

 public:
    LapinMale(){}
    ~LapinMale(){};
    virtual void operation_mois();
    virtual void passage_adulte();
    virtual void meurt() {--_lapin_male_vivant;}
    virtual void naitre(){++_lapin_male_vivant;}
};


/**
 * \class LapinFemelle
 * \brief Classe simulant les lapins femelles
 */
class LapinFemelle : public Lapin{

 public:
     LapinFemelle() {}
     ~LapinFemelle(){}
    void accoucher();
    virtual void operation_mois();
    virtual void passage_adulte();
    virtual void meurt() {--_lapin_femelle_vivante;}
    virtual void naitre(){++_lapin_femelle_vivante;}

 protected:
    int _portee_restante;
    int _prochaine_portee;
    int _portee_an;
};

#endif // Lapin_h
