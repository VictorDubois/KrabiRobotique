#ifndef MOVEMENTSETTINGSWIDGET_H
#define MOVEMENTSETTINGSWIDGET_H

#include <QWidget>

class QDoubleSpinBox;
class QGroupBox;
class QCheckBox;

class MovementSettingsWidget: public QWidget
{
    Q_OBJECT
    public:
        explicit MovementSettingsWidget(QWidget *parent = nullptr);

    signals:

        void stepsUpdated(float linearStep, float angularStep);

        void tableOrientationChanged(bool rotated);

    private:
        void on_stepsUpdated(double);

        void changeTableOrientation(bool rotated);

        QGroupBox* m_stepsGB;
        QDoubleSpinBox* m_angularStepSB;
        QDoubleSpinBox* m_linearStepSB;

        QGroupBox* m_tableGB;
        QCheckBox* m_tableOrientationCB;
};

#endif // MOVEMENTSETTINGSWIDGET_H
