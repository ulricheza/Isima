////////////////////////////////////////////////////////////////////////////////
//                       TP 8 : Classification d'attributs                    //
////////////////////////////////////////////////////////////////////////////////

#include "CImg.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace cimg_library;

/*******************************************************************************

                  Calcul de la fonction d'extraction d'attributs

*******************************************************************************/
CImg<> AttributsExtraction(CImg<> img)
{
   /*int p=2; // Nombre d'attributs
   CImg<> attributs(img.width(),img.height(),p);

   CImg_3x3(I,float);
   float moyenneMax = 0;
   float varianceMax = 0;

   cimg_for3x3(img,x,y,0,0,I,float) {

      //Calcul moyenne locale
      float m = (
                 Ipp + Ipc + Ipn +
                 Icp + Icc + Icn +
                 Inp + Inc + Inn
                 ) / 9.;

      attributs(x,y,0) = m;

      //Calcul variance
      attributs(x,y,1) = (
                           pow(Ipp - m, 2) +
                           pow(Ipc - m, 2) +
                           pow(Ipn - m, 2) +
                           pow(Icp - m, 2) +
                           pow(Icc - m, 2) +
                           pow(Icn - m, 2) +
                           pow(Inp - m, 2) +
                           pow(Inc - m, 2) +
                           pow(Inn - m, 2)
                        ) / 9.;

      //Recherche de la moyenne et de la variance max
      if (fabs(attributs(x,y,0)) > moyenneMax) {
         moyenneMax = fabs(attributs(x,y,0));
      }

      if (fabs(attributs(x,y,1)) > varianceMax) {
         varianceMax = fabs(attributs(x,y,1));
      }
   }


   cimg_forXY(attributs,x,y) {
      attributs(x,y,0) /= moyenneMax;
      attributs(x,y,1) /= varianceMax;
   }
   return attributs;*/

int p=2; // Nombre d'attributs
 CImg<> attributs(img.width(),img.height(),p);

 // Calcul de la moyenne et de la variance locale
 CImg<> N(9,9); 

 cimg_for9x9(img,x,y,0,0,N,float)
 {
  attributs(x,y,0) = N.mean();
  attributs(x,y,1) = N.variance();
 }

 return attributs;
}

/*******************************************************************************

                   Calcul de la distance au carrée

*******************************************************************************/
float d2(CImg<>* g_i,CImg<>* data,int x,int y)
{
   float d = 0.0;

   //Distance Euclidienne
   d = sqrt(pow((*g_i)(0) - (*data)(x,y,0), 2) + pow((*g_i)(1) - (*data)(x,y,1), 2));

 return d;
}



/*******************************************************************************

                        Fonction de classification

@param attibuts le vecteur des attributs
@param ncl le nombre de classes
*******************************************************************************/
CImg<float> Kmeans(CImg<> attributs,int ncl)
{
   CImg<float> res(attributs.width(),attributs.height(),1,1,0);

   /*
    * gi les centres de classes
    */
   CImg<>  * gi = new CImg<>[ncl];
   CImg<>  * temp_gi = new CImg<>[ncl];
   int	 * sum_classe = new int[ncl];


   //Initialisation des centres de classes
   for(int i = 0; i < ncl; i++) {

      gi[i] = CImg<>(2);
      temp_gi[i] = CImg<>(2);

      int randx = (int) (attributs.width() * (rand()/(float)RAND_MAX));
      int randy = (int) (attributs.height() * (rand()/(float)RAND_MAX));

      gi[i](0) = attributs(randx, randy, 0);
      gi[i](1) = attributs(randx, randy, 1);
   }

   bool again = true;

   //tan que pas convergence
   while(again) {
      again = false;

      for(int i = 0; i < ncl; i++) {

         temp_gi[i](0) = 0;
         temp_gi[i](1) = 0;
         sum_classe[i] = 0;
      }

         //Affectation du numero de classe a chaque pixel
         cimg_forXY(attributs, x, y) {

            int indiceMin = 0;
            float dGMin = d2(&(gi[0]), &attributs, x, y);

            for (int i = 1; i < ncl; i++) {

               float dG = d2(&(gi[i]), &attributs, x, y);

               if (dG < dGMin) {
                  indiceMin = i;
                  dGMin = dG;
               }
            }

            sum_classe[indiceMin]++;
            temp_gi[indiceMin](0) += attributs(x,y,0);
            temp_gi[indiceMin](1) += attributs(x,y,1);

            if (res(x,y) != (indiceMin + 1)) {
               again = true;
               res(x,y) = indiceMin + 1;
            }
         }

         //Calcul centre de gravite de chaque classes
         for(int i = 0; i < ncl; i++) {
            gi[i](0) = temp_gi[i](0) / sum_classe[i];
            gi[i](1) = temp_gi[i](1) / sum_classe[i];
         }
   }

   cimg_forXY(res, x, y) {
      res(x,y) = gi[(int)(res(x,y) - 1)](0);
   }

   delete[] gi;
   delete[] temp_gi;
   delete[] sum_classe;

 return res;
}

/*******************************************************************************

                                      main

*******************************************************************************/
int main(int argc, char ** argv)
{

    CImg<> img = CImg<>(argv[1]).channel(0).resize(-50., -50.);

    int ncl = 20;    // Nombre de classes
    CImg<>               attributs = AttributsExtraction(img);
    CImg<float>  etiquette = Kmeans(attributs,ncl);

    // Affichage finale
    CImgDisplay dispImg(img,"Image originale");
    CImgDisplay dispRes(etiquette.normalize(0,255),"Image segmentée");

    while (!dispImg.is_closed()){
      dispImg.wait();
    }

    return 0;
}
