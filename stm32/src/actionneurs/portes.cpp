#include "portes.h"

// constructeur : on fournit les 2 servos et les angles d'ouverture/fermeture
Portes::Portes(Servo* gauche, Servo* droite,
               int angleGaucheOuverte, int angleGaucheFermee,
               int angleDroiteOuverte, int angleDroiteFermee)
    : m_ouvertes(true)
    , m_gauche(gauche), m_droite(droite)
    , m_angleGaucheOuverte(angleGaucheOuverte), m_angleGaucheFermee(angleGaucheFermee)
    , m_angleDroiteOuverte(angleDroiteOuverte), m_angleDroiteFermee(angleDroiteFermee)
{
}

// destructeur
Portes::~Portes()
{
    m_gauche->shutDownServo();
    m_droite->shutDownServo();
}

// ouvre les portes
void Portes::ouvrir()
{
    m_gauche->goToAngle(m_angleGaucheOuverte);
    m_droite->goToAngle(m_angleDroiteOuverte);
    m_ouvertes = true;
}

// ferme les portes
void Portes::fermer()
{
    m_gauche->goToAngle(m_angleGaucheFermee);
    m_droite->goToAngle(m_angleDroiteFermee);
    m_ouvertes = false;
}

// renvoit l'état des portes
bool Portes::ouvertes() const
{
    return m_ouvertes;
}

bool Portes::fermees() const
{
    return !m_ouvertes;
}
