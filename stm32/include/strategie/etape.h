#ifndef ETAPE_H
#define ETAPE_H
#include "position.h"

class Etape
{
public:
    /** @brief Enum des types d'étape possible (un feu, un point de passage...) */
    enum EtapeType
    {
        POINT_PASSAGE = 0,
        COLLECT = 1,
        FRUIT = 2,
        FEU = 3,
        FRESQUE = 4,
        DEPART = 5,
        DEPOSE_FEU = 6,
        DEPOSE_FRUIT = 7,
        TORCHE_MOBILE = 8,
        FEU_COTE_NOTRE_COULEUR_FACE_TERRAIN = 9,
        FEU_COTE_NOTRE_COULEUR_FACE_EXTERIEUR = 10,
        FEU_TERRAIN = 11,
        TIR_MAMMOUTH = 12,
        TIR_FILET = 13,
        FEU_MINI_BRAS = 14,
        FEU_COTE = 15,
        CENTRE_TABLE = 16,
        CLAP = 17,
        GOBELET = 18,
        PIED = 19,
        AMPOULE = 20,
        TAPIS = 21,
        ROBOT_POINT_PASSAGE = POINT_PASSAGE + 20,
        ROBOT_COLLECT =       COLLECT + 20,
        ROBOT_FRUIT =         FRUIT + 20,
        ROBOT_FEU =           FEU + 20,
        ROBOT_FRESQUE =       FRESQUE + 20,
        ROBOT_DEPART =        DEPART + 20,
        ROBOT_DEPOSE_FEU =    DEPOSE_FEU + 20,
        ROBOT_DEPOSE_FRUIT  = DEPOSE_FRUIT + 20,
        ROBOT_TORCHE_MOBILE = TORCHE_MOBILE + 20,
        ROBOT_FEU_COTE_NOTRE_COULEUR_FACE_TERRAIN = FEU_COTE_NOTRE_COULEUR_FACE_TERRAIN + 20,
        ROBOT_FEU_COTE_NOTRE_COULEUR_FACE_EXTERIEUR = FEU_COTE_NOTRE_COULEUR_FACE_EXTERIEUR + 20,
        ROBOT_FEU_TERRAIN =   FEU_TERRAIN + 20,
        ROBOT_TIR_MAMMOUTH =  TIR_MAMMOUTH + 20,
        ROBOT_TIR_FILET = TIR_FILET + 20,
        ROBOT_FEU_MINI_BRAS = FEU_MINI_BRAS + 20,
        ROBOT_CENTRE_TABLE = CENTRE_TABLE + 20,
        ROBOT_CLAP = CLAP + 20,
        ROBOT_GOBELET = GOBELET + 20,
        ROBOT_PIED = PIED + 20,
        ROBOT_AMPOULE = AMPOULE + 20,
        ROBOT_TAPIS = TAPIS + 20

    };

    /** @brief Constructeur d'une etape *
    *   @param position Position de cette étape *
    *   @param le nombre d'étapes attachées à celle_ci *
    *   @param le numero de cette étape *
    *   @param le tableau contenant toutes les étapes, pour qu'elle s'y ajoute *
    *   @param typeType d'étape (un feu, un point de passage...) *
    *   @param state Etat de cette étape, utilisé pour l'exploration du graphe
    *   @param nombreEtapesLieesParFinirEtape Nombre d'étapes qui doivent être considérées comme finie si celle-ci l'est */
    Etape(Position position,/* int nbChildren, */int numero, Etape** tableauEtapesTotal, EtapeType type, int state, int nombreEtapesLieesParFinirEtape);

    /** @brief Constructeur vide d'une etape */
    Etape();

    /** @brief Renvoi un pointeur vers une des etapes attachees a celle-ci *
    *   @param nb le numéro du lien vers l'autre etape */
    Etape* getChild(int nb);

    /** @brief Renvoi un tableau de pointeurs vers les etapes attachees a celle-ci */
    Etape** getChildren();

    /** @brief Renvoi l'étape précédente pour remonter à l'étape en cours (utilisé pour l'exploration du graphe) */
    Etape* getParent();

    /** @brief Renvoi la position de cette étape */
    Position getPosition();

    /** @brief Renvoi l'état de l'étape courante (utilisé pour l'exploration du graphe) */
    int getState();

    /** @brief Set l'état de l'étape courante (utilisé pour l'exploration du graphe) *
    *   @param state le nouvel état de l'étape */
    void setState(int state);

    /** @brief Renvoi la distance de cette étape à l'étape où se trouve le robot */
    int getDistance();

    /** @brief Set la distance de cette étape à l'étape où se trouve le robot *
    *   @param distance de cette étape à l'étape où se trouve le robot */
    void setDistance(int distance);

    /** @brief Set l'étape précédente pour remonter à l'étape en cours (utilisé pour l'exploration du graphe) */
    void setParent(Etape* parent);

    /** @brief Renvoi le nombre d'étapes attachées à celle_ci */
    int getNbChildren();

    /** @brief Renvoi le type de cette étape (un feu, un point de passage...) */
    EtapeType getEtapeType();

    /** @brief Set le type de cette étape (un feu, un point de passage...) *
    *   @param type le type de cette étape (un feu, un point de passage...) */
    void setEtapeType(EtapeType type);

    /** @brief set un tableau de pointeurs vers les etapes attachees a celle-ci *
    *   @param children Tableau des étapes attachées à celle-ci */
    void setChildren(Etape** children);

    /** @brief On aurait vu un robot sur le chemin de cette étape */
    void robotVu();

    /** @brief Renvoi le numero de cette étape */
    int getNumero();

    /** @brief Renvoi true s'il faut éviter cette étape */
    bool aEviter();

    /** @brief Oublie qu'on a vu un robot ici*/
    void oublieRobotVu();

    /** @brief Renvoi un tableau des distances vers les etapes attachees a celle-ci */
    int* getDistances();

    /** @brief set un tableau des distances vers les etapes attachees a celle-ci *
    *   @param distances Tableau des distances vers les etapes attachées à celle-ci */
    void setDistances(int* distances);

    void computeChildDistances();

    /** @brief Renvoi un tableau des étapes qui doivent être considérées comme finie si celle-ci l'est */
    int* getEtapesLieesParFinirEtape();

    /** @brief set un tableau des étapes qui doivent être considérées comme finie si celle-ci l'est *
    *   @param children Tableau des étapes qui doivent être considérées comme finie si celle-ci l'est */
    void setEtapesLieesParFinirEtape(int* numerosEtapesLieesParFinirEtape);

    /** @brief Renvoi le nombre d'étapes qui doivent être considérées comme finie si celle-ci l'est */
    int getNombreEtapesLieesParFinirEtape();

    /** @brief Effectue les changements nécessaires pour considérer l'étape comme effectuée */
    void finir(void);

    /** @brief set le score de l'étape *
    *   @param score le score de l'étape */
    void setScore(int score);

    /** @brief Renvoi le score de l'étape */
    int getScore();

    /** @brief Ajoute un voisinau tableau de voisins */
    Etape* addVoisin(Etape* newVoisin, bool autreSens=true);

private:
    /** @brief Tableau des étapes attachées à celle-ci */
    Etape** children;

    /** @brief Etape précédente pour remonter à l'étape en cours, utilisé pour l'exploration du graphe */
    Etape* parent;

    /** @brief Position de cette étape */
    Position position;

    /** @brief Etat de cette étape, utilisé pour l'exploration du graphe */
    int state;

    /** @brief Distance de cette étape à l'étape où se trouve le robot */
    int distance;

    /** @brief Type d'étape (un feu, un point de passage...) */
    EtapeType type;

    /** @brief int Set le nombre d'étapes attachées à celle_ci */
    int nbChildren;

    /** @brief int le numero de cette étape */
    int numero;

    /** @brief Tableau des distances vers les étapes attachées à celle-ci */
    int* distances;

    /** @brief Nombre d'étapes qui doivent être considérées comme finie si celle-ci l'est */
    int nombreEtapesLieesParFinirEtape;

    /** @brief Tableau des étapes qui doivent être considérées comme finie si celle-ci l'est */
    int* numerosEtapesLieesParFinirEtape;

    /** @brief Score de l'étape, correspondant à si on veut que le robot la réalise ou pas*/
    int score;
};

#endif // ETAPE_H
