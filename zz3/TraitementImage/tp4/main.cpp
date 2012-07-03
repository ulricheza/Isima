////////////////////////////////////////////////////////////////////////////////
//                          TP 4 : Filtrage de Diffusion                      //
////////////////////////////////////////////////////////////////////////////////

#include "CImg.h"

using namespace cimg_library;

/*******************************************************************************

                             Filtrage de diffusion

*******************************************************************************/
CImg<> PeronaMalik2D(CImg<float> imageIn, int nbiter, float delta_t, float lambda, int option)
{
 CImg<> imgOut= imageIn;
 int i, j; 

 for (i = 0; i < nBiter ; i ++ )
 {
	for (j = 0 ; j < nBiter ; i++ )
	{
		imgOut(i,j) = imgOut(i,j) + delta_t * ( get_gradient 
	}
 }
 return imgOut;
}
/*******************************************************************************

                   Filtrage de diffusion spatio-temporel

*******************************************************************************/
CImg<> PeronaMalik2D_T(CImg<> imageIn, int nbiter, float delta_t, float lambda, int option)
{
 CImg<> imgOut= imageIn;

 
 return imgOut;
}
/*******************************************************************************

                                    Main

*******************************************************************************/
int main()
{
 // Ouverture de l'image "Lena.bmp"
 CImg<> img = CImg<>("TwoLeaveShop2front0330.bmp").channel(0);
 img.append(CImg<>("TwoLeaveShop2front0335.bmp").channel(0),'z');
 img.append(CImg<>("TwoLeaveShop2front0340.bmp").channel(0),'z');
 img.append(CImg<>("TwoLeaveShop2front0345.bmp").channel(0),'z');
 img.append(CImg<>("TwoLeaveShop2front0350.bmp").channel(0),'z');
 img.append(CImg<>("TwoLeaveShop2front0355.bmp").channel(0),'z');
 img.append(CImg<>("TwoLeaveShop2front0360.bmp").channel(0),'z');
 img.append(CImg<>("TwoLeaveShop2front0365.bmp").channel(0),'z');

 // Bruitage de l'image
 img.noise(-20);

 // Paramètres du filtre
 int   nbiter  = 30;
 float delta_t = 0.3;
 float lambda  = 1./5;
 int   model   = 2;

 //Filtrage 2D de la quatrième image
 CImg<> imgout2D = PeronaMalik2D(img.get_slice(3),nbiter,delta_t,lambda,model);

 // Affichage
 CImgDisplay dispSpatial(img.get_slice(3),"Image Originale");
 CImgDisplay dispFilter2D(imgout2D,"Image Filtree en 2D");

 //Filtrage 2D+T
 CImg<> imgout2DT = PeronaMalik2D_T(img,nbiter,delta_t,lambda,model);

 // Affichage
 CImgDisplay dispFilter2DT(imgout2DT.get_slice(3),"Image Filtrée en 2D+T");

  while (!dispSpatial.is_closed())
  {
	dispSpatial.wait();
  }
  return 0;
}
