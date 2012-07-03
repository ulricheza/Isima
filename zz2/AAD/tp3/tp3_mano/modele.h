/**
 * \file modele.h
 * \author Maxime Escourbiac Jean Christophe
 * \version 0.1
 * \date 19 novembre 2010
 */
 
 #ifndef __MODELE_H__
 #define __MODELE_H__

 #include <iostream>
 #include <cstdio>
 #include <cstdlib>
 #include <cmath>
 #include <list>
 
 using namespace std;

 class Pb;
 
 class Ville
 {
   private:
     int _node;
	  int _x;
	  int _y;
	  double _distance;
	public:
     Ville() {}
     ~Ville() {}
	  double calcul_distance(Ville * voisin);
     friend class Pb;
     friend bool compare_distance(Ville * v1, Ville * v2);
 };

 class Pb
 {
    private:
       int _dimension;
	    list<Ville*> _ville_restante;
	    list<Ville*> _chemin;
    public:
       Pb() {}
       ~Pb() {}
       void lecture_fic(char * name);
       void maj_dist(Ville * ref);
       void traitement();
	    void afficher_res();
};

bool compare_distance(Ville * v1, Ville * v2);

#endif
       	   