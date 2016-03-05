#ifndef MOVEMENTSETTINGSWIDGET_H
#define MOVEMENTSETTINGSWIDGET_H

#include <QWidget>

class QDoubleSpinBox;
class QGroupBox;

class MovementSettingsWidget: public QWidget
{
    Q_OBJECT
    public:
        explicit MovementSettingsWidget(QWidget *parent = nullptr);

    signals:

        void stepsUpdated(float linearStep, float angularStep);

    private:
        void on_stepsUpdated(double);

        QGroupBox* m_stepsGB;
        QDoubleSpinBox* m_angularStepSB;
        QDoubleSpinBox* m_linearStepSB;
};

#endif // MOVEMENTSETTINGSWIDGET_H
