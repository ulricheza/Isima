/*
 * \file Service.h
 * \author Maxime Escourbiac Jean-Christophe Septier
 * \brief fichier de declaration de la classe Service
 * \version 1.0
 * \date 7 janvier 2011
 */

#ifndef _SERVICE_H
#define	_SERVICE_H

class Service {
public:
    Service(int client,int quantite);
    Service(int client, int arrive, int depart, int quantite);
    
    //getters
    int getClient()   {return _client;}
    int getArrive()   {return _arrive;}
    int getDepart()   {return _depart;}
    int getQuantite() {return _quantite;}

    //setters
    void setArrive(int val) {_arrive = val;}
    void setDepart(int val) {_depart = val;}
    
private:
    int _client;
    int _arrive; //temps d'arrive au lieu
    int _depart;
    int _quantite;
};

#endif	/* _SERVICE_H */

