/********************************************************************************
** Form generated from reading UI file 'bluetoothwindow.ui'
**
** Created: Thu Feb 11 15:34:48 2016
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BLUETOOTHWINDOW_H
#define UI_BLUETOOTHWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BluetoothWindow
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QListWidget *list;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *power;
    QCheckBox *discoverable;
    QHBoxLayout *horizontalLayout;
    QPushButton *selectButton;
    QPushButton *scan;
    QGroupBox *groupBox_3;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *labelDevice;
    QLabel *label_2;
    QLabel *statusLabel;

    void setupUi(QWidget *BluetoothWindow)
    {
        if (BluetoothWindow->objectName().isEmpty())
            BluetoothWindow->setObjectName(QString::fromUtf8("BluetoothWindow"));
        BluetoothWindow->resize(400, 411);
        verticalLayout = new QVBoxLayout(BluetoothWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_2 = new QGroupBox(BluetoothWindow);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        list = new QListWidget(groupBox_2);
        list->setObjectName(QString::fromUtf8("list"));

        verticalLayout_2->addWidget(list);

        groupBox = new QGroupBox(groupBox_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        power = new QCheckBox(groupBox);
        power->setObjectName(QString::fromUtf8("power"));
        power->setChecked(true);

        horizontalLayout_2->addWidget(power);

        discoverable = new QCheckBox(groupBox);
        discoverable->setObjectName(QString::fromUtf8("discoverable"));
        discoverable->setChecked(true);

        horizontalLayout_2->addWidget(discoverable);


        verticalLayout_2->addWidget(groupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        selectButton = new QPushButton(groupBox_2);
        selectButton->setObjectName(QString::fromUtf8("selectButton"));

        horizontalLayout->addWidget(selectButton);

        scan = new QPushButton(groupBox_2);
        scan->setObjectName(QString::fromUtf8("scan"));

        horizontalLayout->addWidget(scan);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(BluetoothWindow);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        formLayout = new QFormLayout(groupBox_3);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        labelDevice = new QLabel(groupBox_3);
        labelDevice->setObjectName(QString::fromUtf8("labelDevice"));

        formLayout->setWidget(0, QFormLayout::FieldRole, labelDevice);

        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        statusLabel = new QLabel(groupBox_3);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));

        formLayout->setWidget(1, QFormLayout::FieldRole, statusLabel);


        verticalLayout->addWidget(groupBox_3);


        retranslateUi(BluetoothWindow);

        QMetaObject::connectSlotsByName(BluetoothWindow);
    } // setupUi

    void retranslateUi(QWidget *BluetoothWindow)
    {
        BluetoothWindow->setWindowTitle(QApplication::translate("BluetoothWindow", "Bluetooth Scanner", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("BluetoothWindow", "Scanner", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("BluetoothWindow", "Local Device", 0, QApplication::UnicodeUTF8));
        power->setText(QApplication::translate("BluetoothWindow", "Bluetooth Powered On", 0, QApplication::UnicodeUTF8));
        discoverable->setText(QApplication::translate("BluetoothWindow", "Discoverable", 0, QApplication::UnicodeUTF8));
        selectButton->setText(QApplication::translate("BluetoothWindow", "Select", 0, QApplication::UnicodeUTF8));
        scan->setText(QApplication::translate("BluetoothWindow", "Scan", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("BluetoothWindow", "Device", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("BluetoothWindow", "Current device :", 0, QApplication::UnicodeUTF8));
        labelDevice->setText(QString());
        label_2->setText(QApplication::translate("BluetoothWindow", "Status :", 0, QApplication::UnicodeUTF8));
        statusLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class BluetoothWindow: public Ui_BluetoothWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLUETOOTHWINDOW_H
