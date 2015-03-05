#ifndef XMLREADER_H_INCLUDED
#define XMLREADER_H_INCLUDED

/*!
 * \file XMLReader.h
 * \brief Loader de fichiers XML
 * \author Robin 'hilnius' Nicollet
 * \version 0.1
 * 
 * Permet de lire un fichier XML (un XML a peine personalisé)
 * Lit les syntaxes suivantes:
 * Les écritures suivantes désignent "<A><foo>3</foo><bar>89</bar></A>"
 * <A foo=3 bar=89 />  
 * <A foo=3 bar="89" />  
 * <A foo="3" bar="89" /> 
 * <A foo=3><bar>89</bar></A>  
 * etc...
 * Ce qui est entre deux balises, sans tag, est mis dans la valeur de la balise.
 * <A foo=3>Grapefruit</A> désigne donc un arbre à une branche contenant {type=foo, valeur=3} et dont la racine est {type=A, valeur=Grapefruit}
 * Les seuls commentaires tolérés sont ceux entre les balises de la racine.
 * 
*/

#include <QString>
#include <vector>
#include <iostream>

/*! \class XMLTag
 * \brief Classe représentant un noeud d'arbre XML.
 *
 * La classe instancie un noeud d'arbre XML. 
 * Elle a un type, qui est l'objet qu'elle représente. <Object width="3"></Object> a pour type Object
*/
class XMLTag
{
	public:
		XMLTag();
		
		/**
		 * \fn QString convertInsideValuesToTags(QString values)
		 * \brief Convertit des valeurs insérées dans la balise en tags.
		 * 
		 * Par exemple, convertInsideValuesToTags "value="salut" width=3 hello=true"  
		 * renvoie "<value>salut</value><width>3</width><hello>true</hello>".
		 * 
		 * \param input Chaine à convertir.
		 * \return Chaine sous forme de tags.
		*/
		QString convertInsideValuesToTags(QString values);

		/**
		 * \fn QString readSelf(QString input)
		 * \brief Se lit soi-même (seulement au niveau 0).
		 * 
		 * Ne lit que les Tag de niveau 0, met les autres dans p_inside.
		 * Par exemple, readSelf "<Prop> <a> <b> </b> </a> <c> </c> </Prop>" 
		 * met " <a> <b> </b> </a> <c> </c> " dans p_inside.
		 * 
		 * \param input Chaine qui va être lue.
		 * \return La chaine pas encore traitée (dans "<a> </a> <prop>...", renvoie " <prop>..."). Renvoie input si le traitement a échoué ou si values est la valeur que doit prendre la balise.
		*/
		QString readSelf(QString input);

		/**
		 * \fn void readInside()
		 * \brief Lis p_inside et la parse.
		 * 
		*/
		void readInside();

		/**
		 * \fn void print()
		 * \brief Ecrit le contenu de la balise, et de ses sous-balises.
		 * 
		*/
		void print();
		
		/**
		 * \fn void setType(QString type)
		 * \brief Remplace le type existant par l'argument donné en paramètre.
		 * \param type Le type de balise. <Exemple /> est de type Exemple.
		*/
		void setType(QString type);

		/**
		 * \fn void setValue(QString value)
		 * \brief Remplace la valeur existante par l'argument donné en paramètre.
		 * \param value La valeur de la balise. <Var>3</var> a pour valeur 3.
		*/
		void setValue(QString value);

		/**
		 * \fn void setParent(const XMLTag* tag)
		 * \brief Change le parent de la balise.
		 * \param tag Le futur parent de la balise.
		*/
		void setParent(const XMLTag* tag);

		/**
		 * \fn void addChild(XMLTag* tag)
		 * \brief Ajoute un enfant à la balise.
		 * \param tag L'enfant à ajouter.
		*/
		void addChild(XMLTag* tag);

		/**
		 * \fn void setInside(QString inside)
		 * \brief Permet de changer la valeur de p_inside.
		 * \param inside La nouvelle valeur de p_inside.
		*/
		void setInside(QString inside);

		/**
		 * \fn const QString& getType()
		 * \brief Renvoie le type de la balise.
		 * \return Le type de balise, sous forme de QString.
		*/
		const QString& getType() const;

		/**
		 * \fn const QString& getValue()
		 * \brief Renvoie la valeur de la balise.
		 * \return La valeur de balise, sous forme de QString.
		*/
		const QString& getValue() const;

		/**
		 * \fn const XMLTag* getParent()
		 * \brief Père de la balise.
		 * Renvoie le père de la balise.
		 * \return Le parent de la balise.
		*/
		const XMLTag* getParent();

		/**
		 * \fn std::vector<XMLTag*> getChildren()
		 * \brief Enfants de la balise.
		 * \return Les enfants de la balise (du noeud).
		*/
		std::vector<XMLTag*> getChildren();

		/**
		 * \fn bool finishedReading()
		 * \brief Renvoie true si la balise s'est bien lue.
		 * \return true si p_inside est vide, false sinon.
		*/
		bool finishedReading() const;

        const bool& getSolid() const;

        void setSolid(bool solid);
	
	private:
		const XMLTag* p_parent; /*!< Père. */
		std::vector<XMLTag*> p_children; /*!< Enfants. */
		QString p_type; /*!< Type (<A></A> a pour type A). */
		QString p_value; /*!< Valeur (<A>3</A> a pour valeur 3). */
        bool p_solid; /*!< Valeur pour savoir si objet solide. */
		QString p_inside; /*!< Contenu non encore traité. */
};

/*! \namespace XMLReader
 * 
 * espace de nommage regroupant les fonctions de charge des fichiers XML.
 */
namespace XMLReader
{
	/**
	 * \fn XMLTag* getTree(QString xmlString)
	 * \brief Convertit une chaine XML en arbre représentant la structure XML.
	 *
	 * \param xmlString Chaine qui va être convertie en arbre XML.
	 * \return Pointeur sur la racine de l'arbre.
	*/
	XMLTag* getTree(QString xmlString);
}


#endif










