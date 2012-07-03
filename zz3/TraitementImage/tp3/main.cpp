////////////////////////////////////////////////////////////////////////////////
//                          TP 3 : Filtrage Fréquentiel                       //
////////////////////////////////////////////////////////////////////////////////

#include "CImg.h"
#include <math.h>

using namespace cimg_library;

/*******************************************************************************

    Calcul d'une image compos�e du module de image1 et de la phase de image2

*******************************************************************************/
CImg<unsigned char> Melange (CImg<unsigned char> imageIn1,CImg<unsigned char> imageIn2)
{
 CImg<unsigned char> imgOut(imageIn1.width(),imageIn1.height(),1,1,0);
 //get_FFT 0 - Reel / 1 - Imaginaire
 CImgList<float> FFT1 = imageIn1.get_FFT();
 CImgList<float> FFT2 = imageIn2.get_FFT();
 
 //Calcul du module de l'image 1
 CImg<float> mod = (FFT1[0].get_sqr() + FFT1[1].get_sqr()).get_sqrt();
 //Calcul de la phase de l'image 2
 CImg<float> phase = FFT2[1].get_atan2(FFT2[0]);
 
 //partie reel du melange des images
 CImg<float> reFinal(mod.get_mul(phase.get_cos()));
 //partie imaginaire du melange des images
 CImg<float> imFinal(mod.get_mul(phase.get_sin()));
 
 //On construit une liste pour faire la FFT inverse
 CImgList<float> final(reFinal, imFinal);
 
 //On fait FFT inverse, on recupere l'image (partie reelle) et
 //normalise pour passer dans un unsigned char
 imgOut = (final.get_FFT(true)[0]).normalize(0, 255);

 return imgOut;
}

/*******************************************************************************

                        Filtrage d'une image tram�e

*******************************************************************************/
CImg<unsigned char> Detramage (CImg<unsigned char> imageIn)
{
 CImg<unsigned char> imgOut(imageIn.width(),imageIn.height(),1,1,0);

 return imgOut;
}

/*******************************************************************************

      Filtrage Gaussien d'une image (avec un ecart-type spatial de 'sigma')

*******************************************************************************/
CImg<unsigned char> FiltrageGaussien (CImg<unsigned char> imageIn, float sigma)
{
 CImg<unsigned char> imgOut(imageIn.width(),imageIn.height(),1,1,0);

 return imgOut;
}

/*******************************************************************************

                                    Main

*******************************************************************************/
int main()
{
 ///////////////////////////////////////////////////////////////////////////////
 //                        Question 1: M�lange d'image                        //
 ///////////////////////////////////////////////////////////////////////////////

 // Ouverture des deux images
 CImg<unsigned char> imgClown("clown.bmp");
 CImg<unsigned char> imgGatlin("gatlin.bmp");

 // R�sultat du m�lange
 CImg<unsigned char> imgRes1 = Melange (imgClown.channel(0),imgGatlin.channel(0));

 // Affichage du r�sultat
 CImgDisplay dispClown(imgClown,"Question 1 : Image de Clown (1/3)");
 CImgDisplay dispGatlin(imgGatlin,"Question 1 : Image de Gatlin (2/3)");
 CImgDisplay dispRes1(imgRes1,"Question 1 : Image Melangee (3/3)");

 ///////////////////////////////////////////////////////////////////////////////
 //                        Question 2: Détramage                              //
 ///////////////////////////////////////////////////////////////////////////////

 // Ouverture de l'image "lena_trame.bmp"
 CImg<unsigned char> imgLenaTramee("lena_trame.bmp");

 // R�sultat du détramage
 CImg<unsigned char> imgRes2 = Detramage (imgLenaTramee.channel(0));

 // Affichage du r�sultat
 CImgDisplay dispTramee(imgLenaTramee,"Question 2 : Image de Lena Tramee (1/2)");
 CImgDisplay dispDetramee(imgRes2,"Question 2 : Image de Lena Detramee (2/2)");


 ///////////////////////////////////////////////////////////////////////////////
 //                        Question 3: Filtrage Gaussien                      //
 ///////////////////////////////////////////////////////////////////////////////

 // Ouverture de l'image "lena.bmp"
 CImg<unsigned char> imgLena("lena.bmp");

 // Ajout d'un bruit additif Gaussien
 imgLena.noise(-5);

 // Résultat du détramage
 float sigma = 1;
 CImg<unsigned char> imgRes3 = FiltrageGaussien (imgLena.channel(0),sigma);

 // Affichage du r�sultat
 CImgDisplay dispBruitee(imgLena,"Question 3 : Image de Lena Bruitee (1/2)");
 CImgDisplay dispDebruitee(imgRes3,"Question 3 : Image de Lena Debruitee (2/2)");


 while (!dispClown.is_closed())
 {
  dispClown.wait();
 }
 return 0;
}
