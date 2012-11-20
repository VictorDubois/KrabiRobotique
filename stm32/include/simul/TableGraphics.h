#ifndef TABLEGRAPHICS_H_INCLUDED
#define TABLEGRAPHICS_H_INCLUDED

/*!
 * \file TableGraphics.h
 * \brief Formes à dessiner avec QT.
 * \author Robin 'hilnius' Nicollet
 * \version 0.1
 * 
 * Permet de convertir un fichier XML issu de XMLReader en formes à dessiner avec Qt.
 * Prend en charge :
 * - Les rectangles <Rect />
 * - Les rectangles arrondis <RoundedRect />
 * - Les ellipses <Ellipse />
 * - La couleur selon la propriété Color::name de Qt.
 * 
 * 
*/

#include <QFile>
#include <QIODevice>
#include <QString>
#include <vector>
#include <QPainter>
#include <QColor>
#include "XMLReader.h"

/*! \class Shape
 * \brief Classe représentant une forme.
 *
 * Utilisée pour héritage.
*/
class Shape
{
	public:
		Shape();
		virtual ~Shape();

		/**
		 * \fn virtual void readSelf(QString)
		 * \brief Lecture de l'objet par lui même.
		 *
		 * Charge la forme à partir de la branche XML.
		 * Utilise le polymorphisme.
		 *
		 * \param tree Branche représentant la forme.
		 */
		virtual void readSelf(XMLTag* tree);
		/**
		 * \fn virtual void drawSelf(QPainter* painter)
		 * \brief Dessin de l'objet par lui même.
		 *
		 * L'ojbet se dessine.
		 *
		 * \param painter QPainer servant à dessiner.
		 */
		virtual void drawSelf(QPainter* painter);
		/**
		 * \fn virtual void addXOffset(int xOffset)
		 * \brief Ajout d'un offset selon X.
		 *
		 * Ajoute une offset selon l'axe X.
		 *
		 * \param xOffset Valeur de l'offset.
		 */
		virtual void addXOffset(int xOffset) = 0;
		/**
		 * \fn virtual void addYOffset(int yOffset)
		 * \brief Ajout d'un offset selon Y.
		 *
		 * Ajoute une offset selon l'axe Y.
		 *
		 * \param yOffset Valeur de l'offset.
		 */
		virtual void addYOffset(int yOffset) = 0;

	protected:
		QColor p_color; /*!< Couleur. */
		int p_z; /*!< Côte. Non implémenté actuellement (inutile) */
};

class Point2d
{
	public:
		Point2d(int mx=0, int my=0);

		virtual void addXOffset(int xOffset);
		virtual void addYOffset(int yOffset);

		virtual void readSelf(XMLTag* tree);

		int x; /*!< Coordonnée X */
		int y; /*!< Coordonnée Y */
};
typedef Point2d Size2d;

class Rect : public Shape
{
	public:
		Rect();
		virtual ~Rect();

		virtual void readSelf(XMLTag* tree);
		virtual void drawSelf(QPainter* painter);
		virtual void addXOffset(int xOffset);
		virtual void addYOffset(int yOffset);
	
	protected:
		Point2d p_start; /*!< Position du coin haut-gauche. */
		Size2d p_size; /*!< Taille. */
};
class RoundedRect : public Rect
{
	public:
		RoundedRect();

		virtual void readSelf(XMLTag* tree);
		virtual void drawSelf(QPainter* painter);
		virtual void addXOffset(int xOffset);
		virtual void addYOffset(int yOffset);
	
	protected:
		int p_xRadius; /*!< Rayon des coins selon X. */
		int p_yRadius; /*!< Rayon des coins selon Y. */
};
class Ellipse : public Shape
{
	public:
		Ellipse();

		virtual void readSelf(XMLTag* tree);
		virtual void drawSelf(QPainter* painter);
		virtual void addXOffset(int xOffset);
		virtual void addYOffset(int yOffset);
	
	protected:
		Point2d p_center; /*!< Position du centre. */
		int p_xRadius; /*!< Rayon selon l'axe X. */ 
		int p_yRadius; /*!< Rayon selon l'axe Y. */
};

/*! \class TableGraphics
 * \brief Classe des formes à dessiner.
 *
 * La classe charge les formes à dessiner, les stocke et les dessine.
 * Elle ne contient qu'une instance graphique des objets.
*/
class TableGraphics
{
	public:
		TableGraphics();

		/**
		 * \fn void addXOffset(int xOffset)
		 * \brief Ajout d'un offset selon X.
		 *
		 * Ajoute une offset selon l'axe X à toutes les formes de la table.
		 *
		 * \param xOffset Valeur de l'offset.
		 */
		void addXOffset(int xOffset);
		/**
		 * \fn void addYOffset(int yOffset)
		 * \brief Ajout d'un offset selon Y.
		 *
		 * Ajoute une offset selon l'axe Y à toutes les formes de la table.
		 *
		 * \param yOffset Valeur de l'offset.
		 */
		void addYOffset(int yOffset);
		
		/**
		 * \fn void load(QString filename)
		 * \brief Charge des formes a partir d'un fichier XML
		 *
		 * Crée l'arbre XML a l'aide de XMLReader. 
		 * Utilise ensuite les fonctions virtuelles readSelf() afin que les formes reçoivent leurs paramètres.
		 *
		 * \param filename Nom du fichier à charger.
		 */
		void load(QString filename);
		/**
		 * \fn void draw(QPainter* painter)
		 * \brief Dessine toutes les formes
		 *
		 * Utilise les fonctions virtuelles de Shape pour que toutes les formes se dessinent.
		 *
		 * \param painter Pointeur sur le QPainter étant chargé du dessin.
		 */
		void draw(QPainter* painter);

		
	private:
		std::vector<Shape*> shapes; /*!< Pointeurs sur les formes (polymorphisme). */
	
};


#endif
