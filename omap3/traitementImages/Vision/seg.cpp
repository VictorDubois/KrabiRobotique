#include "cv.h"
#include "highgui.h"
 
#include <cmath>
#include <iostream>
#include <vector>

 
#define PI 3.14159265
 
using namespace cv;
using namespace std;
 
int main(int argc, char** argv) {

    // les paramètres pour applatir l'image reçue de la camèra.
    // A regler selon la position de la camera sur le robot !
    int alpha_=30., beta_=90., gamma_=90.;
    int f_ = 500, dist_ =415;

    // indique si on a le flux video ou pas.
    bool video = false;
    
    // source est l'image vu par la camèra.
    // destination est l'image "vu" par le robot.
    // contours1 est l'image obtenue apres detection de contours sur l'image en 3 channals.
    // contours2 est l'image obtenue apres detection de contours sur l'image dans le channal G (Green).
    // lines1 est un vecteur contenant les coordonnées des extremites des segments detectes

    Mat source, destination, contours1, contours2;
    vector<Vec4i> lines1,lines2; 
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

    Mat test=Mat_<Scalar>(40,40);
    test=Scalar(0.,254.,255.);
    cout << test.at<Scalar>(20,20)[1]<< endl;
    imshow(wndname5, test);
 
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
	cvtColor(destination, contours1, CV_BGR2GRAY);
	Mat gray;
	cvtColor(destination, gray, CV_BGR2GRAY);	
	GaussianBlur(contours1, contours1, Size(5,5), 1.5, 1.5);
	Canny(contours1, contours1, 20, 50, 3,false);
	
	// on construit contours2, l'image contenant les contours de l'image destination dans le channal 1 ie Green
	vector<Mat> channels;
	split(destination, channels);
	GaussianBlur(channels[1], contours2, Size(5,5), 1.5, 1.5);
	Canny(contours2, contours2, 20, 50, 3,false);

	IplImage *tranche,*src;
	src=  cvLoadImage("d.JPG");
	tranche = cvCreateImage(cvGetSize(src),src->depth , 1);
	cvInRangeS(src,Scalar(0.,0.,0.),Scalar(0.,255.,0.),tranche);
	imshow(wndname5,src);	
	imshow("test2",tranche);	

	// les parametres ci-dessous dependent de la resolution de la camera, des parametres pour applatir.
	// ils servent a faire le lien entre la distance reelle sur la table et la distance mesure sur l'image.

	double dminCentres=40.;	// la distance minimale entre les centres des cercles a detecter.
	int rayonMin=10;	// le rayon minimal des cercles a detecter.
	int rayonMax=200;	// le rayon maximal des cercles a detecter
 

	// Detection des cercles dans les images contours1 et contours2,
	HoughLinesP(contours1,lines1, 1, CV_PI/180,1, 13, 5 );
	//HoughLinesP(contours2, lines2, 1, CV_PI/180, 80, 30, 10 );;

	// Ces parametres dependent de la qualite de la camera,
	// ils donnent les valeurs (en int) possibles des pixelx dont la couleur est celle des pions.
	int couleurPionsMax=2000000000;
	int couleurPionsMin=0;
	
	// puis on dessine chaque cercle detecte dans contours2 en ne gardant que les pions,
	// et on stocke le triplet (x,y,rayon) de ces pions dans le tableau pions.
	vector<Vec3f> pions; 

    for( size_t i = 0; i < lines1.size(); i++ )
    {
	line( destination, Point(lines1[i][0], lines1[i][1]),
            Point(lines1[i][2], lines1[i][3]), Scalar(0,0,255), 3, 8 );

    }
    for( size_t i = 0; i < lines2.size(); i++ )
    {
	line( destination, Point(lines2[i][0], lines2[i][1]),
            Point(lines2[i][2], lines2[i][3]), Scalar(0,0,255), 3, 8 );

    }

        imshow(wndname2, destination);
	imshow(wndname3,contours1);
	imshow(wndname4,contours2);
	//cout <<pions.size()<< endl;

	// pour fermer les deux fenêtre des test sur ordinateur.
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
