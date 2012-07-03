#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

#include "CImg.h"


using namespace cimg_library;
using namespace std;

//Definition du filtre de Prewitt   
CImg<double> filtrePrewitt(3,3,1,1,
                           -1.0, -1.0, -1.0,
                            0.0,  0.0,  0.0,
                            1.0,  1.0,  1.0
                          );
		     
/******************************************
Calcul de la phase du gradient de l'image imageIn
******************************************/
CImg<float> Phase (CImg<unsigned char> imageIn)
{

//Calcul des produits de convolution afin d'obtenir les deux images
//representant le gradient de l'image initiale

 CImg<double> y = imageIn.get_convolve( filtrePrewitt );
 CImg<double> x = imageIn.get_convolve( filtrePrewitt.transpose() );

//calcul de la phase
 y.atan2(x);
 
 return y;  
}

/******************************************
Calcul d'un sigma_filtre sur l'image imageIn
******************************************/
CImg<float> sigmaFiltre (CImg<unsigned char> imageIn)
{
  double epsilon = 100.0;
  
  CImg <double> meanK(3,3,1,1,1);
  
 //Calcul des produits de convolution
 CImg<double> gradY = imageIn.get_convolve( filtrePrewitt );
 CImg<double> gradX = imageIn.get_convolve( filtrePrewitt.transpose() );
 
 //On obtient l'image du gradient
 CImg<double> grad = ( gradX.get_sqr() + gradY.get_sqr() ).get_sqrt();
 
 CImg<double> Sgrad = grad.get_convolve(meanK); // Calcul de la somme des gradients sur un voisinage 3*3
 
 CImg<double> rap = imageIn.get_div((grad+epsilon));
 
 CImg_3x3(I,float);   
 CImg<double> res(imageIn.width(),imageIn.height(),1,1);       
 cimg_for3x3(rap,x,y,0,0,I,float)   
 { 
    res(x,y) = (Ipp+Ipc+Ipn+Icp+Icc+Icn+Inp+Inc+Inn)/(Sgrad(x,y)+epsilon);
  }

  return res;
}

/******************************************
Main
******************************************/
int main(int argc,char **argv) 
{ 
	cimg_usage("TP2 Imagerie - filtrage spatial");

	const string name_i   = cimg_option("-i","barbara.bmp","Image");

	CImg<unsigned char> image(name_i.c_str()); 
	
	CImg<float> resultPh = Phase(image);
	CImg<float> resultSg = sigmaFiltre(image);

	CImgDisplay main_disp(image,"Visualisation");
        CImgDisplay resP_disp(resultPh,"Phase du Gradient");
        CImgDisplay resS_disp(resultSg,"Sigma_filtre de l'image");
	
        while ( !main_disp.is_closed() ) 
	{ 
		main_disp.wait(); 
	}


return 0; 
}
