/*
 * \file tournee.cpp
 * \author Maxime Escourbiac Jean-Christophe Septier
 * \brief fichier d'implemention de la classe Tournee
 * \version 1.0
 * \date 7 janvier 2011
 */

#include <iostream>
#include "Tournee.h"
#include "Service.h"
#include "Program.h"
#include "Lieu.h"
#include "Requete.h"


/**
 * \fn Tournee::AfficherService()
 * \brief affichage sur la sortie standard d'une tournee
 *
 */
void Tournee::AfficherService()
{
	list<Service*>::iterator it;
        cout << "------------------------"<< endl;
        cout << "------------------------"<< endl;
        cout << "Affichage d'une tournee" << endl;
        cout << "Depart: " << _DateDepart << "Arrive: " << _DateArrive << endl;
	for(it=_service.begin();it!=_service.end();++it)
	{
            cout << "client: " << (*it)->getClient() << " " << "arrive: " << (*it)->getArrive() << " " <<
                    " depart: " << (*it)->getDepart() << " " << "quantite: " << (*it)->getQuantite() << endl;
	}
}

// TODO doc
bool Tournee::FusionPossible(Tournee *t, Lieu * l, Program *p)
{
    list<Service*>::iterator it,itprec;
    bool trouve = false;
    int temps;
    vector<Lieu*>  lieu = *(p->getLieu());

    it =_service.begin();
    int test = l->getId();
    //printf("%d\n",test);
    while( it!=_service.end() && trouve == false)
    {
        //int truc = (*it)->getClient();
        if( l->getId() == (*it)->getClient() )
            trouve = true;
        else
            ++it;
    }

    temps = (*it)->getDepart();

    list<Service*>::iterator it2;
    list<Service*>::iterator it2prec;
    bool possible = true;
    it2=t->getService()->begin();
    it2prec=it;
    while( it2!=t->getService()->end() && possible == true)
    {
        //tests
        int a = (*it2)->getClient();
        int b = (*it2prec)->getClient();
        temps = temps + p->Calcul_dist(lieu[(*it2prec)->getClient()]->getCoord(),
                lieu[(*it2)->getClient()]->getCoord());

        int truc = lieu[(*it2)->getClient()]->getFermeture();
        if(temps < lieu[(*it2)->getClient()]->getOuverture())
            temps = lieu[(*it2)->getClient()]->getOuverture();
        else if(temps > lieu[(*it2)->getClient()]->getFermeture())
                possible = false;

        temps = temps + lieu[(*it2)->getClient()]->getTempservice();
        it2prec=it2;
        it2++;
    }

    if(possible)
    {
        itprec = it2prec;
        it++;

           while( it!=_service.end() && possible == true)
           {
                temps = temps + p->Calcul_dist(lieu[(*itprec)->getClient()]->getCoord(),
                lieu[(*it)->getClient()]->getCoord());

                if(temps < lieu[(*it)->getClient()]->getOuverture())
                    temps = lieu[(*it)->getClient()]->getOuverture();
                else if(temps > lieu[(*it)->getClient()]->getFermeture())
                    possible = false;

                temps = temps + lieu[(*it)->getClient()]->getTempservice();
                itprec=it;
                it++;
           }

    }
    return possible;
}

// TODO doc
bool Tournee::InsertTournee(Tournee *t,Lieu *l, Program *p)
{
    //printf("Insert!!!");
    list<Service*>::iterator it;
    list<Service*>::iterator it2;
    bool trouve = false;
    int client, arrive, depart, quantite,client2;
    //t->Afficher_service();
    //Afficher_service();
    it=_service.begin();

    //recherche de l'element
    while( it!=_service.end() && trouve == false)
    {
        if( l->getId() == (*it)->getClient() )
        {
            trouve = true;
            ++it;
        }
        else
            ++it;

    }
    if(trouve)
    {
        //t->Afficher_service();
        //t->Afficher_service();

        for(it2=(t->getService())->begin();it2!=(t->getService())->end();++it2)
        {
            //printf("Valeur::%d:",(*it2)->getClient());
            _service.insert(it,(*it2));
        }
        AjusterTournee(p,l->getId());
    }

    return trouve;

}

/**
 * \fn  void Tournee::AjusterTournee(Program * p, int lieu)
 * \brief Reajuste les dates de la tournee a partir de lieu
 * \param p pointeur sur l'instance de programme
 * \param lieu id du lieu ou on commence a ajuster les dates 
 * 
 */
 void Tournee::AjusterTournee(Program * p, int lieu)
 {
     int time;
     list<Service*>::iterator cour = _service.begin();
     list<Service*>::iterator prec;
     vector<Lieu*> l = *(p->getLieu());

     //recherche du lieu
     while((*cour)->getClient() != lieu && cour != _service.end())
         ++cour;

     if(cour != _service.end())
     {
         time = (*cour)->getDepart();
         prec = cour;
         ++cour;
         while(cour != _service.end())
         {
             //calcul de la date d'arrive au point
             time +=  p->Calcul_dist(l[(*prec)->getClient()]->getCoord(),l[(*cour)->getClient()]->getCoord());
             (*cour)->setArrive(time);

             //test si on est arrive avant la date d'ouverture
             if(time < l[(*cour)->getClient()]->getOuverture())
                 time = l[(*cour)->getClient()]->getOuverture();

             //calcul de la date de depart du point
             time += l[(*cour)->getClient()]->getTempservice();
             (*cour)->setDepart(time);

             prec = cour; //on avance les iterateurs
             ++cour;
         }
     }
 }

/**
 * \fn Tournee::FinaliserTournee(Program * prog)
 * \brief Finalise une tournee en calculant la distance entre le dernier lieu et le depot
 * \param prog pointeur sur l'instance du programme
 *
 */
void Tournee::FinaliserTournee(Program * prog)
{
    int time;
    Service * s1 = _service.back();
    Service * s2 = _service.front();
    vector<Lieu*>  l = *(prog->getLieu());
    Lieu * last = l[s1->getClient()];
    Lieu * first = l[s2->getClient()];

    //gestion de la date d'arrive
    _DateArrive = s1->getDepart() + prog->Calcul_dist(last->getCoord(),l[0]->getCoord());

    //gestion de la date de depart au plus tard
    time = l[0]->getOuverture() + prog->Calcul_dist(first->getCoord(),l[0]->getCoord());
    if(time<first->getOuverture())
    {
        s2->setArrive(first->getOuverture());
        _DateDepart = first->getOuverture() - time;
    }
}

/**
 * \fn bool InsertService(Requete *r, int l, Program * p)
 * \brief insere une requete dans une tournee apres le lieu l
 * \param r pointeur sur la requete a inserer
 * \param l lieu ou la requete sera inserer
 * \param p pointeur sur l'instance de Program
 */
bool Tournee::InsertService(Requete *r, int l, Program * p)
{
    list<Service*>::iterator it,prec;
    vector<Lieu*> lieu = *(p->getLieu());
    bool trouve = false;
    int client, arrive, depart, quantite,client2;


    if(l == 0)
    {
        client  = r->getCollecte();
        client2 = r->getLivraison();
        arrive = lieu[client]->getOuverture() + lieu[client]->getTempservice();

        _service.push_front(new Service(client2,-r->getQuantite()));
        _service.push_front(new Service(client,lieu[client]->getOuverture(),arrive,r->getQuantite()));
        AjusterTournee(p,client);
    }
    else
    {
        it=_service.begin();
        while( it!=_service.end() && trouve == false)
        {
            if( l == (*it)->getClient() )
                trouve = true;
            else
                ++it;
        }
        if(trouve)
        {
            prec = it;
            ++it;
            _service.insert(it,new Service(r->getCollecte(),r->getQuantite()));
            _service.insert(it,new Service(r->getLivraison(),-r->getQuantite()));
            AjusterTournee(p,l);
        }
    }
    return trouve;
}


/**
 * \fn bool InserableElement(Program * p,int lieu,Requete * req, int * arrive)
 * \brief teste si une requete est inserable apres une requete donnee dans une tournee
 * \param p pointeur sur l'instance de Program
 * \param lieu identifiant du lieu de livraison de la derniere requete
 * \param req requete a inserer
 * \param arrive pointeur sur un entier pour recuperer la date de retour au depot
 *        -1 si on veut pas recuperer la valeur
 * \return true si la requete peut etre insere
 */

bool Tournee::InserableElement(Program * p,list<Service*>::iterator it,int time,int & arrive)
{
    list<Service*>::iterator prec;
    vector<Lieu*> lieu = *p->getLieu();
    bool ret = true;

    while(it != _service.end() && ret)
    {
        if(time < lieu[(*it)->getClient()]->getOuverture())
            time = lieu[(*it)->getClient()]->getOuverture();
        if(time > lieu[(*it)->getClient()]->getFermeture())
            ret = false;
        time += lieu[(*it)->getClient()]->getTempservice();
        prec = it;
        ++it;
        if(it != _service.end())
            time += p->Calcul_dist(lieu[(*it)->getClient()]->getCoord(),lieu[(*prec)->getClient()]->getCoord());
    }
    if(ret)
    {
        //test du retour au depot
        time += p->Calcul_dist(lieu[(*prec)->getClient()]->getCoord(),lieu[0]->getCoord());
        if(time > lieu[0]->getFermeture())
            ret = false;
        if(ret)
            arrive = time;
    }

    return ret;
}


/**
 * \fn bool InserableTournee(Program * p,Requete * req)
 * \brief teste si une requete est inserable dans une tournee
 * \param p pointeur sur l'instance de Program
 * \param req requete a inserer
 * \return true si la requete peut etre insere
 */
bool Tournee::InserableTournee(Program * p,Requete * req)
{
    list<Service*>::iterator it = _service.begin();
    list<Service*>::iterator bestit;
    vector<Lieu*> lieu = *p->getLieu();
    int arrive,depart,time,timeretour,besttime = 10000000;
    int interrequete = _service.size()/2;
    bool ret = false;

    //test si on peut inserer en debut
    time = lieu[req->getCollecte()]->getOuverture() + lieu[req->getCollecte()]->getTempservice();
    time += p->Calcul_dist(lieu[req->getCollecte()]->getCoord(),lieu[req->getLivraison()]->getCoord());
    if(time < lieu[req->getLivraison()]->getOuverture())
        time = lieu[req->getLivraison()]->getOuverture();
    time += lieu[req->getLivraison()]->getTempservice();
    time += p->Calcul_dist(lieu[(*it)->getClient()]->getCoord(),lieu[req->getLivraison()]->getCoord());
    if(InserableElement(p,it,time,timeretour))
    {
        besttime = timeretour;
        bestit = it;
        ret = true;
    }
    ++it;
    //test si on peut inserer dans toutes les sous requetes
    for(int i = 0; i < interrequete-1;++i)
    {
        time = (*it)->getDepart();
        time += p->Calcul_dist(lieu[(*it)->getClient()]->getCoord(),lieu[req->getCollecte()]->getCoord());
        if(time < lieu[req->getCollecte()]->getOuverture())
            time = lieu[req->getCollecte()]->getOuverture();
        time += lieu[req->getCollecte()]->getTempservice();
        time += p->Calcul_dist(lieu[req->getCollecte()]->getCoord(),lieu[req->getLivraison()]->getCoord());
        if(time < lieu[req->getLivraison()]->getOuverture())
            time = lieu[req->getLivraison()]->getOuverture();
        time += lieu[req->getLivraison()]->getTempservice();
        ++it;
        time += p->Calcul_dist(lieu[(*it)->getClient()]->getCoord(),lieu[req->getLivraison()]->getCoord());
        if(InserableElement(p,it,time,timeretour) && timeretour < besttime)
        {
            besttime = timeretour;
            bestit = ++it;
            ret = true;
        }
        else
         ++it;
    }

    //test si on peut inserer en fin
    time = (*it)->getDepart();
    time += p->Calcul_dist(lieu[(*it)->getClient()]->getCoord(),lieu[req->getCollecte()]->getCoord());
    if(time < lieu[req->getCollecte()]->getOuverture())
            time = lieu[req->getCollecte()]->getOuverture();
    time += lieu[req->getCollecte()]->getTempservice();
    time += p->Calcul_dist(lieu[req->getCollecte()]->getCoord(),lieu[req->getLivraison()]->getCoord());
    if(time < lieu[req->getLivraison()]->getOuverture())
        time = lieu[req->getLivraison()]->getOuverture();
    time += lieu[req->getLivraison()]->getTempservice();
    time += p->Calcul_dist(lieu[0]->getCoord(),lieu[req->getLivraison()]->getCoord());

    //on effectue le test directement dans la fonction
    if(time < lieu[0]->getFermeture())
    {
        besttime = time;
        bestit = it;
        ret = true;
    }

    //insertion de la requete
    if(ret)
    {
        if(bestit == _service.begin())
        {
            arrive = lieu[req->getCollecte()]->getOuverture();
            depart = arrive + lieu[req->getCollecte()]->getTempservice();
            _service.push_front(new Service(req->getLivraison(),-req->getQuantite()));
            _service.push_front(new Service(req->getCollecte(),arrive,depart,req->getQuantite()));
            AjusterTournee(p,req->getCollecte());
        }
        else
        {
            if(bestit == _service.end())
            {
                _service.push_back(new Service(req->getCollecte(),req->getQuantite()));
                _service.push_back(new Service(req->getLivraison(),req->getQuantite()));
                AjusterTournee(p,(*bestit)->getClient());
            }
            else
            {
                it = bestit;
                ++it;
                _service.insert(it,new Service(req->getCollecte(),req->getQuantite()));
                _service.insert(it,new Service(req->getLivraison(),-req->getQuantite()));
                AjusterTournee(p,(*bestit)->getClient());
            }
        }
    }
    return ret;
}