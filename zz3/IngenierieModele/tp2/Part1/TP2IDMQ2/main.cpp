/* 
 * File:   main.cpp
 * Author: escourbi
 *
 * Created on October 19, 2011, 10:54 AM
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <sys/time.h>

#include "MersenneTwister.h"

using namespace std;

int main(int argc, char** argv) {

    //Variables servant pour la generation de texte
    MersenneTwister generator;
    ofstream        file;
    string          name;
    int             NTirage;
    int             NReplication;
    int             tailleTab;

    //Variables servant pour le calcul de performance
    //Attention code fonctionnant que sur Linux/Unix.
    struct timeval tv1,tv2;
    long long tempsS,tempUS;


    //On initialise le Mersenne Twister comme a la question Q1 pour avoir le meme rendu
    unsigned long   init[4] = {0x123, 0x234, 0x345, 0x456};
    unsigned long   length  = 4;

    cout << "Nombre de points demande?" << endl;
    cin  >> NTirage;
    cout << "Nombre de replication?" << endl;
    cin  >> NReplication;
    cout << "Nom du fichier genere? " << endl;
    cin  >> name;


    gettimeofday(&tv1,NULL); //Declenchement du chronometre

    generator.Init_by_array(init,length); //initialisation de MT

    cout << "---Generation du tableau MT---" <<endl;
    
    file.open(name.c_str(),ios::out);

    //Ecriture de l'en-tete
    file << "/**"                                                   << endl;
    file << " * \\file " << name                                    << endl;
    file << " * \\author Maxime Escourbiac Jean-Christophe Septier" << endl;
    file << " * \\brief Code C genere automatiquement "             << endl;
    file << " */"                                                   << endl;

    file << "#include <stdio.h>"  << endl;
    file << "#include <stdlib.h>" << endl;
    file << "#include <math.h>" << endl;
    file << "#include <sys/time.h>" << endl;
    file << "#include <unistd.h>" << endl;

    //Generation du tableau Mersenen Twister
    file << "float tabMT[] = {" << endl;

    tailleTab = NTirage * NReplication * 2 ;
    for (int i = 0; i < tailleTab ; ++i)
    {
        file << (float)generator.GenerateDouble() << "," << endl;
    }

    file << "};" << endl;

    //Generation du code utilisant le tableau genere
    cout << "---Generation du code---" << endl;
    
    file << "float calcul_pi();" << endl;
    file << "/**" << endl;
    file << "* \\fn int main(int,char**)" << endl;
    file << "* \\brief effectue une approximation de pi et effectue des calculs stats" << endl;
    file << "*" << endl;
    file << "*/" << endl;
    file << "int main(int argc, char** argv) {" << endl;
    file << "int    i;" << endl;
    file << "int    nb_exp;" << endl;
    file << "float moy = 0.0;" << endl;
    file << "struct timeval tv1,tv2;" << endl;
    file << "long long tempsS,tempUS;" << endl;
    file << "float piIntermediate;" << endl;
    file << "gettimeofday(&tv1,NULL);" << endl;
    file << "printf(\"approximateur de PI\\n\");" << endl;
    file << "printf(\"------------------------------------------\\n\");" << endl;
    file << "printf(\"------------------------------------------\\n\");" << endl;
    file << "for(i=1;i<" << NReplication << ";++i)" << endl;
    file << "{" << endl;
    file << "    printf(\"experience %d:\\n\",i);" << endl;
    file << "    piIntermediate = calcul_pi();" << endl;
    file << "    printf(\"Evaluation de pi : %lf \\n\",piIntermediate);" << endl;
    file << "    moy += piIntermediate;" << endl;
    file << "}" << endl;
    file << "printf(\"------------------------------------------\\n\");" << endl;
    file << "printf(\"------------------------------------------\\n\");" << endl;
    file << "printf(\"exploitation des resultat\\n\");" << endl;
    file << "moy /= " << (float) (NReplication-1) << ";" << endl;
    file << "printf(\"La moyenne est de : %lf \\n\",moy);" << endl;
    file << "gettimeofday(&tv2,NULL);" << endl;
    file << "tempsS  =(tv2.tv_sec-tv1.tv_sec);" << endl;
    file << "tempUS =(tv2.tv_usec-tv1.tv_usec);" << endl;
    file << "printf(\"temps d'execution : %lld s %lld us \\n\", tempsS, tempUS);" << endl;
    file << "return (EXIT_SUCCESS);" << endl;
    file << "}" << endl;
    file << "/**" << endl;
    file << "* \\fn float calcul_pi()" << endl;
    file << "* \\brief Effectue une experience sur la calcul de pi" << endl;
    file << "* \\return valeur de pi approxime" << endl;
    file << "*" << endl;
    file << "*/" << endl;
    file << "float calcul_pi()" << endl;
    file << "{" << endl;
    file << "int    i; " << endl;
    file << "int    valide = 0;" << endl;
    file << "float x;" << endl;
    file << "float y;" << endl;
    file << "static int gene = 0;" << endl;
    file << "for(i=0;i<" << NTirage <<";++i)" << endl;
    file << "{" << endl;
    file << "    x = tabMT[gene++];" << endl;
    file << "    y = tabMT[gene++];" << endl;
    file << "    if(sqrt(x*x+y*y)<= 1.0)" << endl;
    file << "       ++valide;" << endl;
    file << "}" << endl;
    file << "return(4.0*((float)valide/(float)" << NTirage << "));" << endl;
    file << "}" << endl;

    file.close();

    gettimeofday(&tv2,NULL); //arret du chronometrage
    tempsS  =(tv2.tv_sec-tv1.tv_sec);
    tempUS =(tv2.tv_usec-tv1.tv_usec);
    cout << "temps de generation de fichier source : " << tempsS << "s " << tempUS << "us" << endl;

    
    return (EXIT_SUCCESS);
}

