/********************************************************************************
** Form generated from reading UI file 'debugwindow.ui'
**
** Created: Thu Feb 11 15:34:48 2016
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEBUGWINDOW_H
#define UI_DEBUGWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DebugWindow
{
public:
    QAction *actionSimulateur;
    QAction *actionOdom_trie;
    QAction *actionAsservissement;
    QAction *actionDisplay_route;
    QAction *actionHide_table;
    QAction *actionReset_objects;
    QAction *actionRemove_objects;
    QAction *actionDisplay_strategy;
    QAction *actionRemote_Mod;
    QAction *actionBluetooth;
    QAction *actionBluetooth_Interface;
    QAction *actionOdometrie;
    QAction *actionAsserv_Window;
    QAction *actionSharps;
    QAction *actionWatches;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *infoField;
    QMenuBar *menubar;
    QMenu *menuPerspective;
    QMenu *menuViews;
    QMenu *menuSettings;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *DebugWindow)
    {
        if (DebugWindow->objectName().isEmpty())
            DebugWindow->setObjectName(QString::fromUtf8("DebugWindow"));
        DebugWindow->resize(800, 600);
        actionSimulateur = new QAction(DebugWindow);
        actionSimulateur->setObjectName(QString::fromUtf8("actionSimulateur"));
        actionOdom_trie = new QAction(DebugWindow);
        actionOdom_trie->setObjectName(QString::fromUtf8("actionOdom_trie"));
        actionAsservissement = new QAction(DebugWindow);
        actionAsservissement->setObjectName(QString::fromUtf8("actionAsservissement"));
        actionDisplay_route = new QAction(DebugWindow);
        actionDisplay_route->setObjectName(QString::fromUtf8("actionDisplay_route"));
        actionDisplay_route->setCheckable(true);
        actionDisplay_route->setChecked(false);
        actionHide_table = new QAction(DebugWindow);
        actionHide_table->setObjectName(QString::fromUtf8("actionHide_table"));
        actionHide_table->setCheckable(true);
        actionReset_objects = new QAction(DebugWindow);
        actionReset_objects->setObjectName(QString::fromUtf8("actionReset_objects"));
        actionRemove_objects = new QAction(DebugWindow);
        actionRemove_objects->setObjectName(QString::fromUtf8("actionRemove_objects"));
        actionDisplay_strategy = new QAction(DebugWindow);
        actionDisplay_strategy->setObjectName(QString::fromUtf8("actionDisplay_strategy"));
        actionDisplay_strategy->setCheckable(true);
        actionDisplay_strategy->setChecked(true);
        actionRemote_Mod = new QAction(DebugWindow);
        actionRemote_Mod->setObjectName(QString::fromUtf8("actionRemote_Mod"));
        actionRemote_Mod->setCheckable(true);
        actionBluetooth = new QAction(DebugWindow);
        actionBluetooth->setObjectName(QString::fromUtf8("actionBluetooth"));
        actionBluetooth->setCheckable(true);
        actionBluetooth_Interface = new QAction(DebugWindow);
        actionBluetooth_Interface->setObjectName(QString::fromUtf8("actionBluetooth_Interface"));
        actionBluetooth_Interface->setCheckable(true);
        actionOdometrie = new QAction(DebugWindow);
        actionOdometrie->setObjectName(QString::fromUtf8("actionOdometrie"));
        actionOdometrie->setCheckable(true);
        actionAsserv_Window = new QAction(DebugWindow);
        actionAsserv_Window->setObjectName(QString::fromUtf8("actionAsserv_Window"));
        actionAsserv_Window->setCheckable(true);
        actionSharps = new QAction(DebugWindow);
        actionSharps->setObjectName(QString::fromUtf8("actionSharps"));
        actionSharps->setCheckable(true);
        actionWatches = new QAction(DebugWindow);
        actionWatches->setObjectName(QString::fromUtf8("actionWatches"));
        actionWatches->setCheckable(true);
        centralwidget = new QWidget(DebugWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        infoField = new QLabel(centralwidget);
        infoField->setObjectName(QString::fromUtf8("infoField"));

        verticalLayout->addWidget(infoField);

        DebugWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(DebugWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        menuPerspective = new QMenu(menubar);
        menuPerspective->setObjectName(QString::fromUtf8("menuPerspective"));
        menuViews = new QMenu(menubar);
        menuViews->setObjectName(QString::fromUtf8("menuViews"));
        menuSettings = new QMenu(menubar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        DebugWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(DebugWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        DebugWindow->setStatusBar(statusbar);

        menubar->addAction(menuSettings->menuAction());
        menubar->addAction(menuPerspective->menuAction());
        menubar->addAction(menuViews->menuAction());
        menuPerspective->addAction(actionSimulateur);
        menuPerspective->addAction(actionOdom_trie);
        menuPerspective->addAction(actionAsservissement);
        menuViews->addAction(actionBluetooth);
        menuViews->addAction(actionBluetooth_Interface);
        menuViews->addAction(actionOdometrie);
        menuViews->addAction(actionAsserv_Window);
        menuViews->addAction(actionSharps);
        menuViews->addAction(actionWatches);
        menuSettings->addAction(actionDisplay_route);
        menuSettings->addAction(actionDisplay_strategy);
        menuSettings->addAction(actionHide_table);
        menuSettings->addAction(actionReset_objects);
        menuSettings->addAction(actionRemove_objects);
        menuSettings->addAction(actionRemote_Mod);

        retranslateUi(DebugWindow);

        QMetaObject::connectSlotsByName(DebugWindow);
    } // setupUi

    void retranslateUi(QMainWindow *DebugWindow)
    {
        DebugWindow->setWindowTitle(QApplication::translate("DebugWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionSimulateur->setText(QApplication::translate("DebugWindow", "Simulateur", 0, QApplication::UnicodeUTF8));
        actionOdom_trie->setText(QApplication::translate("DebugWindow", "Odometrie", 0, QApplication::UnicodeUTF8));
        actionAsservissement->setText(QApplication::translate("DebugWindow", "Asservissement", 0, QApplication::UnicodeUTF8));
        actionDisplay_route->setText(QApplication::translate("DebugWindow", "Display route", 0, QApplication::UnicodeUTF8));
        actionHide_table->setText(QApplication::translate("DebugWindow", "Hide table", 0, QApplication::UnicodeUTF8));
        actionReset_objects->setText(QApplication::translate("DebugWindow", "Reset objects", 0, QApplication::UnicodeUTF8));
        actionRemove_objects->setText(QApplication::translate("DebugWindow", "Remove objects", 0, QApplication::UnicodeUTF8));
        actionDisplay_strategy->setText(QApplication::translate("DebugWindow", "Display strategy", 0, QApplication::UnicodeUTF8));
        actionRemote_Mod->setText(QApplication::translate("DebugWindow", "Remote Mod", 0, QApplication::UnicodeUTF8));
        actionBluetooth->setText(QApplication::translate("DebugWindow", "Bluetooth Scanner", 0, QApplication::UnicodeUTF8));
        actionBluetooth_Interface->setText(QApplication::translate("DebugWindow", "Bluetooth Interface", 0, QApplication::UnicodeUTF8));
        actionOdometrie->setText(QApplication::translate("DebugWindow", "Odometrie", 0, QApplication::UnicodeUTF8));
        actionAsserv_Window->setText(QApplication::translate("DebugWindow", "Asserv", 0, QApplication::UnicodeUTF8));
        actionSharps->setText(QApplication::translate("DebugWindow", "Sharps", 0, QApplication::UnicodeUTF8));
        actionWatches->setText(QApplication::translate("DebugWindow", "Watches", 0, QApplication::UnicodeUTF8));
        infoField->setText(QApplication::translate("DebugWindow", "...", 0, QApplication::UnicodeUTF8));
        menuPerspective->setTitle(QApplication::translate("DebugWindow", "Perspectives", 0, QApplication::UnicodeUTF8));
        menuViews->setTitle(QApplication::translate("DebugWindow", "Views", 0, QApplication::UnicodeUTF8));
        menuSettings->setTitle(QApplication::translate("DebugWindow", "Settings", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DebugWindow: public Ui_DebugWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBUGWINDOW_H
