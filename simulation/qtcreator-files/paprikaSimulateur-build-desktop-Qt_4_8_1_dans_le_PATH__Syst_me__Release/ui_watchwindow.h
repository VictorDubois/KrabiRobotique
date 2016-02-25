/********************************************************************************
** Form generated from reading UI file 'watchwindow.ui'
**
** Created: Thu Feb 11 15:34:48 2016
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WATCHWINDOW_H
#define UI_WATCHWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WatchWindow
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *noneButton;
    QPushButton *refreshButton;
    QVBoxLayout *watchList;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *WatchWindow)
    {
        if (WatchWindow->objectName().isEmpty())
            WatchWindow->setObjectName(QString::fromUtf8("WatchWindow"));
        WatchWindow->resize(400, 300);
        verticalLayout = new QVBoxLayout(WatchWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        noneButton = new QPushButton(WatchWindow);
        noneButton->setObjectName(QString::fromUtf8("noneButton"));

        horizontalLayout->addWidget(noneButton);

        refreshButton = new QPushButton(WatchWindow);
        refreshButton->setObjectName(QString::fromUtf8("refreshButton"));

        horizontalLayout->addWidget(refreshButton);


        verticalLayout->addLayout(horizontalLayout);

        watchList = new QVBoxLayout();
        watchList->setObjectName(QString::fromUtf8("watchList"));

        verticalLayout->addLayout(watchList);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(WatchWindow);

        QMetaObject::connectSlotsByName(WatchWindow);
    } // setupUi

    void retranslateUi(QWidget *WatchWindow)
    {
        WatchWindow->setWindowTitle(QApplication::translate("WatchWindow", "Watches", 0, QApplication::UnicodeUTF8));
        noneButton->setText(QApplication::translate("WatchWindow", "Deselect All", 0, QApplication::UnicodeUTF8));
        refreshButton->setText(QApplication::translate("WatchWindow", "Query", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WatchWindow: public Ui_WatchWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WATCHWINDOW_H
