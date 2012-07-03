////////////////////////////////////////////////////////////////////////////////
//                          TP 4 : Filtrage de Diffusion                      //
////////////////////////////////////////////////////////////////////////////////

#include "CImg.h"

using namespace cimg_library;

float functionG (float lambda, float s)
{
   //return (exp( -( lambda * s * lambda * s)));
     return 1.0/(1+ lambda * s * lambda * s);
}

/*******************************************************************************

                             Filtrage de diffusion

*******************************************************************************/

CImg<float> PeronaMalik2D(CImg<float> imageIn, int nbiter, float delta_t, float lambda, int option)
{
   float cN, cS, cW, cE;
   CImgList<float> gradBackward;
   CImgList<float> gradForward;
   CImg<float> imageOut = imageIn;


   for (int a = 0; a < nbiter; a++)
   {
      gradBackward = imageOut.get_gradient("xy",-1);
      gradForward = imageOut.get_gradient("xy",1);

      cimg_forXY(imageOut,x,y)
      {
         cN = functionG(lambda, gradBackward[1](x,y));
         cS = functionG(lambda, gradForward[1](x,y));
         cE = functionG(lambda, gradForward[0](x,y));
         cW = functionG(lambda, gradBackward[0](x,y));

         imageOut(x,y) += delta_t*(- cN * gradBackward[1](x,y)
                                   + cS * gradForward[1](x,y)
                                   + cE * gradForward[0](x,y)
                                   - cW * gradBackward[0](x,y));
      }

   }


 return imageOut;
}
/*******************************************************************************

                   Filtrage de diffusion spatio-temporel

*******************************************************************************/
CImg<> PeronaMalik2D_T(CImg<> imageIn, int nbiter, float delta_t, float lambda, int option)
{
   float cN, cS, cW, cE, cAv, cAp;
   CImgList<float> gradBackward;
   CImgList<float> gradForward;
   CImg<float> imageOut = imageIn;


   for (int a = 0; a < nbiter; a++)
   {
      gradBackward = imageOut.get_gradient("xyz",-1);
      gradForward = imageOut.get_gradient("xyz",1);

      cimg_forXYZ(imageOut,x,y,z)
      {
         cN = functionG(lambda, gradBackward[1](x,y,z));
         cS = functionG(lambda, gradForward[1](x,y,z));
         cE = functionG(lambda, gradForward[0](x,y,z));
         cW = functionG(lambda, gradBackward[0](x,y,z));
         cAv = functionG(lambda, gradBackward[2](x,y,z));
         cAp = functionG(lambda, gradForward[2](x,y,z));

         imageOut(x,y,z) += delta_t*(- cN  * gradBackward[1](x,y,z)
                                   + cS  * gradForward[1](x,y,z)
                                   + cE  * gradForward[0](x,y,z)
                                   - cW  * gradBackward[0](x,y,z)
                                   - cAv * gradBackward[2](x,y,z)
                                   + cAp * gradForward[2](x,y,z));
      }

   }


 return imageOut;
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
 img.noise(-5);

 // Paramètres du filtre
 int   nbiter  = 30;
 float delta_t = 0.3;
 float lambda  = 1./5;
 int   model   = 2;

 //Filtrage 2D de la quatrième image
 CImg<> imgout2D = PeronaMalik2D(img.get_slice(3),nbiter,delta_t,lambda,model);

 // Affichage
 CImgDisplay dispSpatial(img.get_slice(3).blur(4),"Image Originale");
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
