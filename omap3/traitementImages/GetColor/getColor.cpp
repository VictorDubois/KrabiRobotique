

// include standard OpenCV headers, same as before
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <iostream>
#include "cv.h"
#include "highgui.h"

// all the new API is put into "cv" namespace. Export its content
using namespace cv;
using namespace std;

// enable/disable use of mixed API in the code below.
#define DEMO_MIXED_API_USE 1

#define CV_EVENT_MOUSEMOVE      0
#define CV_EVENT_LBUTTONDOWN    1
#define CV_EVENT_RBUTTONDOWN    2
#define CV_EVENT_MBUTTONDOWN    3
#define CV_EVENT_LBUTTONUP      4
#define CV_EVENT_RBUTTONUP      5
#define CV_EVENT_MBUTTONUP      6
#define CV_EVENT_LBUTTONDBLCLK  7
#define CV_EVENT_RBUTTONDBLCLK  8
#define CV_EVENT_MBUTTONDBLCLK  9

int h = 0, s = 0, v = 0, tolerance = 40;
IplImage *image;

void my_mouse_callback( int event, int x, int y, int flags, void *param=NULL)
{

	CvScalar pixel;
	
	

if(event== CV_EVENT_LBUTTONDOWN )
	{

		pixel=cvGet2D(image,y,x);
		
	
		printf("\nB=%f, G=%f R=%f",pixel.val[0],pixel.val[1],pixel.val[2]);

		h = (int)pixel.val[0];
		s = (int)pixel.val[1];
		v = (int)pixel.val[2];

		
	}
	


}	


int main( )
{

	const char* imagename = "1.jpg";
	//const char* imagename = "1.jpg";

	IplImage *img = cvLoadImage(imagename);
	if(!img)
	{
		printf("Erreur \n");
        	return -1;

	}
	//Largueur image dans pixels
	int width = img->width;
	//Hauture image dans pixels
	int height = img->height;
	int step = img->widthStep/sizeof(uchar);  

	//Nombre canaux image
	int channels = img->nChannels; 
		



//Binarisation
int x, y;
CvScalar pixel;
IplImage *img_s,*hsv, *detec,*mask,*hsv_s, *mask_s, *image_new, *image_new2, *gray;
IplConvKernel *kernel;
int sommeX = 0, sommeY = 0;
int nbPixels = 0, nbPixels2 = 0;
// Key for keyboard event
char key=0;



//uchar* data = (uchar *)img->imageData; //cargamos los datos de la imagen en “data”
 

printf("\nstep=%d height=%d",step, height);
fflush(stdout);

//image = cvCloneImage(img);

cvNamedWindow("original", CV_WINDOW_AUTOSIZE);
cvShowImage("original", img);


image= cvCloneImage(img);

// Set up the callback
//cvSetMouseCallback("original_hsv", my_mouse_callback, (void*) image_hsv); //original_hsv

//FONCTION QUI DETECTE LES COULEURS RGB
cvSetMouseCallback("original", my_mouse_callback, (void*) image); //original


	while(1/*key != 'Q' && key != 'q'*/) 
	{


		// We wait 10 ms
		key = cvWaitKey(10);

	}



cvReleaseImage( &img );

cvDestroyWindow("original");

cvWaitKey(10);

return 0;

   
}
