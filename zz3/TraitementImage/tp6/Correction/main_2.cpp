////////////////////////////////////////////////////////////////////////////////
//                          TP 6 : Flot optique                      //
////////////////////////////////////////////////////////////////////////////////

#include "../TP0/CImg.h"
#include <iostream.h>
#include <math.h>

using namespace cimg_library;


CImg<> HornSchunck(CImg<> seq)
{
 CImg<> field(seq.width()(),seq.height(),1,2);
 CImg<> fieldb(seq.width()(),seq.height(),1,2);

    CImg<> mask(3,3);
	for (int i = 0; i < 3; i++){
		for(int j =0; j < 3; j++){
			mask(i,j) = 1.0/9.0;
		}}

	float lambda = 10;
 cimg_forXYV(field,x,y,v)
	field(x,y,v) = 0;

  CImg<float>  ukb(seq.width()(),seq.height()), vkb(seq.width()(),seq.height());
  float alpha;
  CImgList<float> grad = seq.get_gradient();

  for(int i=0; i < 50; i++)
  {
	  fieldb = field.get_convolve(mask);
	  		 //ukb = (field.get_convolve(mask))[0];
			  //vkb = (field.get_convolve(mask))[1];
	  for(int x = 0; x < seq.width()(); x++){
		  for(int y = 0; y < seq.height(); y++){

			  alpha = ( grad[0](x,y)*fieldb(x,y,0) + grad[1](x,y)*fieldb(x,y,1) + grad[2](x,y))/(lambda * lambda + grad[0](x,y)*grad[0](x,y) + grad[1](x,y)*grad[1](x,y));

			  field(x,y,0) = fieldb(x,y,0) - grad[0](x,y)*alpha;
			  field(x,y,1) = fieldb(x,y,1) - grad[1](x,y)*alpha;
 }}}

 return field;
}
/*
CImg<> LucasKanade(CImg<> seq)
{
 CImg<> field(seq.width()(),seq.height(),1,2);

 cimg_mapXYV(field,x,y,v)
  field(x,y,v) = 1;

 return field;
}*/

/*******************************************************************************

                                    Main

*******************************************************************************/
int main()
{
 // Ouverture de l'image "Lena.bmp"
 CImg<> seq = CImg<>("rubic1.bmp").channel(0);
 seq.append(CImg<>("rubic2.bmp").channel(0),'z');

 CImg<> displacementHS  = HornSchunck(seq);
 /*CImg<> displacementLK  = LucasKanade(seq);
 CImg<> displacementLK2 = LucasKanade2(seq);
*/
 // Affichage du champ résultat
 float color=500; unsigned int  sampling = 8; float  factor = 40; int  quiver_type = 0; float  opacity = 0.5;

 CImg<> imageHS = seq.get_slice(0).draw_quiver(displacementHS,&color,opacity,sampling,factor,quiver_type);
 CImgDisplay resHS_disp(imageHS,"Horn et Schunck");

 //CImg<> imageLK = seq.get_slice(0).draw_quiver(displacementLK,&color,sampling,factor,quiver_type,opacity);
 //CImgDisplay resLK_disp(imageLK,"Lucas et Kanade");

 //CImg<> imageLK2 = seq.get_slice(0).draw_quiver(displacementLK2,&color,sampling,factor,quiver_type,opacity);
 //CImgDisplay resLK2_disp(imageLK2,"Lucas et Kanade avec gestion des valeurs propres");

 while (!resHS_disp.is_closed )
 {

  resHS_disp.wait();
 }
  return 0;
}
