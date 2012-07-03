/* 
 * File:   Membre.h
 * Author: maxime
 *
 * Created on 5 novembre 2011, 22:35
 */

#ifndef _MEMBRE_H
#define	_MEMBRE_H

#include <string>

using namespace std;

//definition des flags pour les caracteristique du membre
#define M_VIRTUAL      1    //0b001
#define M_PURE_VIRTUAL 3    //0b011 //si virtuelle pure alors deja virtuelle
#define M_STATIC       4    //0b100

/**
 * \enum Accesibilite
 * \brief Enumeration des differents types d'accesseurs possible
 *
 */
enum Accesibility {
    M_PRIVATE,
    M_PROTECTED,
    M_PUBLIC
};

/**
 * \class Membre
 * \brief Classe abstraite representant un membre d'une classe
 *
 */
class Membre {
public:
    //Constructeur et destructeur
    Membre();
    Membre(string id, string type, Accesibility acces, unsigned char caracteristic );
    virtual ~Membre();

    //Methode
    virtual string toString() = 0;

    //Getters et setter
    string        getId()              { return _id; }
    string        getType()            { return _type;}
    Accesibility  getAccess()          { return _acces;}
    unsigned char getCaracteristics()  { return _characteristics;}
    bool          isStatic()           { return ((_characteristics & M_STATIC) == M_STATIC); } //teste si le membre est static

    void setId(string id)                         { _id = id; }
    void setType(string type)                     { _type = type;}
    void setAccesibilite(Accesibility acces)      { _acces = acces;}
    void setCharacteristics( unsigned char caracteristics) { _characteristics = caracteristics;}
    
protected:
    string        _id;             //Nom du membre
    string        _type;           //Type du membre ou type de retour
    Accesibility  _acces;          //Private,Protected ou Public
    unsigned char _characteristics;//Flag caracterisant le membre (cf declarations ci-dessus)
};

#endif	/* _MEMBRE_H */

