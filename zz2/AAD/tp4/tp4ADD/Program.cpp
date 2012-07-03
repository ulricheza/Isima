/*
 * \file program.cpp
 * \author Maxime Escourbiac Jean-Christophe Septier
 * \brief fichier d'implementation de la classe Program
 * \version 1.0
 * \date 7 janvier 2011
 */


#include "Program.h"
#include "Lieu.h"
#include "Requete.h"
#include "Service.h"
#include "Tournee.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

#define TAILLE_POP 50
#define ITER_MAX 50


/**
 * \fn Program::~Program()
 * \brief Destructeur de la classe program
 */
Program::~Program()
{
    while(!_requete.empty())
    {
        delete _requete.front();
        _requete.pop_front();
    }
    while(!_lieu.empty())
    {
        delete _lieu.back();
        _lieu.pop_back();
    }
}

/**
 * \fn Program::Program::LireFichier(char* fichier)
 * \brief Methode de lecture et d'initialisation de l'instance
 * \param fichier chaine de caractere sur la lecture du fichier
 *
 */
void Program::LireFichier(char* fichier)
{
    int capacite, inutile,client,demande,ouv,fer,ser,col,liv;
    Point p;
    ifstream fic(fichier, ios::in);

    if(!fichier)
    {
        cerr << "erreur dans la lecture de fichier";
        exit(EXIT_FAILURE);
    }

    //lecture de la premiere ligne (useless)
    fic >> inutile >> capacite >> inutile;

    //lecture de tous les lieux
    while(!fic.eof())
    {
        fic >> client >> p.x >> p.y >> demande >> ouv >> fer >> ser >> col >> liv;
        _lieu.push_back(new Lieu(client, p, ouv, fer, demande, ser, col, liv, this));
        if(demande > 0)
            _requete.push_back(new Requete(client,liv,demande,this));
    }
    fic.close();
}


/**
 * \fn bool Predicat_suppr(Requete * test)
 * \brief Methode qui teste la faisabitlite d'une requete fonction amie de Program
 * \param fichier chaine de caractere sur la lecture du fichier
 * \return ret true si la requete n'est plus faisable
 *
 */
bool Predicat_suppr(Requete * test)
{
    bool ret = false;
    Program * p = test->getMyprogram();
    int time = p->_temps;

    Lieu * collecte =  p->_lieu[test->getCollecte()];
    Lieu * livraison = p->_lieu[test->getLivraison()];

    time +=  p->Calcul_dist(collecte->getCoord(),p->_lieu[p->_lieuactuel]->getCoord());
    test->setArriveCollecte(time);

    if(time < collecte->getOuverture())
        time = collecte->getOuverture();

    if(time > collecte->getFermeture())
        ret = true;
    else
    {
        time += collecte->getTempservice();
        test->setDepartCollecte(time);
        time += p->Calcul_dist(collecte->getCoord(),livraison->getCoord());
        test->setArriveLivraison(time);
        if(time < livraison->getOuverture())
            time = livraison->getOuverture();
        if(time > livraison->getFermeture())
            ret = true;
        else
        {
            time += livraison->getTempservice();
            test->setDepartLivraison(time);
            time += p->Calcul_dist(p->_lieu[0]->getCoord(),livraison->getCoord());
            if(time > p->_lieu[0]->getFermeture())
                ret = true;
        }
    }
    return ret;
}

/**
 * \fn int  Calcul_dist(Point a, Point b)
 * \brief Methode qui teste la distance entre 2 points
 * \param a Lieu 1
 * \param b Lieu 2
 * \return dist la distance entre les deux points
 *
 */
 int  Program::Calcul_dist(Point a, Point b)
 {
     int deltax = a.x - b.x;
     int deltay = a.y - b.y;
     return ((int)sqrt((double)(deltax*deltax + deltay*deltay)));
 }

/**
 *\fn bool compare_distance(chromosome * elt1, chromosome * elt2)
 * \brief Methode pour le trie des listes de chromosomes
 * \param elt1
 * \param elt2
 * \return booleen pour trier la liste de chromosome
 */
  bool compare_distance(chromosome * elt1, chromosome * elt2)
  {
      if(elt1->_vehiculeutilise < elt2->_vehiculeutilise)
          return true;
      else
          {
            if(elt1->_vehiculeutilise == elt2->_vehiculeutilise  && elt1->_dureetournee < elt2->_dureetournee )
                return true;
            else
                return false;
          }
  }


  /**
 *\fn  bool compare_arc(arc * first, arc * second)
 * \brief Methode pour le trie des arcs
 * \param first
 * \param second
 * \return booleen pour trier la liste d'arc
 */
  bool compare_arc(arc * first, arc * second)
  {
      return( first->gain > second->gain);

  }

 /**
 * \fn bool Predicat_tri_insertion(Requete * elt1, Requete * elt2)
 * \brief Predicat qui permet de choisir la meilleure requete
 * \param elt1 premier pointeur sur une requete
 * \param elt2 deuxieme pointeur sur une requete
 * \return vrai si ArriveTempo de elt1 < Arrive tempo de elt2
 */
  bool Predicat_tri_insertion(Requete * elt1, Requete * elt2)
  {
      return(elt1->getDepartLivraison() < elt2->getDepartLivraison());
  }

  
 /**
  * \fn void HeuInsertion();
  * \brief implementation de l'heuristique d'insertion classique
  *
  */
/*
 * on supposera que le nombre de vehicule est infini et que chaque requete est
 * une tournee faisable
 */
 
  void Program::HeuInsertion(chromosome * gene)
  {
      list<Requete *> requete_restante = gene->_liste;
      list<Requete *> requete_faisable;
      Tournee * tour;
      Requete * req;

      while(!requete_restante.empty())
      {
          requete_faisable = requete_restante;
          _tournee.push_back(tour = new Tournee());
          _temps = _lieu[0]->getOuverture();
          tour->setDateDepart(_temps);
          _lieuactuel = 0;
          while(!requete_faisable.empty())
          {
              requete_faisable.remove_if(Predicat_suppr);
              if(!requete_faisable.empty())
              {
                  req = requete_faisable.front();
                  requete_faisable.pop_front();
                  requete_restante.remove(req);

                  tour->AddService(
                  new Service(req->getCollecte(),req->getArriveCollecte(),
                              req->getDepartCollecte() ,req->getQuantite())
                                  );

                  tour->AddService(
                  new Service(req->getLivraison(),req->getArriveLivraison(),
                              req->getDepartLivraison() ,-req->getQuantite())
                                  );
                  _temps = req->getDepartLivraison();
                  _lieuactuel = req->getLivraison();
              }
          }
          tour->FinaliserTournee(this);
      }
      gene->_vehiculeutilise = _tournee.size();
      gene->_dureetournee = SommeDistance();
      _tournee.clear();

  }

  /**
   *\fn void Program::VarianteHeuInsertion()
   *\brief Implementation de la variante de l'heuristique d'insertion
   */
  void Program::VarianteHeuInsertion(chromosome * gene)
  {
      list<Requete*>::iterator it = gene->_liste.begin();
      list<Tournee*>::iterator t;
      int arrive ;
      int depart ;
      bool insert;

      while(it != gene->_liste.end())
      {
          t = _tournee.begin();
          insert = false;
          while(t != _tournee.end() && !insert)
          {
              insert = (*t)->InserableTournee(this,*(it));
              ++t;
          }
          if(!insert)
          {
              //creation d'une nouvelle tournee
              _tournee.push_back(new Tournee());
              arrive = _lieu[(*it)->getCollecte()]->getOuverture();
              depart = _lieu[(*it)->getCollecte()]->getTempservice() + arrive;
              (_tournee.back())->AddService(new Service((*it)->getCollecte(),arrive,depart,(*it)->getQuantite()));
              arrive = depart + Calcul_dist( _lieu[(*it)->getCollecte()]->getCoord(),_lieu[(*it)->getLivraison()]->getCoord());
              if(arrive < _lieu[(*it)->getLivraison()]->getOuverture())
                  depart = _lieu[(*it)->getLivraison()]->getOuverture();
              else
                  depart = arrive;
              depart += _lieu[(*it)->getLivraison()]->getTempservice();
              (_tournee.back())->AddService(new Service((*it)->getLivraison(),arrive,depart,-(*it)->getQuantite()));
          }
          ++it;
      }
      for(t = _tournee.begin(); t!= _tournee.end();++t)
      {
          (*t)->FinaliserTournee(this);
      }
      gene->_vehiculeutilise = _tournee.size();
      gene->_dureetournee = SommeDistance();
      _tournee.clear();
  }

    /**
  * \fn chromosome * Savings()
  * \brief Algorithme de Savings
  *
  */
chromosome * Program::Savings()
{
    Tournee * t;
    Service *collec, *livr;
    int client, arrivee, depart, quantite;
    int client1, arrivee1, depart1, quantite1,diff;
    // Initialisation des tournees
    list<Requete*>::iterator it;
    for(it=_requete.begin();it!=_requete.end();it++)
    {
        t = new Tournee();

        // Création de la collecte
        client = (*it)->getCollecte();
        diff = Calcul_dist(_lieu[(*it)->getCollecte()]->getCoord(),
                                _lieu[0]->getCoord());
        if(diff>(_lieu[(*it)->getCollecte()])->getOuverture())
            arrivee = diff;
        else arrivee = (_lieu[(*it)->getCollecte()])->getOuverture();
        depart = arrivee + (_lieu[(*it)->getCollecte()])->getTempservice();
        quantite = (_lieu[(*it)->getCollecte()])->getDemande();

        collec = new Service(client,arrivee,depart,quantite);
        t->AddService(collec);

        //creation de la livraison
        client1 = (*it)->getLivraison();
        arrivee1 = depart + Calcul_dist(_lieu[(*it)->getCollecte()]->getCoord(),
                                _lieu[(*it)->getLivraison()]->getCoord());

        if(arrivee1>_lieu[(*it)->getLivraison()]->getOuverture())
            depart1 = arrivee1;
        else depart1 = _lieu[(*it)->getLivraison()]->getOuverture();

        depart1 = depart1 + (_lieu[(*it)->getLivraison()])->getTempservice();
        quantite1 = (_lieu[(*it)->getLivraison()])->getDemande();

        livr = new Service(client1,arrivee1,depart1,quantite1);
        t->AddService(livr);

        (*it)->setTournee(t);
        _tournee.push_back(t);

    }


    //Initialisation de la liste de gain
    int gain;
    int ci0, c0j, cij ;
    int i, j;
    int gain2;
    int ci02, c0j2, cij2 ;
    int i2, j2;


    list<Requete*>::iterator it1;
    list<Requete*>::iterator it2, itTemp;
    list<arc*> L;
    arc *a;
    for(it1=_requete.begin();it1!=_requete.end();it1++)
    {

        ci0 = Calcul_dist(_lieu[i]->getCoord(),_lieu[0]->getCoord());
        itTemp = it1;
        itTemp++;
        for(it2=itTemp; it2!=_requete.end();it2++)
        {

            i =  (*it1)->getLivraison();
            j = (*it2)->getCollecte();


            ci0 = Calcul_dist(_lieu[i]->getCoord(),_lieu[0]->getCoord());
            c0j = Calcul_dist(_lieu[0]->getCoord(),_lieu[j]->getCoord());
            cij = Calcul_dist(_lieu[i]->getCoord(),_lieu[j]->getCoord());
            gain = ci0 + c0j - cij;

            i2 =  (*it2)->getLivraison();
            j2 = (*it1)->getCollecte();

            ci02 = Calcul_dist(_lieu[i2]->getCoord(),_lieu[0]->getCoord());
            c0j2 = Calcul_dist(_lieu[0]->getCoord(),_lieu[j2]->getCoord());
            cij2 = Calcul_dist(_lieu[i2]->getCoord(),_lieu[j2]->getCoord());
            gain2 = ci02 + c0j2 - cij2;

            if(gain>=gain2)
            {
                a = new arc();
                a->i=i;
                a->j=j;
                a->gain=gain;
                a->ri = (*it1);
                a->rj = (*it2);
                L.push_back(a);
            }
            else
            {
                a = new arc();
                a->i=i2;
                a->j=j2;
                a->gain=gain2;
                a->ri = (*it2);
                a->rj = (*it1);
                L.push_back(a);
            }
        }
    }
    // Trie sur les gains
    L.sort(compare_arc);

    list<arc*>::iterator itArc;
    //phases d'itérations
    for(itArc=L.begin();itArc!=L.end();itArc++)
    {
        Tournee *ti = (*itArc)->ri->getTournee();
        Tournee *tj = (*itArc)->rj->getTournee();
        if( (*itArc)->gain > 0)
        {
                if( ti->FusionPossible(tj, _lieu[(*itArc)->i],this)==true )
                {
                    ti->InsertTournee(tj,_lieu[(*itArc)->i],this);
                    (*itArc)->rj->setTournee(ti);
                    _tournee.remove(tj);
                }
        }

    }
    
    list<Tournee*>::iterator itTournee;
    for(itTournee=_tournee.begin();itTournee!=_tournee.end();itTournee++)
    {
        (*itTournee)->FinaliserTournee(this);
    }
   chromosome *c = new chromosome();
    c->_liste=_requete;
    c->_dureetournee = SommeDistance();
    c->_vehiculeutilise = _tournee.size(); 
    return c;
}

  /**
   *\fn bool compare_chrom(chromosome * first, chromosome * second)
   *\brief Méthode pour la comparaison des chromosomes
   */
bool compare_chrom(chromosome * first, chromosome * second)
{
  return(first->_vehiculeutilise == second->_vehiculeutilise
          && first->_dureetournee == first->_dureetournee);
}

/**
   *\fn chromosome * Program::algoGenetique()
   *\brief Algorithme de l'algo génétique
   */
chromosome * Program::algoGenetique()
{
	int i,j,iter, indiceC1,indiceC2;
	chromosome * temp;
	chromosome *f1,*f2, *f1Mut, *f2Mut;
	int nbFils;
	//initialisation de la population
	list<chromosome*> population, populationFils;
	list<chromosome*>::iterator li,li1,li2;
	bool test;
	for(i=0;i<TAILLE_POP;++i)
	{
		//Création des chromosomes aleatoire
		do
		{
			temp = generateChromosome();
                        VarianteHeuInsertion(temp);
			test=true;
			li=population.begin();
			while(li!=population.end() && test==true)
			{
				if((*li)->_dureetournee==temp->_dureetournee
                                  && (*li)->_vehiculeutilise == temp->_vehiculeutilise )
					test=false;
				++li;
			}
		}
		while(test==false);
		population.push_back(temp);
                // Fin création
	}
        //Trier la population selon le gain
      population.sort(compare_distance);

    //phase d'ameliaration iterative
	for(iter=0; iter < ITER_MAX ; ++iter)
	{
		populationFils.clear();
		nbFils=0;
		while(populationFils.size()<TAILLE_POP)
		{
			     //choix des chromosomes
                        do
			{
                            indiceC1 = rand()%(TAILLE_POP/3);
			    indiceC2 = rand()%TAILLE_POP;
                        }while(indiceC1 == indiceC2);

			li1 = population.begin();
			li2 = li1;

			for(i=0;i<indiceC1;++i)
				li1++;
			for(i=0;i<indiceC2;++i)
				li2++;
			croisementLOX((*li1), (*li2), &f1, &f2);

			// Traitement du fils 1
                         VarianteHeuInsertion(f1);

                        //Mutation du fils1
			f1Mut = mutation(f1);
			VarianteHeuInsertion(f1Mut);

			if(f1Mut->_vehiculeutilise < f1->_vehiculeutilise)
			   f1 = f1Mut;
                        
			// Insertion du fils 1 dans la population fils
			populationFils.push_back(f1);
			// Traitement du fils 2
                      
                        VarianteHeuInsertion(f2);

			//Mutation du fils2
			f2Mut = mutation(f2);
			VarianteHeuInsertion(f2Mut);

			if(f2Mut->_vehiculeutilise < f2->_vehiculeutilise)
				f2 = f2Mut;
			// Insertion du fils 1 dans la population fils
			populationFils.push_back(f2);
		}
		populationFils.sort(compare_distance);
		population.merge(populationFils,compare_distance);
		population.unique(compare_chrom);
		while(population.size()>TAILLE_POP)
			population.pop_back();

	}
	return population.front();
}

/**
   *\fn chromosome * Program::RechercheVal()
   *\brief Algorithme pour rechercher une valeur
   * \param r liste des paramètre
   * \param val valeur
   */
bool Program::RechercheVal(list<Requete*> *r, Requete * val)
{
    list<Requete*>::iterator it1;
    it1=r->begin();
    bool test = false;
    while(it1!=r->end() && test==false)
    {
        if((*it1) == val )
            test=true;
        it1++;
    }
    return test;

}

/**
   *\fn chromosome * Program::mutation(chromosome *c)
   *\brief Mutation d'un chromosome
*/
chromosome * Program::mutation(chromosome *c)
{
    int alea1,alea2;
    int i,j;
    chromosome *mut = new chromosome;
    mut->_liste=c->_liste;
    list<Requete *>::iterator it1 = mut->_liste.begin();
    list<Requete *>::iterator it2 = mut->_liste.begin();
    int nb=_requete.size();

    do
    {
        alea1 = rand()%nb;
        alea2 = rand()%nb;
    }while(alea1==alea2);

    for(i=0;i<alea1;++i)
        ++it1;
    for(j=0;j<alea2;++j)
        ++it2;

    Requete *r=(*it1);
    (*it1) = (*it2);
    (*it2) = r;

    return mut;
}

/**
   *\fn croisementLOX(chromosome *P1,chromosome *P2, chromosome **F1, chromosome **F2)
   *\brief Croisement de deux chromosomes
*/
void Program::croisementLOX(chromosome *P1,chromosome *P2, chromosome **F1, chromosome **F2)
{
   int i,alea;
   int nb= _requete.size();
   *F1=new chromosome;
   *F2=new chromosome;
   list<Requete*> restante1 = P1->_liste;//Valeur restante 1
   list<Requete*> restante2 = P2->_liste;//Valeur restante 2




   alea = rand()%nb;
   list<Requete*>::iterator it1; // iterateur sur P1
   list<Requete*>::iterator it2; // iterateur sur P2
   it1=P1->_liste.begin();
   it2=P2->_liste.begin();
   for(i=0;i<alea;++i)
   {
        (*F1)->_liste.push_back((*it2));
        restante1.remove((*it2));
        (*F2)->_liste.push_back((*it1));
        restante2.remove((*it1));
        it1++;
        it2++;
   }
   for(i=alea;i<nb;++i)
   {
       if(RechercheVal(&((*F1)->_liste),(*it1)))
       {
           (*F1)->_liste.push_back(restante1.front());
           restante1.pop_front();
       }
       else
       {
           (*F1)->_liste.push_back((*it1));
            restante1.remove((*it1));
       }
       if(RechercheVal(&((*F2)->_liste),(*it2)))
       {
           (*F2)->_liste.push_back(restante2.front());
           restante2.pop_front();
       }
       else
       {
           (*F2)->_liste.push_back((*it2));
            restante2.remove((*it2));
       }

   }
}

/**
   *\fn chromosome * Program::generateChromosome()
   *\brief génération d'un chromosome aléatoire
*/
chromosome * Program::generateChromosome()
{

  int i,alea,produit,x;
  list<Requete*> tab;
  produit = _requete.size();
  Requete **temp = new Requete*[produit];

  list<Requete*>::iterator it;
  i=0;
  for(it=_requete.begin();it!=_requete.end();++it)
  {
      temp[i]= (*it);
      i++;
  }
  x = produit;

  for(i=0;i<produit;++i)
  {
    alea = rand() %x;
    tab.push_front( temp[alea] );
    temp[alea] = temp[--x];
  }
  delete[] temp;

  chromosome *c = new chromosome();
  c->_liste=tab;
  return c;
}

/**
   *\fn int Program::SommeDistance()
   *\brief calcul la distance total
*/
int Program::SommeDistance()
  {
      list<Tournee *>::iterator it;
      int dist = 0;
      for(it = _tournee.begin();it != _tournee.end();++it)
      {
          dist += (*it)->getDateArrive() - (*it)->getDateDepart();
      }
      return dist;
  }
