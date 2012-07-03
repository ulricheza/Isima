////////////////////////////////////////////////////////////////////////////////
//                       TP 8 : Classification d'attributs                    //
////////////////////////////////////////////////////////////////////////////////

#include "CImg.h"

using namespace cimg_library;

/*******************************************************************************

                  Calcul de la fonction d'extraction d'attributs

*******************************************************************************/
CImg<> AttributsExtraction(CImg<> img)
{
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

 // Code

 return d;
}



/*******************************************************************************

                        Fonction de classification

*******************************************************************************/
CImg<unsigned char> Kmeans(CImg<> attributs,int ncl)
{
 CImg<unsigned char> res(attributs.width(),attributs.height(),1,1,0);

 // Code

 return res;
}

/*******************************************************************************

                                      main

*******************************************************************************/
int main()
{

 CImg<> img = CImg<>("fish.bmp").channel(0);

 int ncl = 2;    // Nombre de classes
 CImg<>               attributs = AttributsExtraction(img);
 CImg<unsigned char>  etiquette = Kmeans(attributs,ncl);

 // Affichage finale
 CImgDisplay dispImg(img,"Image originale");
 CImgDisplay dispRes(etiquette.normalize(0,255),"Image segmentée");

 while (!dispImg.is_closed())
 {
  dispImg.wait();
 }
 return 0;
}
