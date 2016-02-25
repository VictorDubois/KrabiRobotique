/********************************************************************************
** Form generated from reading UI file 'bluetoothinterface.ui'
**
** Created: Thu Feb 11 15:34:48 2016
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BLUETOOTHINTERFACE_H
#define UI_BLUETOOTHINTERFACE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BluetoothInterface
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QRadioButton *radioDebug;
    QRadioButton *radioNormal;
    QTextBrowser *debugBrowser;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *commandEditLine;
    QPushButton *sendButton;

    void setupUi(QWidget *BluetoothInterface)
    {
        if (BluetoothInterface->objectName().isEmpty())
            BluetoothInterface->setObjectName(QString::fromUtf8("BluetoothInterface"));
        BluetoothInterface->resize(839, 522);
        verticalLayout = new QVBoxLayout(BluetoothInterface);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(BluetoothInterface);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        radioDebug = new QRadioButton(BluetoothInterface);
        radioDebug->setObjectName(QString::fromUtf8("radioDebug"));

        horizontalLayout->addWidget(radioDebug);

        radioNormal = new QRadioButton(BluetoothInterface);
        radioNormal->setObjectName(QString::fromUtf8("radioNormal"));
        radioNormal->setChecked(true);

        horizontalLayout->addWidget(radioNormal);


        verticalLayout->addLayout(horizontalLayout);

        debugBrowser = new QTextBrowser(BluetoothInterface);
        debugBrowser->setObjectName(QString::fromUtf8("debugBrowser"));

        verticalLayout->addWidget(debugBrowser);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        commandEditLine = new QLineEdit(BluetoothInterface);
        commandEditLine->setObjectName(QString::fromUtf8("commandEditLine"));

        horizontalLayout_2->addWidget(commandEditLine);

        sendButton = new QPushButton(BluetoothInterface);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));

        horizontalLayout_2->addWidget(sendButton);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(BluetoothInterface);

        QMetaObject::connectSlotsByName(BluetoothInterface);
    } // setupUi

    void retranslateUi(QWidget *BluetoothInterface)
    {
        BluetoothInterface->setWindowTitle(QApplication::translate("BluetoothInterface", "Bluetooth Interface", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("BluetoothInterface", "Console :", 0, QApplication::UnicodeUTF8));
        radioDebug->setText(QApplication::translate("BluetoothInterface", "Debug", 0, QApplication::UnicodeUTF8));
        radioNormal->setText(QApplication::translate("BluetoothInterface", "Normal", 0, QApplication::UnicodeUTF8));
        sendButton->setText(QApplication::translate("BluetoothInterface", "Send", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BluetoothInterface: public Ui_BluetoothInterface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLUETOOTHINTERFACE_H
