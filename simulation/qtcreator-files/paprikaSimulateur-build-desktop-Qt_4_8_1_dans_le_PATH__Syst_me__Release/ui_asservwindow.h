/********************************************************************************
** Form generated from reading UI file 'asservwindow.ui'
**
** Created: Thu Feb 11 15:34:48 2016
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASSERVWINDOW_H
#define UI_ASSERVWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AsservWindow
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *label;
    QDoubleSpinBox *linKp;
    QLabel *label_2;
    QDoubleSpinBox *linKi;
    QLabel *label_3;
    QDoubleSpinBox *linKd;
    QCheckBox *linearEnabled;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *linQuery;
    QPushButton *linSet;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout_2;
    QLabel *label_4;
    QDoubleSpinBox *angKp;
    QLabel *label_6;
    QDoubleSpinBox *angKi;
    QLabel *label_5;
    QDoubleSpinBox *angKd;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *angQuery;
    QPushButton *angSet;
    QCheckBox *angularEnabled;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *linearGraph;
    QCheckBox *angularGraph;
    QCheckBox *dutyGraph;
    QGroupBox *groupBox_3;
    QFormLayout *formLayout_3;
    QLabel *label_7;
    QDoubleSpinBox *linSpeed;
    QLabel *label_8;
    QDoubleSpinBox *angSpeed;
    QLabel *label_10;
    QDoubleSpinBox *engineLimit;
    QLabel *label_9;
    QSpinBox *duration;
    QLabel *label_11;
    QLabel *durationLabel;
    QPushButton *stopButton;
    QPushButton *runButton;
    QCheckBox *clickGoto;

    void setupUi(QWidget *AsservWindow)
    {
        if (AsservWindow->objectName().isEmpty())
            AsservWindow->setObjectName(QString::fromUtf8("AsservWindow"));
        AsservWindow->resize(634, 494);
        verticalLayout = new QVBoxLayout(AsservWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBox = new QGroupBox(AsservWindow);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        linKp = new QDoubleSpinBox(groupBox);
        linKp->setObjectName(QString::fromUtf8("linKp"));
        linKp->setDecimals(5);
        linKp->setSingleStep(0.1);

        formLayout->setWidget(0, QFormLayout::FieldRole, linKp);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        linKi = new QDoubleSpinBox(groupBox);
        linKi->setObjectName(QString::fromUtf8("linKi"));
        linKi->setDecimals(5);
        linKi->setSingleStep(0.001);

        formLayout->setWidget(1, QFormLayout::FieldRole, linKi);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        linKd = new QDoubleSpinBox(groupBox);
        linKd->setObjectName(QString::fromUtf8("linKd"));
        linKd->setDecimals(5);
        linKd->setSingleStep(0.1);

        formLayout->setWidget(2, QFormLayout::FieldRole, linKd);

        linearEnabled = new QCheckBox(groupBox);
        linearEnabled->setObjectName(QString::fromUtf8("linearEnabled"));
        linearEnabled->setChecked(true);

        formLayout->setWidget(3, QFormLayout::FieldRole, linearEnabled);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        linQuery = new QPushButton(groupBox);
        linQuery->setObjectName(QString::fromUtf8("linQuery"));

        horizontalLayout_2->addWidget(linQuery);

        linSet = new QPushButton(groupBox);
        linSet->setObjectName(QString::fromUtf8("linSet"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        linSet->setFont(font);

        horizontalLayout_2->addWidget(linSet);


        formLayout->setLayout(4, QFormLayout::FieldRole, horizontalLayout_2);


        horizontalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(AsservWindow);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        formLayout_2 = new QFormLayout(groupBox_2);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_4);

        angKp = new QDoubleSpinBox(groupBox_2);
        angKp->setObjectName(QString::fromUtf8("angKp"));
        angKp->setDecimals(5);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, angKp);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_6);

        angKi = new QDoubleSpinBox(groupBox_2);
        angKi->setObjectName(QString::fromUtf8("angKi"));
        angKi->setDecimals(5);
        angKi->setSingleStep(0.1);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, angKi);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_5);

        angKd = new QDoubleSpinBox(groupBox_2);
        angKd->setObjectName(QString::fromUtf8("angKd"));
        angKd->setDecimals(5);
        angKd->setSingleStep(0.1);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, angKd);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        angQuery = new QPushButton(groupBox_2);
        angQuery->setObjectName(QString::fromUtf8("angQuery"));

        horizontalLayout_3->addWidget(angQuery);

        angSet = new QPushButton(groupBox_2);
        angSet->setObjectName(QString::fromUtf8("angSet"));
        angSet->setFont(font);

        horizontalLayout_3->addWidget(angSet);


        formLayout_2->setLayout(4, QFormLayout::FieldRole, horizontalLayout_3);

        angularEnabled = new QCheckBox(groupBox_2);
        angularEnabled->setObjectName(QString::fromUtf8("angularEnabled"));
        angularEnabled->setChecked(true);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, angularEnabled);


        horizontalLayout->addWidget(groupBox_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        linearGraph = new QCheckBox(AsservWindow);
        linearGraph->setObjectName(QString::fromUtf8("linearGraph"));
        linearGraph->setChecked(true);

        horizontalLayout_4->addWidget(linearGraph);

        angularGraph = new QCheckBox(AsservWindow);
        angularGraph->setObjectName(QString::fromUtf8("angularGraph"));

        horizontalLayout_4->addWidget(angularGraph);

        dutyGraph = new QCheckBox(AsservWindow);
        dutyGraph->setObjectName(QString::fromUtf8("dutyGraph"));

        horizontalLayout_4->addWidget(dutyGraph);


        verticalLayout->addLayout(horizontalLayout_4);

        groupBox_3 = new QGroupBox(AsservWindow);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        formLayout_3 = new QFormLayout(groupBox_3);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_7);

        linSpeed = new QDoubleSpinBox(groupBox_3);
        linSpeed->setObjectName(QString::fromUtf8("linSpeed"));
        linSpeed->setMinimum(-10);
        linSpeed->setMaximum(10);
        linSpeed->setSingleStep(0.5);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, linSpeed);

        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_8);

        angSpeed = new QDoubleSpinBox(groupBox_3);
        angSpeed->setObjectName(QString::fromUtf8("angSpeed"));
        angSpeed->setDecimals(5);
        angSpeed->setMinimum(-1);
        angSpeed->setMaximum(1);
        angSpeed->setSingleStep(0.5);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, angSpeed);

        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_10);

        engineLimit = new QDoubleSpinBox(groupBox_3);
        engineLimit->setObjectName(QString::fromUtf8("engineLimit"));
        engineLimit->setMinimum(-1);
        engineLimit->setMaximum(1);
        engineLimit->setSingleStep(0.1);
        engineLimit->setValue(1);

        formLayout_3->setWidget(2, QFormLayout::FieldRole, engineLimit);

        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout_3->setWidget(3, QFormLayout::LabelRole, label_9);

        duration = new QSpinBox(groupBox_3);
        duration->setObjectName(QString::fromUtf8("duration"));
        duration->setMinimum(10);
        duration->setMaximum(10000);
        duration->setSingleStep(50);
        duration->setValue(200);

        formLayout_3->setWidget(3, QFormLayout::FieldRole, duration);

        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        formLayout_3->setWidget(4, QFormLayout::LabelRole, label_11);

        durationLabel = new QLabel(groupBox_3);
        durationLabel->setObjectName(QString::fromUtf8("durationLabel"));

        formLayout_3->setWidget(4, QFormLayout::FieldRole, durationLabel);

        stopButton = new QPushButton(groupBox_3);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));

        formLayout_3->setWidget(5, QFormLayout::LabelRole, stopButton);

        runButton = new QPushButton(groupBox_3);
        runButton->setObjectName(QString::fromUtf8("runButton"));
        runButton->setFont(font);

        formLayout_3->setWidget(5, QFormLayout::FieldRole, runButton);


        verticalLayout->addWidget(groupBox_3);

        clickGoto = new QCheckBox(AsservWindow);
        clickGoto->setObjectName(QString::fromUtf8("clickGoto"));
        clickGoto->setChecked(true);

        verticalLayout->addWidget(clickGoto);


        retranslateUi(AsservWindow);

        QMetaObject::connectSlotsByName(AsservWindow);
    } // setupUi

    void retranslateUi(QWidget *AsservWindow)
    {
        AsservWindow->setWindowTitle(QApplication::translate("AsservWindow", "Asservissement", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("AsservWindow", "LinearPID", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AsservWindow", "Kp", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("AsservWindow", "Ki", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("AsservWindow", "Kd", 0, QApplication::UnicodeUTF8));
        linearEnabled->setText(QApplication::translate("AsservWindow", "Enabled", 0, QApplication::UnicodeUTF8));
        linQuery->setText(QApplication::translate("AsservWindow", "Query", 0, QApplication::UnicodeUTF8));
        linSet->setText(QApplication::translate("AsservWindow", "Send", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("AsservWindow", "AngularPID", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("AsservWindow", "Kp", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("AsservWindow", "Ki", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("AsservWindow", "Kd", 0, QApplication::UnicodeUTF8));
        angQuery->setText(QApplication::translate("AsservWindow", "Query", 0, QApplication::UnicodeUTF8));
        angSet->setText(QApplication::translate("AsservWindow", "Send", 0, QApplication::UnicodeUTF8));
        angularEnabled->setText(QApplication::translate("AsservWindow", "Enabled", 0, QApplication::UnicodeUTF8));
        linearGraph->setText(QApplication::translate("AsservWindow", "Linear Graph", 0, QApplication::UnicodeUTF8));
        angularGraph->setText(QApplication::translate("AsservWindow", "Angular Graph", 0, QApplication::UnicodeUTF8));
        dutyGraph->setText(QApplication::translate("AsservWindow", "Duty Graph", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("AsservWindow", "Test", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("AsservWindow", "Linear Speed", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("AsservWindow", "Angular Speed", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("AsservWindow", "Engine Limit (-1 ... 1)", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("AsservWindow", "Test Duration (cycles)", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("AsservWindow", "Test Duration (seconds)", 0, QApplication::UnicodeUTF8));
        durationLabel->setText(QString());
        stopButton->setText(QApplication::translate("AsservWindow", "Stop", 0, QApplication::UnicodeUTF8));
        runButton->setText(QApplication::translate("AsservWindow", "Run", 0, QApplication::UnicodeUTF8));
        clickGoto->setText(QApplication::translate("AsservWindow", "Right click on the table to send the robot to this location", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AsservWindow: public Ui_AsservWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASSERVWINDOW_H
