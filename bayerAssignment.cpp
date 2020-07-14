//Mac OS: g++ -o bayerAssignment.exe bayerAssignment.cpp -O2 -lm -lpthread -I/usr/X11R6/include -L/usr/X11R6/lib -lm -lpthread -lX11
// ./bayerAssignment.exe to load an image
#include <iostream>
#include "/Users/brittanyprice/Documents/Spring_2019_Courses/CSC_370/C++_Assignments/BayerFilter/CImg-2.5.0/CImg.h"

using namespace cimg_library;
using namespace std;


int main() {
 
    CImg<unsigned char> orig;
  CImg<unsigned char> image("CaptainAmerica.bmp");
  CImg<unsigned char> original("Batman-vs-Captain-America.bmp");
  CImg<unsigned char> bf("WallyWest.bmp");
    
//    orig.load("CaptainAmerica.bmp");
//    orig.load("Batman-vs-Captain-America.bmp");
    orig.load("WallyWest.bmp");

   
  //Create empty image to fill in with colored Bayer Filter
CImg<unsigned char> bayerFilter(orig.width(), orig.height(), 1, 3, 0);
//
//
//  //Copy over green intensities (every other pixel)
  for (int i = 0; i < orig.width(); i++){
      for(int j = i%2; j < orig.height(); j+=2){
         //Copy over green channel intensity for this pixel
         bayerFilter(i,j,0,1) = orig(i,j,0,1);
         //red and blue are zero
         bayerFilter(i,j,0,0) = 0.0;
         bayerFilter(i,j,0,2) = 0.0;
      }
  }

  //Copy over blue intensities (every other pixel of every other row)

    for (int i = 0; i < orig.width(); i+=2){
        for(int j = (i+1)%2; j < orig.height();j+=2){
            //Copy over blue channel intensity for this pixel
            bayerFilter(i,j,0,2) = orig(i,j,0,2);
            //red and green are zero
            bayerFilter(i,j,0,0) = 0.0;//turns on green
            bayerFilter(i,j,0,1) = 0.0;
        }
    }
//
  //Copy over red intensities (every other pixel of every other row)
    for (int i = 1; i < orig.width(); i+=2){
        for(int j = (i+1)%2; j < orig.height();j+=2){//(i+1)%2 prevents
            //Copy over red channel intensity for this pixel
            bayerFilter(i,j,0,0) = orig(i,j,0,0);
            //green and blue are zero
            bayerFilter(i,j,0,1) = 0.0;//turns on green
            bayerFilter(i,j,0,2) = 0.0;//commenting out makes this blue-green
        }
    }

  //Display and save filtered image
//    CImgDisplay disp(bayerFilter);
//    while (!disp.is_closed()){
//        disp.wait();
//    }
//
//    bayerFilter.save("bayerFilter.bmp");
    
//    CImgDisplay display(bayerFilter);
//    while (!display.is_closed()){
//        display.wait();
//    }
//    bayerFilter.save("bayerFilter2.bmp");
//
//    CImgDisplay finalDisp(bayerFilter);
//    while (!finalDisp.is_closed()){
//        finalDisp.wait();
//    }
//    bayerFilter.save("thirdBayerImage.bmp");
    

  //Reconstruct image from filter
  //Fill in here//
    
    CImg<unsigned char> demosaic(bayerFilter.width(), bayerFilter.height(), 1, 3, 0);
    //Copy over green intensities (every other pixel)
    for (int i = 0; i < bayerFilter.width(); i++){
        for(int j = 0; j < bayerFilter.height(); j++){

            if( i > 0 && i < bayerFilter.width() && j > 0 && j < bayerFilter.height()){
                if(i%2==0 && j%2==0){//green with blue on top/bottom
                    demosaic(i,j,0,1) = bayerFilter(i,j,0,1);
                    demosaic(i,j,0,0) = (bayerFilter(i+1,j,0,0) + bayerFilter(i-1, j,0,0))/2;
                    demosaic(i,j,0,2) = (bayerFilter(i,j+1,0,2) + bayerFilter(i, j-1, 0,2))/2;
                }
                else if(i%2!=0 && j%2!=0){//blue on the sides
                    demosaic(i,j,0,1) = bayerFilter(i,j,0,1);
                    demosaic(i,j,0,0) = (bayerFilter(i,j+1,0,0) + bayerFilter(i, j-1,0,0))/2;
                    demosaic(i,j,0,2) = (bayerFilter(i+1,j,0,2) + bayerFilter(i-1, j, 0,2))/2;
                }

                else if(i%2==0 && j%2!=0){//always blue; average red and green
                    demosaic(i,j,0,2) = bayerFilter(i,j,0,2);
                    demosaic(i,j,0,0) = (bayerFilter(i-1,j+1,0,0) + bayerFilter(i-1,j-1,0,0) + bayerFilter(i+1,j+1,0,0) + bayerFilter(i+1,j-1,0,0))/4;//red

                    demosaic(i,j,0,1) = (bayerFilter(i+1,j,0,1) + bayerFilter(i-1,j,0,1) + bayerFilter(i,j+1,0,1) + bayerFilter(i,j-1,0,1))/4;//green
                }
                else if (i%2!=0 && j%2==0){//always red; average green and blue
                    demosaic(i,j,0,0) = bayerFilter(i,j,0,0);

                    demosaic(i,j,0,1) = (bayerFilter(i+1,j,0,1) + bayerFilter(i-1,j,0,1) + bayerFilter(i,j+1,0,1) + bayerFilter(i,j-1,0,1))/4;//green

                    demosaic(i,j,0,2) = (bayerFilter(i-1,j+1,0,2) + bayerFilter(i-1,j-1,0,2) + bayerFilter(i+1,j+1,0,2) + bayerFilter(i+1,j-1,0,2))/4;//blue
                }
            }

        else{
            demosaic(i,j,0,0) = 0.0;
            demosaic(i,j,0,1) = 0.0;
            demosaic(i,j,0,2) = 0.0;
        }
    }
}


  //Display and save reconstructed image
  //Fill in here//

//    CImgDisplay reconImage(demosaic);
//    while (!reconImage.is_closed()){
//        reconImage.wait();
//    }
//    demosaic.save("reconstructionImage.bmp");
//
    //Display and save filtered image
//    CImgDisplay newImage(demosaic);
//    while (!newImage.is_closed()){
//        newImage.wait();
//    }
//    demosaic.save("reconstructedImage2.bmp");
//
    CImgDisplay lastRecon(demosaic);
    while (!lastRecon.is_closed()){
        lastRecon.wait();
    }
    demosaic.save("finalReconstruction.bmp");
  
  return 0;
}
