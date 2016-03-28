#ifndef OBJET_H
#define OBJET_H
#ifndef ROBOTHW

#include "position.h"
#include "angle.h"
#include <QPainter>
#include </usr/local/include/Box2D/Box2D.h>

/**@brief Classe permettant de gérer les différents objets pouvant être déplacé sur la table (pièce, lingot) */
class Objet
{
    public:
        /**@enum Type */
        /**@brief Énumération permettant de classifier les différents objets */
        enum Type
        {

            ANY,

            SHELL, /*!< Représente un coquillage*/
            SANDCUBE,
            SANDCUBE1,/*!< Représente un cube de chateau de sable*/
            /* SANDCONE, /*!< Représente un cone de chateau de sable*/
            SANDCYLINDER, /*!< Représente un cylinder de chateau de sable*/
            PORTE /*!< Représente la porte des cabine de plage*/
            /*MER, /*!< Représente la mer*/
            /*POISSON, /*!< Représente le poisson*/
            /*FILET/*!< Représente le filet*/
        };
        /**@brief Constructeur de la classe permettant de construire directement un objet de type type à la position p avec pour angle initial theta. */
        /**@param world Pointer vers le b2World dans lequel va être créé notre objet*/
        /**@param P Position initial de l'objet*/
        /**@param type Type de l'objet créé */
        /**@param theta Angle initial de l'objet crée en radian */
		Objet(b2World & world, Position p, Type type, Angle theta = 0., QColor color = QColor());
        /**@brief Destructeur de la classe */
        ~Objet();
        /**@brief Permet de dessiner l'objet à l'écran */
        /**@param pa Pointeur vers le QPainter qui dessine à l'écran */
        void paint(QPainter & pa);
        /**@brief Met à jour la position de l'objet sur la table ainsi que la ses vitesses */
        void updatePos();

        void moveOutOfField();

        Position getPosition();
        Type getType();
        bool isNear(Position p, Distance radius = 0.);

    protected:
    private:
        /**@brief Contient la position du centre de l'objet. */
        Position p;
        /**@brief Angle actuel de l'objet par rapport au repert de la table (utile seulement pour les objets de type goldBar) */
        Angle theta;
        /**@brief Contient le type de l'objet*/
        Type type;
        /**@brief Pointeur vers un objet de type b2Body afin de représenter l'objet par Box2D*/
        b2Body* body;
        /**@brief Pointeur vers l'objet de type b2World dans lequel notre objet est définie */
        b2World* world;
		/**@brief Couleur de l'objet */
		QColor p_color;

        Distance radius;
};

#endif // ROBOTHW
#endif // OBJET_H
