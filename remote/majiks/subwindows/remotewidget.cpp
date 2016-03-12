#include "remotewidget.h"

#include "serialproxy/abstractserialproxy.h"

#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

RemoteWidget::RemoteWidget(AbstractSerialProxy *serialProxy, QWidget *parent): QWidget(parent)
{
    m_serialProxy = serialProxy;

    m_upButton      = new QPushButton(tr("Up"));
    m_downButton    = new QPushButton(tr("Down"));
    m_leftButton    = new QPushButton(tr("Turn Left"));
    m_rightButton   = new QPushButton(tr("Turn Right"));

    m_upButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_downButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_leftButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_rightButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(m_upButton,     &QPushButton::pressed, this, &RemoteWidget::on_upButton_pressed);
    connect(m_downButton,   &QPushButton::pressed, this, &RemoteWidget::on_downButton_pressed);
    connect(m_leftButton,   &QPushButton::pressed, this, &RemoteWidget::on_leftButton_pressed);
    connect(m_rightButton,  &QPushButton::pressed, this, &RemoteWidget::on_rightButton_pressed);

    m_currentPositionLabel = new QLabel(this);

    QGridLayout* grid = new QGridLayout(this);

    grid->addWidget(m_upButton,             1, 2);
    grid->addWidget(m_downButton,           3, 2);
    grid->addWidget(m_leftButton,           2, 1);
    grid->addWidget(m_rightButton,          2, 3);

    grid->addWidget(m_currentPositionLabel, 2, 2, Qt::AlignCenter);

    setCurrentPosition(QPointF(0.f, 0.f), 0.f);
    setLinearStep(10.f);
    setAngularStep(1.f);
}

void RemoteWidget::setCurrentPosition(const QPointF& position, float angle)
{
    m_currentPosition = position;
    m_currentAngle = angle;
    m_currentPositionLabel->setText(tr("Current position\nX:\t%1mm\nY:\t%2mm\nAngle:\t%3°").arg(position.x()).arg(position.y()).arg(angle));
}

void RemoteWidget::on_leftButton_pressed()
{
    rotateRobot(-getAngularStep());
}

void RemoteWidget::on_rightButton_pressed()
{
    rotateRobot(-getAngularStep());
}

void RemoteWidget::on_upButton_pressed()
{
    moveRobot(getLinearStep());
}

void RemoteWidget::on_downButton_pressed()
{
    moveRobot(-getLinearStep());
}

void RemoteWidget::rotateRobot(float/* angle*/)
{
    //TODO
}

void RemoteWidget::moveRobot(float/* distance*/)
{
    //TODO
}

float RemoteWidget::getAngularStep() const
{
    return m_angularStep;
}

float RemoteWidget::getLinearStep() const
{
    return m_linearStep;
}

void RemoteWidget::setAngularStep(float step)
{
    m_angularStep = step;
}

void RemoteWidget::setLinearStep(float step)
{
    m_linearStep = step;
}

void RemoteWidget::setSteps(float linearStep, float angularStep)
{
    setAngularStep(angularStep);
    setLinearStep(linearStep);
}
