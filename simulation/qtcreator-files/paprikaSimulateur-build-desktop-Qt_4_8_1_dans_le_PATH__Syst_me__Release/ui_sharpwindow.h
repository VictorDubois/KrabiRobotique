/********************************************************************************
** Form generated from reading UI file 'sharpwindow.ui'
**
** Created: Thu Feb 11 15:34:48 2016
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHARPWINDOW_H
#define UI_SHARPWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHeaderView>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SharpWindow
{
public:
    QVBoxLayout *verticalLayout;
    QCheckBox *watchCheckBox;
    QTableWidget *sharpsList;

    void setupUi(QWidget *SharpWindow)
    {
        if (SharpWindow->objectName().isEmpty())
            SharpWindow->setObjectName(QString::fromUtf8("SharpWindow"));
        SharpWindow->resize(400, 421);
        verticalLayout = new QVBoxLayout(SharpWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        watchCheckBox = new QCheckBox(SharpWindow);
        watchCheckBox->setObjectName(QString::fromUtf8("watchCheckBox"));

        verticalLayout->addWidget(watchCheckBox);

        sharpsList = new QTableWidget(SharpWindow);
        sharpsList->setObjectName(QString::fromUtf8("sharpsList"));
        sharpsList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        sharpsList->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(sharpsList);


        retranslateUi(SharpWindow);

        QMetaObject::connectSlotsByName(SharpWindow);
    } // setupUi

    void retranslateUi(QWidget *SharpWindow)
    {
        SharpWindow->setWindowTitle(QApplication::translate("SharpWindow", "Sharps", 0, QApplication::UnicodeUTF8));
        watchCheckBox->setText(QApplication::translate("SharpWindow", "Check sharps", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SharpWindow: public Ui_SharpWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHARPWINDOW_H
