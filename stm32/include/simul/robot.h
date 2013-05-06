#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED

#include <QPainter>
#include <QKeyEvent>
#include </usr/local/include/Box2D/Box2D.h>
#include <boost/circular_buffer.hpp>
#include "positionPlusAngle.h"
#include "odometrie.h"

#define ROBOT_POLYGON_COUNT 17
/** @class Robot
    @brief Classe permettant de simuler l'ensemble des couches basses du robot

    La classe simule entièrement le comportement des couches au dessous de l'asservicement dans le robot. Elle gére surtout toute la simulation du robot.
*/
class Robot
{
private:
    /** @brief Booléen vrai si le robot est en mode de controle manuel */
	bool manual;
	/** @brief Référence vers le monde dans lequel évolue le robot */
	b2World &world;
	/** @brief Position et angle actuel du robot*/
    PositionPlusAngle pos;
    /** @brief Vitesse linéaire et vitesse angulaire actuel du robot*/
	PositionPlusAngle deriv;
	boost::circular_buffer<PositionPlusAngle> olds;
	class Asservissement* asservissement;
	class Odometrie* odometrie;
    class StrategieV2* strategie;
    int leftLowerHammerStatus;
    int leftUpperHammerStatus;
    int rightLowerHammerStatus;
    int rightUpperHammerStatus;

	b2Body* body;
    QPoint robotPolygonPoints[ROBOT_POLYGON_COUNT];
public:

	unsigned int level;

    /** @brief Constructeur de la classe
        @param world Référence vers le b2World dans lequel évolura le robot*/
    Robot(b2World &world, PositionPlusAngle depart, bool manual);
	/** @brief Destructeur de la classe*/
	~Robot();
    /** @brief Permet d'afficher le robot à l'écran
        @param p Référence vers le painter actuellement utilisé pour dessiner à l'écran
        @param dt */
	void paint(QPainter &p, int dt);
	/** @brief Permet de gérer les actions à effectué en fonction des touches activé par l'utilisateur
        @param evt Pointer vers l'évenement intercepté
        @param press Booléen indiquant si une touche a été pressée ou non*/
	void keyPressEvent(QKeyEvent* evt,bool press);
	void updateForces(int dt);
	void setLevel();
	/** @brief Permet d'obtenir la position actuel du robot
        @return Retourne la position et l'angle actuel du robot*/
	PositionPlusAngle getPos();
	/** @brief Permet de fixer la position et l'angle actuel du robot */
	void setPos(PositionPlusAngle p);
	/** @brief Permet d'obtenir la vitesse angulaire du robot
        @return Retourne la vitesse angulaire actuel du robot*/
	Angle getVitesseAngulaire();
	/** @brief Permet d'obtenir la vitesse linaire actuel du robot
        @return Retourne la vitesse linaire actuel du robot*/
	Distance getVitesseLineaire();

    QPoint getLeftUpperHammerPos() const;
    QPoint getRightUpperHammerPos() const;
    QPoint getLeftLowerHammerPos() const;
    QPoint getRightLowerHammerPos() const;
    void startLeftUpperHammer();
    void startRightUpperHammer();
    void startLeftLowerHammer();
    void startRightLowerHammer();
};

#endif //ROBOT_H_INCLUDED

