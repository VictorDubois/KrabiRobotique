//Matching avec cvMatchTemplate()
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include "iostream"
using namespace std;

/*enregistrez une image template en appuyant sur 'espace'
cette image sera recherchée dans la video issue de la webcam
matchtemplate retourne une valeur de corrélation pour chaque pixel de l'image
la valeur la plus grande de corrélation correspond très probablement au template recherché
pour un matching plus précis, il est possible de régler le seuil à partir duquel il y a matching
pour cela, observer dans la console la valeur maximale de corrélation pour chaque frame
puis agir sur la trackbar de seuil*/

int main() {

    //définition des images a utiliser
    IplImage *src,*hsv,*mask;//=cvCreateImage(cvSize(640,480), 8, 3);
    IplImage *templ;// = cvCreateImage(cvSize(200,300), 8, 3);

 templ = cvLoadImage("motif.JPG");
	if(!templ)
	{
		printf("Erreur \n");
        	return -1;

	}
src = cvLoadImage("image.JPG");
if(!src)
	{
		printf("Erreur \n");
        	return -1;

	}



    //définition de la taille(largeur, hauteur) de l'image ftmp
    int iwidth = src->width - templ->width + 1;
    int iheight = src->height - templ->height + 1;
    IplImage *ftmp = cvCreateImage(cvSize(iwidth,iheight),IPL_DEPTH_32F,1);

    //seuil qui pourra être réglé avec un trackbar pour une détection plus pertinente
    double seuil = 80.0;
    //le trackbar n'acceptant que des valeurs entières on utilise 'seuil_int'
    int seuil_int = (int) seuil;
//int center_x=0,center_y=0;
CvPoint min_loc_ant, max_loc_ant;
min_loc_ant.x=min_loc_ant.y=max_loc_ant.x=max_loc_ant.y=0;
CvPoint min_loc, max_loc;
min_loc_ant.x=min_loc_ant.y=max_loc_ant.x=max_loc_ant.y=2;
    

max_loc_ant.x=-1;
max_loc_ant.y=-1;
min_loc_ant.x=-1;
min_loc_ant.y=-1;
int key=1;

     cvSmooth(src,src,CV_MEDIAN,3);
int repite=0,premiermotiftrouve=0;

    while (repite==0)
    {
    

        cvMatchTemplate( src, templ, ftmp, CV_TM_CCOEFF_NORMED);//trouver ce qui correspond à 'templ' dans 'src'
        //src: l'image source capturée par la caméra
        //templ: le template qui sera recherché dans l'image source
        //ftmp: l'image qui contient le réultat du calcul
        //CV_TM_CCOEFF_NORMED: la méthode de calcul utilisée ici permet un matching plus pertinent mais au prix de plus de calcul


        //retrouver dans 'ftmp' les coordonnées du point ayant une valeur maximale
        double min_val, max_val;
        
        cvMinMaxLoc(ftmp, &min_val, &max_val, &min_loc, &max_loc);

        //défnir un deuxième point à partir du premier point et de la taille de 'ftmp'
        CvPoint max_loc2 = cvPoint(max_loc.x + templ->width, max_loc.y + templ->height);//définir le deuxième point en fonction de la taille du template

        //trackelfbar pour régler le seuil
        cvCreateTrackbar( "seuil", "out", &seuil_int, 100, NULL );

        // 'seuil' appartient à [0 1] alors que 'seuil_int' appartient à [0 100] donc:
        seuil = (double) seuil_int / 100.0;

       

        //si la valeur maximale de 'ftmp' est supérieure au 'seuil'
        //dessiner un rectangle rouge utilisant les coordonnées des deux points 'max_loc' et 'max_loc2'
        if( max_val > seuil && max_val!=1 )
	 {
		if(premiermotiftrouve==0)
		{	
			max_loc_ant.x=max_loc.x;
			max_loc_ant.y=max_loc.y;
			min_loc_ant.x=min_loc.x;
			min_loc_ant.y=min_loc.y;
			premiermotiftrouve=1;
		}
		else if((max_loc.x==max_loc_ant.x) && (max_loc.y==max_loc_ant.y) && (min_loc.x==min_loc_ant.x) && (min_loc.x==min_loc_ant.x))
		{
			repite=1;
		}
		cvRectangle(src, max_loc,max_loc2, cvScalar(0,0,255));
		printf("\nx1=%d   x2_x=%d    y1=%d    y2=%d",max_loc.x,max_loc2.x,max_loc.y,max_loc2.y);
		

	}


        cvNamedWindow( "out", CV_WINDOW_AUTOSIZE );
        cvShowImage( "out", src );
        cvNamedWindow( "template", CV_WINDOW_AUTOSIZE );
        cvShowImage( "template", templ );

        // On attend 10 ms
        key = cvWaitKey(1000);
	   }
while(1);
    // On détruit les fenêtres créées
    cvDestroyAllWindows();

     return 0;

}

