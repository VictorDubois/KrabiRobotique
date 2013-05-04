#include "ascenseur.h"

Ascenseur* Ascenseur::m_ascenseur = NULL;

// Constructeur
Ascenseur::Ascenseur(Roue* vis, LimitSwitchSensor* fdcHaut, LimitSwitchSensor* fdcBas)
    : m_tourne(false), m_vaEnHaut(true), m_vis(vis), m_fdcHaut(fdcHaut), m_fdcBas(fdcBas)
{
    vis->tourne(0.0f);
    m_ascenseur = this;
}

// destructeur
Ascenseur::~Ascenseur()
{
    if (m_ascenseur == this)
        m_ascenseur = NULL;
}

// l'ascenseur monte tout en haut
void Ascenseur::monter()
{
    m_vaEnHaut = true;

    if (!toutEnHaut())
    {
        m_tourne = true;
        m_vis->tourne(1.0f);
    }
}

// l'ascenseur descend tout en bas
void Ascenseur::descendre()
{
    m_vaEnHaut = false;

    if (!toutEnHaut())
    {
        m_tourne = true;
        m_vis->tourne(-1.0f);
    }
}

// met à jour l'état de l'ascenseur pour l'arreter si il est arrivé à son but
void Ascenseur::update()
{
    if (m_tourne)
    {
        if (m_vaEnHaut ? toutEnHaut() : toutEnBas())
        {
            m_tourne = false;
            m_vis->tourne(0.0f);
        }
    }
}

// est ce que l'ascenseur a fini sa montée/descente
bool Ascenseur::aFini() const
{
    return !m_tourne;
}

// est ce que l'ascenseur va/est en haut ?
bool Ascenseur::vaEnHaut() const
{
    return m_vaEnHaut;
}

// est ce que les fdc sont activés ?
bool Ascenseur::toutEnHaut() const
{
    return m_fdcHaut->getValue().b;
}

bool Ascenseur::toutEnBas() const
{
    return m_fdcBas->getValue().b;
}

// renvoit l'ascenseur
Ascenseur* Ascenseur::get()
{
    return m_ascenseur;
}

