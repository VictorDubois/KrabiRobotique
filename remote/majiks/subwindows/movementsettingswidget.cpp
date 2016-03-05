#include "movementsettingswidget.h"

#include <QGroupBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QBoxLayout>
#include <QGridLayout>

MovementSettingsWidget::MovementSettingsWidget(QWidget *parent) : QWidget(parent)
{
    m_stepsGB = new QGroupBox(tr("Pas de déplacement"), this);

    m_angularStepSB = new QDoubleSpinBox(this);
    m_angularStepSB->setSuffix(tr(" °"));
    m_angularStepSB->setSingleStep(0.5);
    m_angularStepSB->setRange(0., 360.);
    m_angularStepSB->setValue(1.);

    m_linearStepSB = new QDoubleSpinBox(this);
    m_linearStepSB->setSuffix(tr(" mm"));
    m_linearStepSB->setSingleStep(10.);
    m_linearStepSB->setRange(0., 1000.);
    m_linearStepSB->setValue(10.);

    connect(m_angularStepSB,    static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &MovementSettingsWidget::on_stepsUpdated);
    connect(m_linearStepSB,     static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &MovementSettingsWidget::on_stepsUpdated);

    QVBoxLayout* layout = new QVBoxLayout(this);

    QGridLayout* stepsLayout = new QGridLayout(m_stepsGB);
    stepsLayout->addWidget(new QLabel(tr("Distance")),  1, 1);
    stepsLayout->addWidget(new QLabel(tr("Angle")),     1, 2);
    stepsLayout->addWidget(m_linearStepSB,              2, 1);
    stepsLayout->addWidget(m_angularStepSB,             2, 2);

    layout->addWidget(m_stepsGB);
    layout->addStretch();
}


void MovementSettingsWidget::on_stepsUpdated(double)
{
    emit stepsUpdated(static_cast<float>(m_linearStepSB->value()), static_cast<float>(m_angularStepSB->value()));
}
