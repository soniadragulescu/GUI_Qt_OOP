/********************************************************************************
** Form generated from reading UI file 'laborator1011OOP.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LABORATOR1011OOP_H
#define UI_LABORATOR1011OOP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_laborator1011OOPClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *laborator1011OOPClass)
    {
        if (laborator1011OOPClass->objectName().isEmpty())
            laborator1011OOPClass->setObjectName(QString::fromUtf8("laborator1011OOPClass"));
        laborator1011OOPClass->resize(600, 400);
        menuBar = new QMenuBar(laborator1011OOPClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        laborator1011OOPClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(laborator1011OOPClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        laborator1011OOPClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(laborator1011OOPClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        laborator1011OOPClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(laborator1011OOPClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        laborator1011OOPClass->setStatusBar(statusBar);

        retranslateUi(laborator1011OOPClass);

        QMetaObject::connectSlotsByName(laborator1011OOPClass);
    } // setupUi

    void retranslateUi(QMainWindow *laborator1011OOPClass)
    {
        laborator1011OOPClass->setWindowTitle(QApplication::translate("laborator1011OOPClass", "laborator1011OOP", nullptr));
    } // retranslateUi

};

namespace Ui {
    class laborator1011OOPClass: public Ui_laborator1011OOPClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LABORATOR1011OOP_H
