// TP1 Imagerie - Prise en main de la librairie CImg

#include "CImg.h"
using namespace cimg_library;

/******************************************
Main
******************************************/
int main(int argc,char **argv) 
{ 
 CImg<float>img("milla.bmp"), dest(img);
 CImgList<> G = img.get_gradient("xy",0);
 dest = (G[0].get_sqr() + G[1].get_sqr()) .get_sqrt();

 CImgDisplay main_disp(dest,"Norme du gradient");
 while (!main_disp.is_closed())
 {
      main_disp.wait();
 }
 return 0;
}
