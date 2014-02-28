#ifndef ETAPE_H
#define ETAPE_H
#include "position.h"
#define NB_MAX_CHILDREN 4

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
        FEU_COTE = 9,
        FEU_TERRAIN = 10,
        TIR_MAMMOUTH = 11,
        ROBOT_POINT_PASSAGE = POINT_PASSAGE + 20,
        ROBOT_COLLECT =       COLLECT + 20,
        ROBOT_FRUIT =         FRUIT + 20,
        ROBOT_FEU =           FEU + 20,
        ROBOT_FRESQUE =       FRESQUE + 20,
        ROBOT_DEPART =        DEPART + 20,
        ROBOT_DEPOSE_FEU =    DEPOSE_FEU + 20,
        ROBOT_DEPOSE_FRUIT  = DEPOSE_FRUIT + 20,
        ROBOT_TORCHE_MOBILE = TORCHE_MOBILE + 20,
        ROBOT_FEU_COTE =      FEU_COTE + 20,
        ROBOT_FEU_TERRAIN =   FEU_TERRAIN + 20,
        ROBOT_TIR_MAMMOUTH =  TIR_MAMMOUTH + 20,
    };

    /** @brief Constructeur d'une etape *
    *   @param position Position de cette étape *
    *   @param children Tableau des étapes attachées à celle-ci *
    *   @param le nombre d'étapes attachées à celle_ci *
    *   @param le numero de cette étape *
    *   @param typeType d'étape (un feu, un point de passage...) *
    *   @param state Etat de cette étape, utilisé pour l'exploration du graphe */
    Etape(Position position, Etape** children, int nbChildren, int numero, EtapeType type, int state);
    //Etape(Position position, Etape* (&children)[NB_MAX_CHILDREN], int nbChildren, EtapeType type, int state);

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

private:
    /** @brief Tableau des étapes attachées à celle-ci */
    Etape** children;
    //Etape* (&children)[NB_MAX_CHILDREN];

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
};

#endif // ETAPE_H
