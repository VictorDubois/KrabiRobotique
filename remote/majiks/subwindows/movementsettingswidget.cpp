#include "movementsettingswidget.h"

#include <QGroupBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QCheckBox>
#include <QBoxLayout>
#include <QGridLayout>

MovementSettingsWidget::MovementSettingsWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    m_stepsGB = new QGroupBox(tr("Movement steps"), this);

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

    QGridLayout* stepsLayout = new QGridLayout(m_stepsGB);
    stepsLayout->addWidget(new QLabel(tr("Distance")),  1, 1);
    stepsLayout->addWidget(new QLabel(tr("Angle")),     1, 2);
    stepsLayout->addWidget(m_linearStepSB,              2, 1);
    stepsLayout->addWidget(m_angularStepSB,             2, 2);

    layout->addWidget(m_stepsGB);


    m_tableGB = new QGroupBox(tr("Table settings"), this);

    m_tableOrientationCB = new QCheckBox(tr("Swap table axes"), this);

    connect(m_tableOrientationCB, &QCheckBox::toggled, this, &MovementSettingsWidget::changeTableOrientation);

    QGridLayout* tableSettingsLayout = new QGridLayout(m_tableGB);
    tableSettingsLayout->addWidget(m_tableOrientationCB, 1, 1);

    layout->addWidget(m_tableGB);
    layout->addStretch();
}

void MovementSettingsWidget::changeTableOrientation(bool rotated)
{
    emit tableOrientationChanged(rotated);
}


void MovementSettingsWidget::on_stepsUpdated(double)
{
    emit stepsUpdated(static_cast<float>(m_linearStepSB->value()), static_cast<float>(m_angularStepSB->value()));
}
