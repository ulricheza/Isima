/**
 * \file instance.cpp
 * \brief fichier soruce de la classe instance
 * \author Maxime Escourbiac Jean-Christophe Septier
 * \version 1.0
 * \date Lundi 1 novembre 2010
 */
 
#include "instance.h"

/**
 * \fn instance::instance(char * name )
 * \brief constructeur de la classe instance
 * \param name nom du fichier qui contient l'instance a etudier
 */
instance::instance(char *name)
{
   FILE *f;
   int i,j,machine,cout,valeur_arc_prec;
   sommet *prec,*init,*puit,*temp;
   arc * arc_temp;

   f=fopen(name,"r");
   if(f==NULL)
   {
      fprintf(stderr," Erreur d'ouverture du fichier ");
      exit(EXIT_FAILURE);
   }

   _graph = new graphe();

   //sommet initial
   init = new sommet();
   init->id_job = -1;
   init->id_machine = -1;
   _graph->V.push_back(init);
   //sommet puit
   puit = new sommet();
   puit->id_job = -2;
   puit->id_machine = -2;
   _graph->V.push_back(puit);

   fscanf(f,"%s",_nom);
   fscanf(f,"%d%d",&_nbJob,&_nbMachine);

   //Initialisation de la matrice d'ordre de machine et de job
   _ordreMachine = new int* [_nbJob];
   _ordreJob = new int* [_nbMachine];

   for(i=0;i<_nbJob;++i)
   {
      prec = init;
      valeur_arc_prec=0;
      _ordreMachine[i] = new int [_nbMachine];
      for(j=0;j<_nbMachine;++j)
      {
         fscanf(f,"%d%d",&machine,&cout);
         //Remplissage de la matrice
         _ordreMachine[i][j]=machine;
         temp = new sommet();
         temp->id_job = i;
         temp->id_machine = machine;
         _graph->V.push_back(temp);
           
         arc_temp = new arc();
         arc_temp->orig = prec;
         arc_temp->dest = temp;
         arc_temp->duree = valeur_arc_prec;
         valeur_arc_prec = cout;
         prec->sortie.push_back(arc_temp);
         temp->entree.push_back(arc_temp);//Modif
         _graph->E.push_back(arc_temp);
         prec = temp;
       }
       arc_temp = new arc();
       arc_temp->orig = prec;
       arc_temp->dest = puit;
       arc_temp->duree = valeur_arc_prec;
       prec->sortie.push_back(arc_temp);
       puit->entree.push_back(arc_temp);//Modif
       _graph->E.push_back(arc_temp);
   }
   for ( i=0 ; i < _nbMachine ; i++)
      _ordreJob[i] = new int [_nbJob];
   fclose(f);
}

/**
 * \fn instance::~instance()
 * \brief destructeur de la classe instance
 */

instance::~instance(void) 
{
   int i;
   for(i=0;i<(int)_graph->V.size();i++)
   {
      _graph->V[i]->entree.clear();
      _graph->V[i]->sortie.clear();
      delete _graph->V[i];
   }
   for(i=0;i<(int)_graph->E.size();i++)
   {
      delete _graph->E[i];
   }
   delete _graph;
   for(i=0;i<_nbJob;++i)
      delete _ordreMachine[i];
   delete _ordreMachine;
   for(i=0;i<_nbMachine;++i)
      delete _ordreJob[i];
   delete _ordreJob;
     
}

/**
 * \fn void instance::ajoutArcsVecteur(int * vecteur)
 * \brief ajoute les arc ajoute via le vecteur
 * \param vecteur
 */
void instance::ajoutArcsVecteur(int * vecteur)
{
   int i,j;
   int valJob,valMachine,nb;
   int *compteur,*compteurMac;

   nb=_nbJob*_nbMachine;
   
   //Initialise le compteur
   compteur=new int [_nbJob];
   compteurMac=new int [_nbJob];
   
   for(i=0;i<_nbJob;i++)
      compteur[i]=0;
   for(i=0;i<_nbMachine;++i)
      compteurMac[i]=0;
   
   //Remplir le tableau et donner l'ordre des jobs par machine
   for(i=0;i<nb;i++)
   {
      valJob=vecteur[i];
      valMachine=_ordreMachine[ valJob ][ compteur[valJob] ];
      _ordreJob[ valMachine ][ compteurMac[valMachine] ] = valJob;
      compteur[valJob]++;
      compteurMac[valMachine]++;
   }

   //Vérifier
   int numSommetDep,numSommetFin;
   int indiceSommetDep,indiceSommetFin;;
   int ind;
   sommet *dep, * fin;
   arc *arc_temp;
   for(i=0;i<_nbMachine;i++)
   {
      for(j=1;j<_nbJob;j++)
      {
         numSommetDep=_ordreJob[i][j-1];
         ind=0;
         while(_ordreMachine[numSommetDep][ind]!=i)
            ind++;
         indiceSommetDep=numSommetDep*_nbMachine+2+ind;
         numSommetFin=_ordreJob[i][j];
         ind=0;
         while(_ordreMachine[numSommetFin][ind]!=i)
            ind++;
         indiceSommetFin=numSommetFin*_nbMachine+2+ind;

         dep=_graph->V[indiceSommetDep];
         fin=_graph->V[indiceSommetFin];

         arc_temp = new arc();
         arc_temp->orig = dep;
         arc_temp->dest = fin;
         arc_temp->duree = (dep->sortie.front())->duree;

         dep->sortie.push_back(arc_temp);
         fin->entree.push_back(arc_temp);

         _sommetSortantModif.push_back(dep);
         _sommetEntrantModif.push_back(fin);
      } 
   }
   delete compteur;
   delete compteurMac;
}

/**
 * \fn void instance::supArc()
 * \brief supprime les arc ajoute via le vecteur
 *
 */
void instance::supArc()
{
   while (!_sommetEntrantModif.empty())
   {
      delete _sommetEntrantModif.back()->entree.back();
      _sommetEntrantModif.back()->entree.pop_back();
      _sommetEntrantModif.pop_back();
   }
   while (!_sommetSortantModif.empty())
   {
      _sommetSortantModif.back()->sortie.pop_back();
      _sommetSortantModif.pop_back();
   }
}


/**
 * \fn void instance::bellman()
 * \brief algorithme de calcul de plus long chemin
 *
 */
void instance::bellman()
{
   //declaration des variables
   register int i;
   register unsigned int j;
   int nb_sommet;
   list<sommet*>::iterator it;
   list<arc*>::iterator ia;

   //initialisation des variables
   nb_sommet = _graph->V.size();

   list<sommet*>li(nb_sommet); // creation de la liste
   it = li.begin();

   //initialisation de la liste de travail
   
   for(i=0;i<nb_sommet;++i)
   {
      (*it)= _graph->V[i];
      (*it)->distance = 0.0;
      (*it)->sommet_restant = (*it)->entree.size();

      ++it;
   }
   
   i=0;
   while(i<nb_sommet)
   {
      it = li.begin();
      //recherche d'un sommet avec tous ses precedents marques
      while((*it)->sommet_restant > 0)
          ++it;

      //mise a jour des sommets a traiter ainsi que des distances
      ia = (*it)->sortie.begin();
      j = 0;
      while(j < (*it)->sortie.size())
      {
         ((*ia)->dest->sommet_restant)--;
         /*MAJ distance si necessaire*/
         if(((*it)->distance + (*ia)->duree) > (*ia)->dest->distance )
            (*ia)->dest->distance = (*it)->distance + (*ia)->duree;

         ++ia;++j;
      }


      //MAJ pour retrouver le chemin critique
      ia = (*it)->entree.begin();
      j=0;
      while(j < (*it)->entree.size() && (*it)->distance - (*ia)->duree - (*ia)->orig->distance > EPS )
      {
         ++j;
         ++ia;
      }
      if(j == (*it)->entree.size())
         (*it)->prec = NULL;
      else 
         (*it)->prec = (*ia)->orig;
      //fin recherche chemin critique
      
      li.erase(it);
      ++i;
   }
   li.clear();
}
   

/**
 * \fn int * instance::gene_vecteur_alea()
 * \brief generateur du vecteur aleatoire
 *
 */
int * instance::gene_vecteur_alea()
{
  int i,alea,produit,x;
  int * tab = new int[_nbMachine*_nbJob];
  int * temp = new int[_nbMachine*_nbJob];
  
  produit = _nbMachine*_nbJob;
  for(i=0;i<produit;++i)
    temp[i]= i % _nbJob;
  
  x = produit;
  
  for(i=0;i<produit;++i)
  {
    alea = rand() %x;
    tab[i] = temp[alea];
    temp[alea] = temp[x-- - 1];
  }
  delete[] temp;
  
  return tab;
}

/**
 * \fn  void instance::recherche_locale(int * vecteur,int itermax)
 * \brief fonction de recherche locale utilisant la methode de la descente
 * \param vecteur vecteur de Bierwith initial
 * \param itermax nombre d'iteration max
*
 */

void instance::recherche_locale(int * s,int itermax)
{
   int iter = 0,indice_cour,indice_prec,temp_ch,cour=1,prec=0;
   register int i,j;
   float t1,t2;
   bool fin = false;
   sommet * temp;
   vector <sommet*> chemin;

   //evaluer vecteur;
   ajoutArcsVecteur(s);
   bellman();
   t1 = _graph->V[1]->distance;

   //generation chemin critique
   temp = _graph->V[1]->prec;
   while(temp != NULL)
   {
      chemin.push_back(temp);
      temp = temp->prec;
   }

   while(!fin && iter<itermax)
   {
      while( chemin[cour] != _graph->V[0] && chemin[cour]->id_job == chemin[prec]->id_job)
      {
         prec++;
         cour++;
      }
      if(chemin[cour] == _graph->V[0])
         fin = true;
      else
      {
         //reformation du vecteur s
         indice_cour=0;
         indice_prec=0;
         i=0;j=0;
         while(_ordreMachine[chemin[cour]->id_job][i] != chemin[cour]->id_machine)
            i++;
         while(j != i+1)
         {
            if(s[indice_cour] == chemin[cour]->id_job)
               ++j;
            ++indice_cour;
         }
         --indice_cour;

         i=0;j=0;
         while(_ordreMachine[chemin[prec]->id_job][i] != chemin[prec]->id_machine)
            i++;
         while(j != i+1)
         {
            if(s[indice_prec] == chemin[prec]->id_job)
               ++j;
            ++indice_prec;
         }
         --indice_prec;
		 temp_ch = s[indice_prec];
         s[indice_prec]=s[indice_cour];
         s[indice_cour]=temp_ch;
         
		 supArc();
		 ajoutArcsVecteur(s);
		 bellman();
         t2 = _graph->V[1]->distance;
         if(t1 > t2)
         {           
            t1 = t2;
            while(!chemin.empty())
               chemin.pop_back();
            temp = _graph->V[1]->prec;
            while(temp != NULL)
            {
               chemin.push_back(temp);
               temp = temp->prec;
            } 
               prec = 0;
               cour = 1;   
         }
         else
         {
            temp_ch = s[indice_prec];
            s[indice_prec]=s[indice_cour];
            s[indice_cour]=temp_ch;
            prec++; 
            cour++;
			supArc();
			ajoutArcsVecteur(s);
			bellman();
         }
         ++iter;
      }
   }
}

/**
 * \fn int * instance::mutation(const int * tab);
 * \brief fonction de mutation d'un vecteur
 * \param tab vecteur a muter
 * \return le vecteur mute
 */

int * instance::mutation(const int * tab)
{
   int *tab2;
   int alea,alea2,temp,i;
   int nb=_nbMachine*_nbJob;
   tab2 = new int[nb];
   for(i=0;i<nb;i++)
      tab2[i]=tab[i];
   
   alea = rand() %nb;

    do{
      alea2 = rand() %nb;
   }while(alea==alea2);

   temp=tab2[alea];
   tab2[alea]=tab2[alea2];
   tab2[alea2]=temp;

   return tab2;
}

/**
 * \fn void instance::croisementLOX(int *P1,int *P2, int **F1, int **F2)
 * \brief fonction de croisement de 2 vecteurs
 * \param P1 vecteur pere
 * \param P2 vecteur pere
 * \param F1 vecteur fils
 * \param F2 vecteur fils
 */

void instance::croisementLOX(int *P1,int *P2, int **F1, int **F2)
{
   int i,alea;
   int *compteurF1, *compteurF2;
   int nb=_nbMachine*_nbJob;
   *F1=new int[nb];
   *F2=new int[nb];

   alea = rand()%nb;
   compteurF1=new int[_nbJob];
   compteurF2=new int[_nbJob];
   for(i=0;i<_nbJob;i++)
   {
      compteurF1[i]=0;
      compteurF2[i]=0;
   }

   for(i=0;i<alea;i++)
   {
     (*F1)[i]=P2[i];
     compteurF1[P2[i]]++;

     (*F2)[i]=P1[i];
     compteurF2[P1[i]]++;
   }
   int j1=alea,j2=alea;
   for(i=0;i<nb;i++)
   {
    if(compteurF1[P1[i]]!=_nbMachine)
    {
        (*F1)[j1]=P1[i];
             compteurF1[P1[i]]++;
		 j1++;
    }

    if(compteurF2[P2[i]]!=_nbMachine)
    {
        (*F2)[j2]=P2[i];
          compteurF2[P2[i]]++;
		j2++;
    }
   }
}
