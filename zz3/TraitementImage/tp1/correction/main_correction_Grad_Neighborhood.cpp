// TP1 Imagerie - Prise en main de la librairie CImg

#include "CImg.h"
using namespace cimg_library;

/******************************************
Main
******************************************/
int main(int argc,char **argv) 
{ 
 CImg<float>img("milla.bmp"), gradnorm(img.channel(0));
 
 CImg_3x3(I,float);                    // Define a 3x3x3 neighborhood
 cimg_for3x3(img,x,y,0,0,I,float)   // Loop over the volume, using the neighborhood I
 { 
  const float ix = 0.5f*(Inc-Ipc);    // Compute the derivative along the x-axis.
  const float iy = 0.5f*(Icn-Icp);    // Compute the derivative along the y-axis.
  gradnorm(x,y) = std::sqrt(ix*ix+iy*iy);  // Set the gradient norm in the destination image
 }

 CImgDisplay main_disp(gradnorm,"Norme du gradient");
 while (!main_disp.is_closed())
 {
      main_disp.wait();
 }
 return 0;
}
