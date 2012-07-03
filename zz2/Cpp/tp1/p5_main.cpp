/**
 * \file p5_main.cpp
 * \brief programme principal partie 5
 * \author Maxime Escourbiac
 * \version 1.0
 * \date Mercredi 6 octobre 2010
 */


#include "p5_voiture.h"
#include "p5_parking.h"

using namespace std;

int main(int,char**)
{
   Voiture * parc[5],* obs;
   int i ;
   cout << "Creation du parc de voiture" << endl;
   parc[0] = new Voiture("renault","rouge","essence",80,5500,8.1,7.0,52.6,140.9);
   parc[1] = new Voiture("peugeot","blanche","diesel",140,3863,9.6,7.4,60.0,110.0);
   parc[2] = new Voiture("citroen","noire","hybride",75,4000,5.5,4.0,40.1,60.1);
   parc[3] = new Voiture("fiat","jaune","essence",65,4000,5.5,5.2,35.8,80.0);
   parc[4] = new Voiture("Ferrari","rouge","essence",400,7500,17.8,16.5,80.6,250.6);
   
   cout << "creation parking" << endl;
   Parking * hangar = new Parking(4);
   
   cout << "faire le plein des 4iere voiture..." << endl;
   for(i=0;i<4;i++)
    parc[i]->faire_plein();
   cout << "Simulation de conduite des voiture..." << endl;
   cout << "megane <== 400km" << endl;
   parc[0]->rouler(400.0,"autoroute");
   cout << "peugeot <== 300km" << endl;
   parc[1]->rouler(300.0,"ville");
   cout << "citroen <== 450km sur du parking" << endl;
   parc[2]->rouler(450.0,"parking");
   cout << "fiat <== 1400km" << endl;
   parc[3]->rouler(1400.0,"autoroute");
   cout << "ferrari <== 10km" << endl;
   parc[4]->rouler(10.0,"ville");
   
   cout << "Essence restant dans le reservoir" << endl;
   for(i=0;i<5;i++)
   {
       cout << "reservoir voiture " << i << ": " << parc[i]->getRESERVOIR() << " L" << endl;
       cout << "kilometrage voiture " << i << ": " << parc[i]->getKILOMETRAGE() << " Km" << endl;
   }
   
   cout << "nombre de voiture " << Voiture::getNOMBRE_VOITURE() << endl;
   cout << "pollution totale " << Voiture::getPOLLUTION() << endl;
   
   cout << "on gare les voitures" << endl;
   
   for(i=0;i<5;i++)
   {
      if(hangar->garer(parc[i]) == -1)
      {
         cout << "parking plein" << endl;
      }
      else
         cout << "voiture " << i << " garee" << endl;
   }
   
   cout << "on sort la voiture 2 du garage" << endl;
   hangar->sortir(parc[2]);
   
   cout << "voiture presente au garage" << endl;
   
   for(i=0;i<hangar->get_CAPACITE();i++)
   {
      obs = hangar->observer(i);
      if(obs)
      {
         cout << "voiture " << i << endl;
         cout << "marque : " << obs->getMARQUE() << "  couleur : " << obs->getCOULEUR() << endl;
      }
   }
   
   return 0;
}
