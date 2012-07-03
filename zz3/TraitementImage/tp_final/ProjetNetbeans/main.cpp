/** 
 * \file   main.cpp
 * \author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 * \date   4 décembre 2011, 18:06
 * \brief  Fichier main du mini-projet.
 * 
 * Spatio-temporal image segmentation using optical flow and clustering
 * algorithm
 * 
 */

#include <iostream>
#include "ClusteringSpatioTemporel.hpp"

/**
 * \fn int main(int argc, char** argv)
 * \brief Fonction main du mini-projet.
 * \param argc Nombre d'arguments passes en parametre du programme.
 * \param argv Liste des arguments passes en parametre du programme.
 * \return 0
 *  
 */
int main(int argc, char** argv) {
    
    if(argc == 3)
    {
        ClusteringSpatioTemporel clustering(argv[1],argv[2]);
                  
        //affichage de l'image originale
        CImgDisplay main_disp(clustering.getImageOriginale(),"Image originale");

        //Test sur le calcul de la norme du flot optique
        CImgDisplay main_dispFlotOptique(clustering.getNormeFlotOptique(),"Norme du flot optique");

        //Test sur le clustering
        clustering.clustering();
        CImgDisplay main_dispCluster0(clustering.getImage(0),"Fond statique");
        CImgDisplay main_dispCluster1(clustering.getImage(1),"Fond mobile");
        CImgDisplay main_dispCluster2(clustering.getImage(2),"Objets statiques");
        CImgDisplay main_dispCluster3(clustering.getImage(3),"Objets mobiles");

        while(1);
    }
    else
    {
        std::cerr << "Erreur dans les arguments" << std::endl;
    }
    return 0;
}

