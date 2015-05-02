#ifndef ETAPE_H
#define ETAPE_H
#include "position.h"

class Etape
{
public:
    /** @brief Enum des types d'étape possible (un feu, un point de passage...) */
    enum EtapeType
    {
        ROBOT_VU_ICI = 100,
        POINT_PASSAGE = 0,
        COLLECT = 1,
        FRUIT = 2,
        DEPART = 5,
        DEPOSE_FEU = 6,
        DEPOSE_FRUIT = 7,
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
        DEPOSE_GOBELET = 22,
        ROBOT_POINT_PASSAGE = POINT_PASSAGE + ROBOT_VU_ICI,
        ROBOT_COLLECT =       COLLECT + ROBOT_VU_ICI,
        ROBOT_FRUIT =         FRUIT + ROBOT_VU_ICI,
        ROBOT_DEPART =        DEPART + ROBOT_VU_ICI,
        ROBOT_DEPOSE_FEU =    DEPOSE_FEU + ROBOT_VU_ICI,
        ROBOT_DEPOSE_FRUIT  = DEPOSE_FRUIT + ROBOT_VU_ICI,
        ROBOT_FEU_TERRAIN =   FEU_TERRAIN + ROBOT_VU_ICI,
        ROBOT_TIR_MAMMOUTH =  TIR_MAMMOUTH + ROBOT_VU_ICI,
        ROBOT_TIR_FILET = TIR_FILET + ROBOT_VU_ICI,
        ROBOT_FEU_MINI_BRAS = FEU_MINI_BRAS + ROBOT_VU_ICI,
        ROBOT_CENTRE_TABLE = CENTRE_TABLE + ROBOT_VU_ICI,
        ROBOT_CLAP = CLAP + ROBOT_VU_ICI,
        ROBOT_GOBELET = GOBELET + ROBOT_VU_ICI,
        ROBOT_PIED = PIED + ROBOT_VU_ICI,
        ROBOT_AMPOULE = AMPOULE + ROBOT_VU_ICI,
        ROBOT_TAPIS = TAPIS + ROBOT_VU_ICI,
        ROBOT_DEPOSE_GOBELET = DEPOSE_GOBELET + ROBOT_VU_ICI

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

    /** @brief Setter de l'étape à laquelle on fini l'action de l'étape */
    void setNumeroEtapeFinAction(int newNumeroEtapeFinAction);

    /** @brief Getter de l'étape à laquelle on fini l'action de l'étape */
    int getNumeroEtapeFinAction();

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

    /** @brief Etape à laquelle on fini l'action de l'étape */
    int numeroEtapeFinAction;
};

#endif // ETAPE_H
