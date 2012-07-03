#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

#include "CImg.h"


using namespace cimg_library;
using namespace std;


/******************************************
Calcul de la phase du gradient de l'image imageIn
******************************************/
CImg<float> Phase (CImg<unsigned char> imageIn)
{
 CImg <> Px(3,3,1,1), Py(3,3,1,1);

 Px(0,0)=-1; Px(0,1)=-1; Px(0,2)=-1;
 Px(1,0)=0;  Px(1,1)=0;  Px(1,2)=0;	
 Px(2,1)=1;  Px(2,0)=1;  Px(2,2)=1;

 Py(0,0)=-1; Py(0,1)=0; Py(0,2)=1;
 Py(1,0)=-1; Py(1,1)=0; Py(1,2)=1;	
 Py(2,1)=-1; Py(2,0)=0; Py(2,2)=1;

 CImg<double> img_x = imageIn.get_convolve(Px);
 CImg<double> res   = imageIn.get_convolve(Py);
 res.atan2(img_x);

 return res;
}

/******************************************
Calcul d'un sigma_filtre sur l'image imageIn
******************************************/
CImg<float> sigmaFiltre (CImg<unsigned char> imageIn)
{
  float epsilon = 100;
  CImg <> Px(3,3,1,1), Py(3,3,1,1), meanK(3,3,1,1,1);

  Px(0,0)=-1; Px(0,1)=-1; Px(0,2)=-1;
  Px(1,0)=0;  Px(1,1)=0;  Px(1,2)=0;	
  Px(2,1)=1;  Px(2,0)=1;  Px(2,2)=1;

  Py(0,0)=-1; Py(0,1)=0; Py(0,2)=1;
  Py(1,0)=-1; Py(1,1)=0; Py(1,2)=1;	
  Py(2,1)=-1; Py(2,0)=0; Py(2,2)=1;

  CImg<double> img_x = imageIn.get_convolve(Px);
  CImg<double> img_y = imageIn.get_convolve(Py);
  CImg<double> grad  = (img_x.get_sqr() +  img_y.get_sqr()) .get_sqrt();
  CImg<double> Sgrad = grad.get_convolve(meanK); // Calcul de la somme des gradients sur un voisinage 3*3
 
  CImg<> rap = imageIn.get_div((grad+epsilon));
 
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

	const string name_i   = cimg_option("-i","im.bmp","Image");

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
