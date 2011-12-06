//Matching avec cvMatchTemplate()
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include "iostream"
using namespace std;
using namespace cv;
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

 templ = cvLoadImage("templ2.JPG");
	if(!templ)
	{
		printf("Erreur \n");
        	return -1;

	}
src = cvLoadImage("img3.JPG");
if(!src)
	{
		printf("Erreur \n");
        	return -1;

	}
mask = cvCreateImage(cvGetSize(src),src->depth , 1);
hsv = cvCloneImage(src);
cvCvtColor(src, hsv, CV_BGR2HSV);



cvInRangeS(hsv, cvScalar(9,80, 0), cvScalar(30,240,255),mask);


cvSaveImage("mascara.JPG",mask);
src = cvLoadImage("mascara.JPG"/*"mascara.JPG"*/);//src = cvLoadImage("img.JPG", 0);
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
    //définitions de points
    CvPoint cadre_pt1 = cvPoint( (src->width - templ->width) / 2 , (src->height - templ->height) / 2);
    CvPoint cadre_pt2 = cvPoint(cadre_pt1.x + templ->width , cadre_pt1.y + templ->height);



 /*   CvCapture* capture = cvCreateCameraCapture( CV_CAP_ANY );
    if( !capture )
        return 1;
    if(!cvGrabFrame( capture ))
        return 2;
    
*/int key=1;

     cvSmooth(src,src,CV_MEDIAN,3);
	imshow("test",src);

    while (1/*(max_loc.x!=max_loc_ant.x) && (max_loc.y!=max_loc_ant.y) && (min_loc.x!=min_loc_ant.x) && (min_loc.x!=min_loc_ant.x)*/)
    {
		max_loc_ant.x=max_loc.x;
	max_loc_ant.y=max_loc.y;
	min_loc_ant.x=min_loc.x;
	min_loc_ant.y=min_loc.y;
        //si la touche 'échap' code ASCII '27' est appuyée, on quitte la boucle pour terminer le programme
        if( key == 27 ) break;

        //capture les frames dans l'image 'src'
        //src = cvRetrieveFrame( capture );

        //applique le filtre médian pour réduire le bruit
       // cvSmooth(src,src,CV_MEDIAN,3);

        //si la touche 'espace' code ASCII '32' est appuyée, on enregistre le template à partir de l'image 'src'
        //le template est un rectangle 200*300 centré dans l'image 'src'
       /* if (key == 32)
            {
            //dessine un rectangle noir autour de la zone qui est "photographiée"
            cvRectangle(src, cadre_pt1,cadre_pt2, cvScalar(0,0,0));

            //définition une région d'intérêt ROI
            CvRect roi = cvRect (cadre_pt1.x,cadre_pt1.y,templ->width,templ->height);

            //fixe la ROI à l'image
            cvSetImageROI(src,roi);

            //copie le rectangle sélectionné de 'src' à 'templ'
            cvCopy(src,templ);

            // libérer la Region Of Interest de 'src'
            cvResetImageROI(src);
            }*/

        cvMatchTemplate( src, templ, ftmp, 2);//trouver ce qui correspond à 'templ' dans 'src'
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

        //afficher la valeur maximale*100 de 'ftmp' pour chaque frame
        cout << max_val*100 << "===";

        //si la valeur maximale de 'ftmp' est supérieure au 'seuil'
        //dessiner un rectangle rouge utilisant les coordonnées des deux points 'max_loc' et 'max_loc2'
        if( max_val > seuil && max_val!=1 )
	 {
		cvRectangle(src, max_loc,max_loc2, cvScalar(0,0,255));
		printf("\nx1=%d   x2_x=%d    y1=%d    y2=%d",max_loc.x,max_loc2.x,max_loc.y,max_loc2.y);
		CvPoint centre;		
		if(max_loc.x>max_loc2.x)

			centre.x=max_loc2.x+41;//(int)((max_loc.x-max_loc2.x)/2);
		else
			centre.x=max_loc.x+41;(int)((max_loc2.x-max_loc.x)/2);	
		if(max_loc.y>max_loc2.y)

			centre.y=max_loc2.y+25;//(int)((max_loc.y-max_loc2.y)/2);		
		else

			centre.y=max_loc2.y+25;//(int)((max_loc2.y-max_loc.y)/2);	

		printf("\ncentrexl=%d    centrey=%d\n",centre.x,centre.y);	
 
float distance = 0;
int position=2;//0 gauche, 1 droite
CvPoint ptoref;
ptoref.x=((src->width)/2);
ptoref.y=((src->height));
if(ptoref.x>centre.x)	//figure a gauche
{
	position=0;	
	distance=sqrt(((ptoref.x-centre.x)*(ptoref.x-centre.x))+((ptoref.y-centre.y)*(ptoref.y-centre.y)));
}
else	//figure a droite
{
	position=1;	
	distance=sqrt(((centre.x-ptoref.x)*(centre.x-ptoref.x))+((ptoref.y-centre.y)*(ptoref.y-centre.y)));
}
CvPoint position_new;
position_new.x=((src->height)-(centre.y));
position_new.y=(centre.x-(src->width/2));
float distance2=sqrt((position_new.x*position_new.x)+(position_new.y*position_new.y));
printf("\n\ndistance1=%f distance2=%f",distance,distance2);
if(position==0)
	printf("\nFigure detecté à gauche à une distance de %f dans les coordonnés[%d,%d]",distance,position_new.x,position_new.y);
else
	printf("\nFigure detecté à droite à une distance de %f dans les coordonnés[%d,%d]",distance,position_new.x,position_new.y);

/*int hauteur=350;
int alfa=15;
int d_horizontale=1000;//cm
int distance2=((350*cos30)/sin30);
*/











	}


        cvNamedWindow( "out", CV_WINDOW_AUTOSIZE );
        cvShowImage( "out", src );
        cvNamedWindow( "template", CV_WINDOW_AUTOSIZE );
        cvShowImage( "template", templ );

        // On attend 10 ms
        key = cvWaitKey(1000);
	
        // On essaye de capturer la frame suivante
       // if(!cvGrabFrame( int centre_y=(int)((max_loc.y-max_loc2.y)/2);capture )) key = 27;

    }
while(1);
    // On détruit les fenêtres créées
    cvDestroyAllWindows();

    // On détruit la capture
   // cvReleaseCapture( &capture );

    return 0;

}

