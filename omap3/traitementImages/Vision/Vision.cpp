#include "cv.h"
#include "highgui.h"
 
#include <cmath>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265
 
using namespace cv;
using namespace std;



// les paramètres pour applatir l'image reçue de la camèra.
// A regler selon la position de la camera sur le robot !
int alpha_=30., beta_=90., gamma_=90.;
int f_ = 500, dist_ =415;

// les parametres ci-dessous dependent de la resolution de la camera, des parametres pour applatir.
// ils servent a faire le lien entre la distance reelle sur la table et la distance mesure sur l'image.
// et aussi de detecter les cercles avec précision

double dminCentres=40.;	// la distance minimale entre les centres des cercles a detecter.
int rayonMin=13;	// le rayon minimal des cercles a detecter.
int rayonMax=192;	// le rayon maximal des cercles a detecter
	
int coteCase=350; 		// en mm, chaque case a une longueur de 100 pixels donc chaque pixel represente 3,5 mm.

// cette fonction prend en argument une matrice de 0 et de 1,
// et retourne si le  pourcentage des "1" est superieur à la valeur pourcentage donnée en argument.
bool estBlanc(Mat rect,double pourcentage) {
    bool estBlanc;
    Size taille = rect.size();
    double w = (double)taille.width, h = (double)taille.height;
    double nombreDesUns=countNonZero((Mat_<double>)rect);
    double pourcentageDesUns=nombreDesUns/(w*h);
    if (pourcentageDesUns>=pourcentage) {
	estBlanc=true;
    }
    else {
	estBlanc=false;
    }
    return estBlanc;
}


//cette fonction dit si le point est à l'interieur du rectangle 
bool estInterieur(Rect rectangle,Point point) {
    double x=rectangle.x;
    double y=rectangle.y;
    double w=rectangle.width;
    double h=rectangle.height;
    if ((point.x>=x)&&(point.y>=y)&&(point.x<=x+w)&&(point.y<=y+h)) {
	return true;
    }
    else return false;
}

// cette fonction donne le type du pion observé : 0 un simple pion, 1 une tour.
int pion(double longueur) {
    if (longueur<=20)
	return 0;
    else return 1;
}
 
int main(int argc, char** argv) {


    // indique si on a le flux video ou pas.
    bool video = false;
    
    // source est l'image vu par la camèra.
    // destination est l'image "vu" par le robot.
    // contours1 est l'image obtenue apres detection de contours sur l'image en 3 channals.
    // contours2 est l'image obtenue apres detection de contours sur l'image dans le channal G (Green).
    // cercles1 est un vecteur contenant les coordonnées et rayons des cercles dans l'image contours1
    // cercles2 est un vecteur contenant les coordonnées et rayons des cercles dans l'image contours2
    Mat source, destination, contours1, contours2;
    vector<Vec3f> cercles1, cercles2; 
    VideoCapture capture(0);

    // lecture des donnees : 
    if (argc >= 2) {
        // Si au moins un argument est précisé, on essaye de charger l'image
        cout << "Lecture de " << argv[1] << endl;
        source = imread(argv[1]);
    } else {
        // Sinon on essaye d'ouvrir une capture de vidéo (webcam)
        cout << "Ouverture du flux vidéo..." << endl;
        if(!capture.isOpened()) {
            cout << "... échec :(" << endl;
            return -1;
        }
        cout << "... ça marche :)" << endl;
        video = true;
    }
 
    // juste pour les tests sur ordinateur.
    string wndname1 = "Source";
    string wndname2 = "destination";
    string wndname3 = "contours1";
    string wndname4 = "contours2";
    string wndname5 = "test";
    namedWindow(wndname1, 1);
    namedWindow(wndname2, 1);
    namedWindow(wndname3, 1);
    namedWindow(wndname4, 1);
    namedWindow(wndname5, 1);

    while(true) {

        // on transforme les angles en radians.
        double f, dist;
        double alpha, beta, gamma;
        alpha = ((double)alpha_ - 90.)*PI/180;
        beta = ((double)beta_ - 90.)*PI/180;
        gamma = ((double)gamma_ - 90.)*PI/180;
        f = (double) f_;
        dist = (double) dist_;
 
        if (video) {
            // Capture l'image de la caméra
            capture >> source;
        }
 
        // Affiche l'image
        imshow(wndname1, source);
 
        Size taille = source.size();
        double w = (double)taille.width, h = (double)taille.height;
 
        // Cette matrice projette l'image de la caméra (2D) dans l'espace (3D)
        // et la centre
        Mat A1 = (Mat_<double>(4,3) <<
            1, 0, -w/2,
            0, 1, -h/2,
            0, 0,    0,
            0, 0,    1);
        // On définit les 3 matrices de rotation (une par axe)
        Mat RX = (Mat_<double>(4, 4) <<
            1,          0,           0, 0,
            0, cos(alpha), -sin(alpha), 0,
            0, sin(alpha),  cos(alpha), 0,
            0,          0,           0, 1);
        Mat RY = (Mat_<double>(4, 4) <<
            cos(beta), 0, -sin(beta), 0,
                    0, 1,          0, 0,
            sin(beta), 0,  cos(beta), 0,
                    0, 0,          0, 1);
        Mat RZ = (Mat_<double>(4, 4) <<
            cos(gamma), -sin(gamma), 0, 0,
            sin(gamma),  cos(gamma), 0, 0,
            0,          0,           1, 0,
            0,          0,           0, 1);
        // La matrice de rotation finale
        Mat R = RX * RY * RZ;
        // Matrice de translation : on place le plan à la distance "dist" de
        // la caméra
        Mat T = (Mat_<double>(4, 4) <<
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, dist,
            0, 0, 0, 1);
        // Matrice de la caméra : projette l'image en 2D et la centre
        Mat A2 = (Mat_<double>(3,4) <<
            f, 0, w/2, 0,
            0, f, h/2, 0,
            0, 0,   1, 0);
        // La matrice de transformation est tout simplement le produit des
        // matrices
        Mat transfo = A2 * (T * (R * A1));
 
        // Applique la transformation
        warpPerspective(source, destination, transfo, taille, INTER_CUBIC | WARP_INVERSE_MAP);
        // Affiche le résultat
        imshow(wndname2, destination);

    	// le traitement

	// on construit contours1, l'image contenant les contours de l'image destination (en 3 channals)
	// et on construit aussi l'image gray : c'est l'image "destination" en noir et blanc.
	cvtColor(destination, contours1, CV_BGR2GRAY);
	GaussianBlur(contours1, contours1, Size(5,5), 1.5, 1.5);
	Canny(contours1, contours1, 20, 50, 3,false);
	Mat gray;
	cvtColor(destination, gray, CV_BGR2GRAY);	
	
	// on construit contours2, l'image contenant les contours de l'image destination dans le channal 1 (ie Green)
	vector<Mat> channels;
	split(destination, channels);
	GaussianBlur(channels[1], contours2, Size(5,5), 1.5, 1.5);
	Canny(contours2, contours2, 20, 50, 3,false);

	// on consruit l'image Ggray : c'est l'image channels[1] (Vert) en noir et blanc.
	// et Gray2, l'image channels[2] (Rouge) en noir et blanc
	// et ensuite Ressemblance qui correspond à l'image ou le jaune dans "destination" est en blanc dans cette image et les autres couleurs sont en noir
	// c est le vecteur contenant les contours dans l'image "Ressemblance"
	Mat Ggray,Ggray2;
	threshold(channels[1], Ggray, 172.,255., THRESH_BINARY);
	threshold(channels[2], Ggray2, 172.,255., THRESH_BINARY);
	Mat Ressemblance,contours3;
	Ressemblance=((Ggray)&(Ggray2));
	GaussianBlur(Ressemblance, contours3, Size(5,5), 1.5, 1.5);
	Canny(contours3, contours3, 20, 50, 3,false);
	vector<vector<Point> > c;
	findContours(contours3, c, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	// Detection des cercles dans les images contours1 et contours2,
	HoughCircles(contours1,cercles1,CV_HOUGH_GRADIENT,2,dminCentres,600.,190.,rayonMin,rayonMax);
	HoughCircles(contours2,cercles2,CV_HOUGH_GRADIENT,2,dminCentres,600.,190.,rayonMin,rayonMax);

	// Ces parametres dependent de la qualite de la camera,
	// ils donnent les valeurs (en int) possibles des pixelx dont la couleur est celle des pions.
	//int couleurPionsMax=2000000000;
	//int couleurPionsMin=0;
	
	// puis on dessine chaque cercle (detecte dans contours2) dans destination en ne gardant que les pions,
	// et on stocke le triplet (x,y,rayon) de ces pions dans le tableau pions.
	// la matrice rect sert à eliminer les cercles parasites.
	vector<Vec3f> pions; 
	Mat rect;

	for( size_t i = 0; i < cercles2.size(); i++ )
    	{
            Point centre(cvRound(cercles2[i][0]), cvRound(cercles2[i][1]));	     
            int rayon = cvRound(cercles2[i][2]);

	    //on construit rect la matrice rectangle entourant le cercle i dans "Ressemblance", et on le transforme en une matrice de 0 et de 1,
	    getRectSubPix(Ressemblance, Size(2*rayon,2*rayon),centre,rect);
	    rect/=255.;

	    // et on fait des conditions pour ne garder que les pions, ici on se base sur les couleurs,
	    // les valeurs des pixels sont détérminées par des tests sur plusieurs images, il faut les changer en fonction de la luminence de la table !
	    if ((((Mat_<double>)gray).at<double>(centre)>104)&&(((Mat_<double>)gray).at<double>(centre)<248)&&(((Mat_<double>)destination).at<double>(centre)<218)&&(((Mat_<double>)channels[0]).at<double>(centre)>6)&&(((Mat_<double>)channels[0]).at<double>(centre)<182)&&(((Mat_<double>)channels[2]).at<double>(centre)>133)&&(((Mat_<double>)channels[1]).at<double>(centre)>103)&&(estBlanc(rect,0.25))){
	    //if (estBlanc(rect,0.25)) {
		   
		double hauteur=0;		//c'est la hauteur du rectangle entourant le pion.
 		    
		// on cherche le rectangle entourant le pion,
		for (size_t k=0; k<c.size();k++) {
		    Rect Rectangle;
	    	    Rectangle=boundingRect(Mat(c[k]));  
		    if (estInterieur(Rectangle,centre)) {
	    	        rectangle(destination,Rectangle,Scalar(255,0,0),1,CV_AA, 0);
		        hauteur=Rectangle.height;
		    }	
		}

		// Pour les tests :
                // on dessine le centre du cercle en vert dans l'image "destination"
                circle( destination, centre, 3, Scalar(0,255,0), -1, CV_AA, 0 );
                // on dessine le cercle en rouge dans l'image "destination"
                circle( destination, centre, rayon, Scalar(0,0,255), 1, CV_AA, 0 );

                // on dessine le centre du cercle en vert dans l'image "destination"
                circle( destination, Point(centre.x,centre.y+hauteur-2*rayon), 3, Scalar(0,255,0), -1, CV_AA, 0 );
                // on dessine le cercle en rouge dans l'image "destination"
                circle( destination, Point(centre.x,centre.y+hauteur-2*rayon), rayon, Scalar(0,0,255), 1, CV_AA, 0 );

		// et on écrit en bleu les coordonnées de chaque centres dans l'image "destination" et aussi la hauteur du rectangle entourant le pion.
		std::ostringstream abscisse;
	     	std::ostringstream ordonnee;
	     	std::ostringstream type;
	     	abscisse << (centre.x-w/2)*3.5;
	        ordonnee << (h-(centre.y+hauteur-2*rayon))*3.5;
		type << (int)hauteur;
	     	std::string result = abscisse.str()+" ; "+ordonnee.str()+" ; "+type.str();
	     	putText(destination,result,centre+Point(10,0),FONT_HERSHEY_SIMPLEX,0.25,Scalar(255,0,0));

	        // et on stocke les coordonnes et le rayon dans le tableau pions
		cercles2[i][0]=((centre.x-w/2)*3.5); 	//en mm //a verifier!
		cercles2[i][1]=((h-(centre.y+hauteur-2*rayon))*3.5);	//en mm //a verifier !
		///cercles2[i][2]=pion(longueurMax);
		pions.push_back(cercles2[i]); 
	    }
    	}

	line(destination,Point(w/2,0),Point(w/2,h),Scalar(255,0,0),1,CV_AA);
	circle(destination,Point(w/2,h-210),3,Scalar(0,255,0),-1,CV_AA,0);

	// les tests
        imshow(wndname2, destination);
	imshow(wndname3,contours1);
	imshow(wndname4,contours2);
	imshow("contours3",contours3);
	imshow("gray",gray);
	imshow("Ggray2",Ggray2);
	imshow("Ressemblance",Ressemblance);
	imshow("channels[1]",channels[1]);
	imshow("Ggray",Ggray);
	cout <<pions.size()<< endl;
	//cout <<pions[0][0]<<","<<pions[0][1]<<","<<pions[0][2]<<endl;

	// pour fermer les deux fenêtre des tests sur ordinateur.
        if (video) {
            // Quitte lorsqu'une touche est pressée
            if(waitKey(10) >= 0)
                break;
        } else {
            // Quitte lorsque la touche echap est pressée
            if(waitKey(0) == 27)
                break;
        }
    }
 
    return 0;
}
