/********************************************************************************
** Form generated from reading UI file 'remotedebug.ui'
**
** Created: Thu Feb 11 15:34:48 2016
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REMOTEDEBUG_H
#define UI_REMOTEDEBUG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QToolBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RemoteDebug
{
public:
    QVBoxLayout *verticalLayout;
    QToolBox *toolBox;
    QWidget *page;
    QWidget *page_2;

    void setupUi(QWidget *RemoteDebug)
    {
        if (RemoteDebug->objectName().isEmpty())
            RemoteDebug->setObjectName(QString::fromUtf8("RemoteDebug"));
        RemoteDebug->resize(524, 519);
        verticalLayout = new QVBoxLayout(RemoteDebug);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        toolBox = new QToolBox(RemoteDebug);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        page->setGeometry(QRect(0, 0, 506, 439));
        toolBox->addItem(page, QString::fromUtf8("Page 1"));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setGeometry(QRect(0, 0, 506, 439));
        toolBox->addItem(page_2, QString::fromUtf8("Page 2"));

        verticalLayout->addWidget(toolBox);


        retranslateUi(RemoteDebug);

        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(RemoteDebug);
    } // setupUi

    void retranslateUi(QWidget *RemoteDebug)
    {
        RemoteDebug->setWindowTitle(QApplication::translate("RemoteDebug", "Remote Debug", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("RemoteDebug", "Page 1", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("RemoteDebug", "Page 2", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RemoteDebug: public Ui_RemoteDebug {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REMOTEDEBUG_H
