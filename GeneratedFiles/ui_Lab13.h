/********************************************************************************
** Form generated from reading UI file 'Lab13.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAB13_H
#define UI_LAB13_H

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

class Ui_Lab13Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Lab13Class)
    {
        if (Lab13Class->objectName().isEmpty())
            Lab13Class->setObjectName(QStringLiteral("Lab13Class"));
        Lab13Class->resize(600, 400);
        menuBar = new QMenuBar(Lab13Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        Lab13Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Lab13Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Lab13Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(Lab13Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Lab13Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Lab13Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Lab13Class->setStatusBar(statusBar);

        retranslateUi(Lab13Class);

        QMetaObject::connectSlotsByName(Lab13Class);
    } // setupUi

    void retranslateUi(QMainWindow *Lab13Class)
    {
        Lab13Class->setWindowTitle(QApplication::translate("Lab13Class", "Lab13", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Lab13Class: public Ui_Lab13Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAB13_H
