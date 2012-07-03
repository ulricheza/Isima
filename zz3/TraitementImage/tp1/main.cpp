// TP1 Imagerie - Prise en main de la librairie CImg

#include <iostream>
#include "CImg.h"

using namespace cimg_library;
using namespace std;

/******************************************
Main (exemple)
******************************************/
/*
int main(int argc,char **argv) 
{ 
    CImg<unsigned char> image("lena.bmp"), visu(500,400,1,3,0);
    const unsigned char red[] = { 255,0,0 }, green[] = { 0,255,0 }, blue[] = { 0,0,255 };
    image.blur(2.5);
    CImgDisplay main_disp(image,"Click a point"), draw_disp(visu,"Intensity profile");
    while (!main_disp.is_closed() && !draw_disp.is_closed()) {
      main_disp.wait();
      if (main_disp.button() && main_disp.mouse_y()>=0) {
        const int y = main_disp.mouse_y();
        visu.fill(0).draw_graph(image.get_crop(0,y,0,0,image.width()-1,y,0,0),red,1,1,0,255,0);
        visu.draw_graph(image.get_crop(0,y,0,1,image.width()-1,y,0,1),green,1,1,0,255,0);
        visu.draw_graph(image.get_crop(0,y,0,2,image.width()-1,y,0,2),blue,1,1,0,255,0).display(draw_disp);
        }
      }
    return 0;
}
*/

/*******************************************
Main ( Calcul de gradient )
********************************************/
/*
int main(int argc,char **argv) 
{ 
    CImg<unsigned char> image("lena.bmp");
    image = image.get_channel(0);
    CImg<unsigned char> norme;
    CImgList<unsigned char> g =  image.get_gradient("XY",4);

    norme = (g(0).get_sqr() + g(1).get_sqr() ).get_sqrt();
    CImgDisplay main_disp(norme,"Image");

    while(1);
    return 0;
}
*/

/*******************************************
Main ( Calcul de gradient manuel )
********************************************/
int main(int argc,char **argv) 
{ 
    CImg<double> image("lena.bmp");
    
    int width  = image.width();
    int height = image.height(); 
    
    CImg<double> norme,normeManuel,gradX(width,height),gradY(width,height);
    int i,j;
    
    image = image.channel(0);

    //Calcul du gradient par la librairie CImg
    CImgList<double> g =  image.get_gradient("XY",0);

    norme = (g(0).get_sqr() + g(1).get_sqr() ).get_sqrt();
    CImgDisplay main_disp(norme,"Gradient calcule avec Cimg");
    
    
    
    //Calcul du gradient manuel
    for(i = 0; i < width - 1 ; ++i)
    {
       for(j = 0; j < height - 1 ; ++j)
       {
	  gradX(i,j) = image(i+1,j) - image(i,j);
	  gradY(i,j) = image(i,j+1) - image(i,j);
       }
       gradX(i,j) = 0;
    }
    
    for(j = 0; j < width - 1 ; ++j)
       gradY(height - 1,j) = 0;

    

    normeManuel = (gradX.get_sqr() + gradY.get_sqr() ).get_sqrt();
    CImgDisplay main_dispManuel(normeManuel,"Gradient calcule manuellement");

    while(1);
    return 0;
}