/********************************************************************************
** Form generated from reading UI file 'odometriewindow.ui'
**
** Created: Thu Feb 11 15:34:48 2016
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ODOMETRIEWINDOW_H
#define UI_ODOMETRIEWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OdometrieWindow
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *label;
    QDoubleSpinBox *wheelSize;
    QLabel *label_2;
    QDoubleSpinBox *interAxisDistance;
    QHBoxLayout *horizontalLayout;
    QPushButton *applyButton;
    QPushButton *queryButton;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout_2;
    QLabel *label_3;
    QLabel *xRelativeLabel;
    QLabel *label_5;
    QLabel *yRelativeLabel;
    QLabel *label_7;
    QLabel *angleRelativeLabel;
    QPushButton *resetButton;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    QDoubleSpinBox *targetAngle;
    QLabel *label_4;
    QDoubleSpinBox *targetY;
    QDoubleSpinBox *targetX;
    QLabel *label_8;
    QLabel *label_6;
    QPushButton *setWheelSizeFromX;
    QPushButton *setWheelSizeFromY;
    QPushButton *setInterAxisFromAngle;

    void setupUi(QWidget *OdometrieWindow)
    {
        if (OdometrieWindow->objectName().isEmpty())
            OdometrieWindow->setObjectName(QString::fromUtf8("OdometrieWindow"));
        OdometrieWindow->resize(515, 422);
        verticalLayout = new QVBoxLayout(OdometrieWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(OdometrieWindow);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        wheelSize = new QDoubleSpinBox(groupBox);
        wheelSize->setObjectName(QString::fromUtf8("wheelSize"));
        wheelSize->setMaximum(999.99);

        formLayout->setWidget(0, QFormLayout::FieldRole, wheelSize);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        interAxisDistance = new QDoubleSpinBox(groupBox);
        interAxisDistance->setObjectName(QString::fromUtf8("interAxisDistance"));
        interAxisDistance->setMaximum(999.99);

        formLayout->setWidget(1, QFormLayout::FieldRole, interAxisDistance);


        verticalLayout->addWidget(groupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        applyButton = new QPushButton(OdometrieWindow);
        applyButton->setObjectName(QString::fromUtf8("applyButton"));

        horizontalLayout->addWidget(applyButton);

        queryButton = new QPushButton(OdometrieWindow);
        queryButton->setObjectName(QString::fromUtf8("queryButton"));

        horizontalLayout->addWidget(queryButton);


        verticalLayout->addLayout(horizontalLayout);

        groupBox_2 = new QGroupBox(OdometrieWindow);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        formLayout_2 = new QFormLayout(groupBox_2);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_3);

        xRelativeLabel = new QLabel(groupBox_2);
        xRelativeLabel->setObjectName(QString::fromUtf8("xRelativeLabel"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, xRelativeLabel);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_5);

        yRelativeLabel = new QLabel(groupBox_2);
        yRelativeLabel->setObjectName(QString::fromUtf8("yRelativeLabel"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, yRelativeLabel);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_7);

        angleRelativeLabel = new QLabel(groupBox_2);
        angleRelativeLabel->setObjectName(QString::fromUtf8("angleRelativeLabel"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, angleRelativeLabel);


        verticalLayout->addWidget(groupBox_2);

        resetButton = new QPushButton(OdometrieWindow);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));

        verticalLayout->addWidget(resetButton);

        groupBox_3 = new QGroupBox(OdometrieWindow);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout = new QGridLayout(groupBox_3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        targetAngle = new QDoubleSpinBox(groupBox_3);
        targetAngle->setObjectName(QString::fromUtf8("targetAngle"));
        targetAngle->setMinimum(-20);
        targetAngle->setMaximum(20);

        gridLayout->addWidget(targetAngle, 2, 1, 1, 1);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 0, 0, 1, 1);

        targetY = new QDoubleSpinBox(groupBox_3);
        targetY->setObjectName(QString::fromUtf8("targetY"));
        targetY->setMaximum(5000);

        gridLayout->addWidget(targetY, 1, 1, 1, 1);

        targetX = new QDoubleSpinBox(groupBox_3);
        targetX->setObjectName(QString::fromUtf8("targetX"));
        targetX->setMaximum(5000);

        gridLayout->addWidget(targetX, 0, 1, 1, 1);

        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 2, 0, 1, 1);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 1, 0, 1, 1);

        setWheelSizeFromX = new QPushButton(groupBox_3);
        setWheelSizeFromX->setObjectName(QString::fromUtf8("setWheelSizeFromX"));

        gridLayout->addWidget(setWheelSizeFromX, 0, 2, 1, 1);

        setWheelSizeFromY = new QPushButton(groupBox_3);
        setWheelSizeFromY->setObjectName(QString::fromUtf8("setWheelSizeFromY"));

        gridLayout->addWidget(setWheelSizeFromY, 1, 2, 1, 1);

        setInterAxisFromAngle = new QPushButton(groupBox_3);
        setInterAxisFromAngle->setObjectName(QString::fromUtf8("setInterAxisFromAngle"));

        gridLayout->addWidget(setInterAxisFromAngle, 2, 2, 1, 1);


        verticalLayout->addWidget(groupBox_3);


        retranslateUi(OdometrieWindow);

        QMetaObject::connectSlotsByName(OdometrieWindow);
    } // setupUi

    void retranslateUi(QWidget *OdometrieWindow)
    {
        OdometrieWindow->setWindowTitle(QApplication::translate("OdometrieWindow", "Odom\303\251trie", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("OdometrieWindow", "Settings", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("OdometrieWindow", "Wheel size", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("OdometrieWindow", "Inter-axis distance", 0, QApplication::UnicodeUTF8));
        applyButton->setText(QApplication::translate("OdometrieWindow", "Apply", 0, QApplication::UnicodeUTF8));
        queryButton->setText(QApplication::translate("OdometrieWindow", "Query", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("OdometrieWindow", "Infos", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("OdometrieWindow", "x relative", 0, QApplication::UnicodeUTF8));
        xRelativeLabel->setText(QString());
        label_5->setText(QApplication::translate("OdometrieWindow", "y relative", 0, QApplication::UnicodeUTF8));
        yRelativeLabel->setText(QString());
        label_7->setText(QApplication::translate("OdometrieWindow", "angle relative", 0, QApplication::UnicodeUTF8));
        angleRelativeLabel->setText(QString());
        resetButton->setText(QApplication::translate("OdometrieWindow", "Reset", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("OdometrieWindow", "Auto Compute", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("OdometrieWindow", "Target x", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("OdometrieWindow", "Target Angle (\302\260)", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("OdometrieWindow", "Target y", 0, QApplication::UnicodeUTF8));
        setWheelSizeFromX->setText(QApplication::translate("OdometrieWindow", "Compute Wheel size from x", 0, QApplication::UnicodeUTF8));
        setWheelSizeFromY->setText(QApplication::translate("OdometrieWindow", "Compute Wheel size from y", 0, QApplication::UnicodeUTF8));
        setInterAxisFromAngle->setText(QApplication::translate("OdometrieWindow", "Compute Inter-axis from angle", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class OdometrieWindow: public Ui_OdometrieWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ODOMETRIEWINDOW_H
