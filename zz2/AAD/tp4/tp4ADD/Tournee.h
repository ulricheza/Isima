/*
 * \file Tournee.h
 * \author Maxime Escourbiac Jean-Christophe Septier
 * \brief fichier de declaration de la classe Tournee
 * \version 1.0
 * \date 7 janvier 2011
 */

#ifndef _TOURNEE_H
#define	_TOURNEE_H

#include <list>

class Service;
class Program;
class Requete;
class Lieu;
class Program;

using namespace std;

class Tournee {
public:

    //Methodes
    void AddService(Service * srv) { _service.push_back(srv); }
    void AfficherService();
    void AjusterTournee(Program * p, int lieu);
    void FinaliserTournee(Program * prog);
    bool FusionPossible(Tournee *t, Lieu * l, Program *prog);
    bool InsertTournee(Tournee *t,Lieu *l, Program *p);
    bool InserableTournee(Program * p,Requete * req);
    bool InserableElement(Program * p,list<Service*>::iterator it,int time,int & arrive);
    bool InsertService(Requete * r,int l, Program * prog);

    //Getters
    int              getDateDepart() {return _DateDepart;}
    int              getDateArrive() {return _DateArrive;}
    list<Service*> * getService()    {return &_service;}

    //setters
    void setDateDepart(int val) {_DateDepart = val;}
    void setDateArrive(int val) {_DateArrive = val;}

private:
    list<Service*> _service;
    int _DateDepart;
    int _DateArrive;
};
#endif	/* _TOURNEE_H */
