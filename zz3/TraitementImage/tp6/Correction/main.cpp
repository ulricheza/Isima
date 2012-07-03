////////////////////////////////////////////////////////////////////////////////
//                          TP 6 : Flot optique                     //
////////////////////////////////////////////////////////////////////////////////

#include "CImg.h"
#include <math.h>

using namespace cimg_library;


CImg<> HornSchunck(CImg<> seq)
{
    CImg<> field(seq.width(),seq.height(),1,2);
 CImg<> field_moy;

 // Creation du noyau de filtrage: moyenneur
 CImg<float> Mt(3,3); Mt.fill(1/9.);

 // Initialisation du champ
 field.fill(0);

 // Calcul des gradients de l'image
 CImgList<> grad = seq.get_gradient("xyz",0);

 // Schémas iteratifs
 int nbiter = 50;
 float lambda = 10;

 for(int k=0;k<nbiter;++k)
 {
  // Calcul des versions moyennees du champ
  field_moy = field.get_convolve(Mt);

  cimg_forXY(field,x,y)
  {
   float temp = (grad[0](x,y)*field_moy(x,y,0)+grad[1](x,y)*field_moy(x,y,1)+grad[2](x,y))/(lambda*lambda+grad[0](x,y)*grad[0](x,y)+grad[1](x,y)*grad[1](x,y));
   field(x,y,0) = field_moy(x,y,0) - grad[0](x,y)*temp;
   field(x,y,1) = field_moy(x,y,1) - grad[1](x,y)*temp;
  }
 }

return field;
}

CImg<> LucasKanade(CImg<> seq)
{
 CImg<> field(seq.width(),seq.height(),1,2);

 cimg_forXYC(field,x,y,v)
  field(x,y,v) = 0.01;

 return field;
}

CImg<> LucasKanade2(CImg<> seq)
{
 CImg<> field(seq.width(),seq.height(),1,2);

 cimg_forXYC(field,x,y,v)
  field(x,y,v) = 0.01;

 return field;
}

/*******************************************************************************

                                    Main

*******************************************************************************/
int main()
{
 // Ouverture de l'image "Lena.bmp"
 CImg<> seq = CImg<>("rubic1.bmp").channel(0);
 seq.append(CImg<>("rubic2.bmp").channel(0),'z');

 CImg<> displacementHS  = HornSchunck(seq);
 CImg<> displacementLK  = LucasKanade(seq);
 CImg<> displacementLK2 = LucasKanade2(seq);

 // Affichage du champ résultat
 float color=500; unsigned int  sampling = 8; float  factor = 40; int  quiver_type = 0; float  opacity = 0.5;

 CImg<> imageHS = seq.get_slice(0).draw_quiver(displacementHS,&color,opacity,sampling,factor,quiver_type);
 CImgDisplay resHS_disp(imageHS,"Horn et Schunck");

 CImg<> imageLK = seq.get_slice(0).draw_quiver(displacementLK,&color,opacity,sampling,factor,quiver_type);
 CImgDisplay resLK_disp(imageLK,"Lucas et Kanade");

 CImg<> imageLK2 = seq.get_slice(0).draw_quiver(displacementLK2,&color,opacity,sampling,factor,quiver_type);
 CImgDisplay resLK2_disp(imageLK2,"Lucas et Kanade avec gestion des valeurs propres");

 while (!resLK_disp.is_closed())
 {

  resLK_disp.wait();
 }
  return 0;
}
