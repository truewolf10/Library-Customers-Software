/********************************************************************************
** Form generated from reading UI file 'bibliotecacartigui.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BIBLIOTECACARTIGUI_H
#define UI_BIBLIOTECACARTIGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BibliotecaCartiGUIClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BibliotecaCartiGUIClass)
    {
        if (BibliotecaCartiGUIClass->objectName().isEmpty())
            BibliotecaCartiGUIClass->setObjectName(QStringLiteral("BibliotecaCartiGUIClass"));
        BibliotecaCartiGUIClass->resize(600, 400);
        menuBar = new QMenuBar(BibliotecaCartiGUIClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        BibliotecaCartiGUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BibliotecaCartiGUIClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BibliotecaCartiGUIClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(BibliotecaCartiGUIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        BibliotecaCartiGUIClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(BibliotecaCartiGUIClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BibliotecaCartiGUIClass->setStatusBar(statusBar);

        retranslateUi(BibliotecaCartiGUIClass);

        QMetaObject::connectSlotsByName(BibliotecaCartiGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *BibliotecaCartiGUIClass)
    {
        BibliotecaCartiGUIClass->setWindowTitle(QApplication::translate("BibliotecaCartiGUIClass", "BibliotecaCartiGUI", 0));
    } // retranslateUi

};

namespace Ui {
    class BibliotecaCartiGUIClass: public Ui_BibliotecaCartiGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BIBLIOTECACARTIGUI_H
