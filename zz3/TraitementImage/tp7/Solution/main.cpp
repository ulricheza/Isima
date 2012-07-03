////////////////////////////////////////////////////////////////////////////////
//                       TP 7 : Contours actifs implicites                    //
////////////////////////////////////////////////////////////////////////////////

#include "CImg.h"
#include "math.h"

#define MAX(a,b) (((a)<(b)) ? (b) : (a) )
#define MIN(a,b) (((a)<(b)) ? (a) : (b) )
#define SQR(a) (a*a)


using namespace cimg_library;


/*******************************************************************************

     Calcul de la position approximative du contour à partir de la carte
   levelset (psi): isocontour de valeur 0. On recherche donc l'ensemble des
    pixels possédant un voisin de signe opposé (interface entre domaine <0
                                et domaine >0)

*******************************************************************************/
CImg<float> ExtractContour(CImg<float> LevelSet)
{
 CImg<float> Contour(LevelSet.width(),LevelSet.height(),1,1);
 Contour.fill(0);

 CImg_3x3(I,float);
 cimg_for3x3(LevelSet,x,y,0,0,I,float)
 {
  if(Icc*Icp<=0 || Icc*Icn<=0 || Icc*Ipc<=0 || Icc*Inc<=0)
   Contour(x,y) = 1;
 }
 return Contour;
}

/*******************************************************************************

                     Affichage d'un contour dans une image

*******************************************************************************/
void DrawContour(CImg<float>* imgIn,CImg<float> Contour)
{
 const float color = 2*imgIn->max();

 cimg_forXY(Contour,x,y)
 {
  if(Contour(x,y) == 1)
   imgIn->draw_point(x,y,0,&color,0.7);
 }
}

/*******************************************************************************

     Initialisation du LevelSet (psi) à l'aide de la distance euclidienne
    signée. Le contour initial est un cercle de centre (x0,y0) et de rayon r

*******************************************************************************/
void InitLevelSet(CImg<float>* imgIn, int x0,int y0, int r)
{
 cimg_forXY(*imgIn,x,y)
 {
  (*imgIn)(x,y) = sqrt((x-x0)*(x-x0)+(y-y0)*(y-y0))-r;
 }
}

/*******************************************************************************

      Algorithme de propagation d'un contour implicite (modéle géodésique)

*******************************************************************************/
void Propagate(CImg<float> imgIn, CImg<float>* LevelSet)
{
 int   nbiter  = 5000;   // Nombre d'itération
 float delta_t = 2;      // Pas temporel
 float alpha   = 0.05;   // Pondération du terme de propagation
 float beta    = 0.8;    // Pondération du terme d'advection
 float ballon  = -0.01;  // Force ballon

 CImgList<float> grad = imgIn.get_gradient();
 CImg<float> norme_grad = (grad[0].get_sqr() + grad[1].get_sqr()).get_sqrt();
 CImg<float> unit(imgIn.width(),imgIn.height(),imgIn.depth(),imgIn.spectrum(),1);
 CImg<float> F = - unit.get_div( 1 + norme_grad.get_mul(norme_grad) + ballon);
 CImg<float> nablaPlus(imgIn.width(), imgIn.height(), imgIn.depth(), imgIn.spectrum(),0);
 CImg<float> nablaMoins(imgIn.width(), imgIn.height(), imgIn.depth(), imgIn.spectrum(),0);
 CImg<float> Fprop(imgIn.width(), imgIn.height(), imgIn.depth(), imgIn.spectrum(),0);
 CImg<float> Fadv(imgIn.width(), imgIn.height(), imgIn.depth(), imgIn.spectrum(),0);


 CImgList<float> gradF = F.get_gradient();
	 for (int i = 0; i < nbiter; i++)
	 {
         //Derivee a gauche
		  CImgList<float> gradMoins = LevelSet->get_gradient(0,-1);
        //Derivee a droite
        CImgList<float> gradPlus = LevelSet->get_gradient(0,1);

		  cimg_forXY(imgIn,x,y)
		  {
			 nablaPlus(x,y) = sqrt(
                              SQR(MAX(0, gradMoins[0](x,y))) +
                              SQR(MIN(0, gradPlus[0](x,y)))  +
                              SQR(MAX(0, gradMoins[1](x,y))) +
                              SQR(MIN(0, gradPlus[1](x,y)))
                              );
			 nablaMoins(x,y) = sqrt(
                              SQR(MAX(0,gradPlus[0](x,y)))   +
                              SQR(MIN(0, gradMoins[0](x,y))) +
                              SQR(MAX(0, gradPlus[1](x,y)))  +
                              SQR(MIN(0, gradMoins[1](x,y)))
                              );

			 Fprop(x,y)= -(
                        MAX(0,F(x,y)) * nablaPlus(x,y) +
                        MIN(0,F(x,y)) * nablaMoins(x,y)
                        );
			 Fadv(x,y) = -(
                        MAX(0, gradF[0](x,y)) * gradMoins[0](x,y) +
                        MIN(0, gradF[0](x,y)) * gradPlus[0](x,y)  +
								MAX(0, gradF[1](x,y)) * gradMoins[1](x,y) +
                        MIN(0, gradF[1](x,y)) * gradPlus[1](x,y)
                        );

			 (*LevelSet)(x,y) = (*LevelSet)(x,y) +
                              delta_t * (alpha * Fprop(x,y) + beta * Fadv(x,y));
		  }

	 }

}

/*******************************************************************************

                                      main

*******************************************************************************/
int main(int argc, char *argv[])
{
 // Ouverture de l'image "char256.bmp"
 CImg<float> img = CImg<float>("char256.bmp").channel(0);
 img.resize(img.width()/2,img.height()/2);

 // Définition d'un contour initial circulaire
 int x0 = img.width()/2;
 int y0 = img.height()/2;
 int r  = img.height()/4;

 CImg<float> levelset(img.width(),img.height(),1,1);
 InitLevelSet(&levelset,x0,y0,r);

 // Propagation du contour
 Propagate(img,&levelset);

 // Extraction du résultat
 CImg<float> Contour = ExtractContour(levelset);

 // Tracé du résultat dans l'image
 DrawContour(&img,Contour);

 // Affichage finale
 CImgDisplay dispSpatial(img,"Image Segmentée");

 while (!dispSpatial.is_closed())
 {
  dispSpatial.wait();
 }
 return 0;
}
